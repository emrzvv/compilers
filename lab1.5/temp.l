%option noyywrap bison-bridge bison-locations
%{
    #include <stdio.h>
    #include <stdlib.h>

    #define TAG_IDENT 1
    #define TAG_STRING 2

    char *tags[] = { "EOF", "IDENT", "STRING" };

    typedef struct Position Position;
    struct Position {
        int line, pos;
    };

    void printPosition(Position *p) {
        printf("(%d,%d)", p->line, p->pos);
    }

    struct Fragment {
        Position begin, end;
    };

    typedef struct Fragment YYLTYPE;
    typedef struct Fragment Fragment;
    void printFragment(Fragment *f) {
    	printPosition(&(f->begin));
    	printf("-");
    	printPosition(&(f->end));
    }

    union Token {
        char *string;
        char *ident;
    };

    typedef union Token YYSTYPE;

    struct Position current;
    #define YY_USER_ACTION {             \
        int i;                           \
        yylloc->begin = current;      	 \
        for (i = 0; i < yyleng; i++) {   \
            if (yytext[i] == '\n') {     \
                current.line++;          \
                current.pos = 1;         \
            }                            \
            else                         \
                current.pos++;           \
        }                                \
        yylloc->end = current;           \
    } 


    void init(char *program) {
        current.line = 1;
        current.pos = 1;
        yy_scan_string(program);
    }

    void printError(char *msg) {
        printf("ERROR");
        printPosition(&current);
        printf(": %s\n", msg);
    }
%}


STRING ('([^'\n]|'')+'|(#[0-9]+))*
IDENT [a-zA-Z][a-zA-Z0-9]*
WHITESPACE [ \t\n]+


%%

{WHITESPACE}

{IDENT}         { 
                    yylval->ident = strdup(yytext);
                    return TAG_IDENT;
                }

{STRING}        {
                    yylval->string = strdup(yytext);
                    return TAG_STRING;
		        }

.               printError("unknown symbol");

<<EOF>>         return 0;

%%

int getCodeEnd(char *str, int len) {
    if (str[0] != '#') return -1;
    for (int i = 1; i < len; ++i) {
        if (str[i] < '0' || str[i] > '9') {
            if (i == 1) return -1;
            else return i;
        }
    }
    return len;
}

void translate(char *str, int len) {
    char *temp = (char*)malloc(sizeof(char) * len);
    int j = 0;
    for (int i = 0; i < len; ++i) {
        if (str[i] == '\'') {
            if (i + 1 < len && str[i + 1] == '\'') {
                temp[j] = '\'';
                j++;
                i++;
            } // else skip
        } else if (str[i] == '#') {
            int codeEnd = getCodeEnd(str + i, len - i);
            if (codeEnd != -1) {
                char codeStr[codeEnd];
                strncpy(codeStr, &str[i + 1], codeEnd - 1);
                codeStr[codeEnd - 1] = '\0';

                int code = atoi(codeStr);

                if (code >= 0 && code <= 255) { 
                    temp[j] = (char)code; 
                    j++;
                    i += codeEnd; 
                } else {
                    temp[j] = str[i]; 
                    j++;
                }
            } else {
                temp[j] = str[i];
                j++;
            }
        } else {
            temp[j] = str[i];
            j++;
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
    free(temp);
}

int main() {
    int tagType;
    YYSTYPE value;
    YYLTYPE coords;

   	FILE *input;
	long size;
	char *str;

	union Token token;
	{
        input = fopen("prog", "r");
        if (input == NULL) {
            fputs("File not found", stderr);
            exit(1);
        }

        fseek(input, 0, SEEK_END);
        size = ftell(input);
        rewind(input);

        str = (char*)malloc(sizeof(char) * (size + 1));
        if (str == NULL) {
            fputs("Memory allocation error", stderr);
            exit(2);
        }    
        size_t n = fread(str, sizeof(char), size, input);
        if (n != size) {
            fputs("File read error", stderr);
            exit(3);
        }
    }

    str[size] = '\0';
    fclose(input);
    init(str);
    
    do {
        tagType = yylex(&value, &coords);
        if (tagType == 0)
            break;

        printf("%s ", tags[tagType]);
        printFragment(&coords);
        
        if (tagType == TAG_IDENT) {
            printf(": %s", value.ident);
            free(value.ident);
        } 
        else if (tagType == TAG_STRING) {
            translate(value.string, strlen(value.string));
            printf(": %s", value.string); 
            free(value.string);   
        }

        printf("\n");        
    }
    while (tagType != 0);

	free(str);
    return 0;
}
