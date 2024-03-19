%option noyywrap bison-bridge bison-locations
%{
    #include <stdio.h>
    #include <stdlib.h>

    #define TAG_IDENT 1
    #define TAG_STRING 2

    char *tag_names[] = { "EOF", "IDENT", "STRING" };

    typedef struct Position Position;
    struct Position {
        int line, pos, index;
    };

    void print_pos(Position *p) {
        printf("(%d,%d)",p->line,p->pos);
    }

    struct Fragment {
        Position starting, following;
    };

    typedef struct Fragment YYLTYPE;
    typedef struct Fragment Fragment;
    void print_frag(Fragment* f) {
    	print_pos(&(f->starting));
    	printf("-");
    	print_pos(&(f->following));
    }

    union Token {
        char *string;
        char *ident;
        int ident_num;
    };

    typedef union Token YYSTYPE;

    int continued;
    struct Position cur;
    #define YY_USER_ACTION {             \
        int i;                           \
        if (!continued)                  \
            yylloc->starting = cur;      \
        continued = 0;                   \
        for ( i = 0; i < yyleng; i++){   \
            if ( yytext[i] == '\n'){     \
                cur.line++;              \
                cur.pos = 1;             \
            }                            \
            else                         \
                cur.pos++;               \
            cur.index++;                 \
        }                                \
        yylloc->following = cur;         \
    } 


    void init_scanner (char *program){
        continued = 0;
        cur.line = 1;
        cur.pos = 1;
        cur.index = 0;
        yy_scan_string(program);
    }

    void err (char *msg){
        printf ("Error");
        print_pos(&cur);
        printf(":%s\n",msg);
    }

    int lexem_size;

    typedef struct{
        int size;
        char** names;
    } identTabel;

    void create_ident_tabel(identTabel * t){
        t->size = 0;
        t->names = NULL;
    }

    int add_ident(identTabel* tabel, char* name){
        for (int i = 0; i < tabel->size; i++){
            if (strcmp(name, tabel->names[i]) == 0){
                return i;
            }
        }

        tabel->size++;
        if (tabel->size == 1){
            tabel->names = (char**)malloc(sizeof(char*) * (tabel->size));
        }
        else {
            tabel->names = (char**)realloc(tabel->names, sizeof(char*) * (tabel->size));
        }
        tabel->names[tabel->size - 1] = (char*)malloc(sizeof(char)*strlen(name));
        strcpy(tabel->names[tabel->size - 1], name);
        return tabel->size-1;
    }

    identTabel tabel;
    
%}


STRING ('([^'\n]|'')+'|(#[0-9]+))*
IDENT [a-zA-Z][a-zA-Z0-9]*
WHITESPACE [ \t\n]+


%%

{WHITESPACE}


{STRING}	      {
			yylval->string = strdup(yytext);
			return TAG_STRING;
		      }


                      
{IDENT}               { 
                        // yylval->ident_num = add_ident(&tabel, yytext);
                        yylval->ident = strdup(yytext);
                        return TAG_IDENT;
                      }

.                     err ("ERROR unknown symbol");

<<EOF>>               return 0;


%%

int main(){
    int tag;
    YYSTYPE value;
    YYLTYPE coords;
   	FILE *inputfile;
	long size_str;
	char *str;
	union Token token;
	{
        inputfile = fopen("prog","r");
        if (inputfile == NULL) {
            fputs("File not found", stderr);
            exit(1);
        }
        fseek(inputfile, 0,SEEK_END);
        size_str = ftell(inputfile);
        rewind(inputfile);

        str=(char*)malloc(sizeof(char)*(size_str+1));
        if (str == NULL) {
            fputs("Memory error",stderr);
            exit(2);
        }    
        size_t n = fread(str,sizeof(char),size_str,inputfile);
        if (n != size_str) {
            fputs ("Reading error",stderr);
            exit (3);
        }
    }

    str[size_str] = '\0';
    fclose (inputfile);
    init_scanner(str);
    create_ident_tabel(&tabel);
    do{
        tag = yylex(&value,&coords);
        if (tag == 0)
            break;

        printf("%s ",tag_names[tag]);
        print_frag(&coords);
        
        
        if (tag == TAG_STRING){
            printf(": %s", value.string); 
            free(value.string);   
        }

        if (tag == TAG_IDENT){
            printf(": %s", value.ident);
            free(value.ident);
        } 

        printf("\n");        
    }
    while (tag != 0); 
    
    printf("\nIDENT TABEL:\n");
    for (int i = 0; i < tabel.size; i++){
        printf("    %d -> %s\n", i, tabel.names[i]);
        free(tabel.names[i]);
    }
    free(tabel.names);

	free(str);
    return 0;
}
