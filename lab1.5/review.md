% Лабораторная работа № 1.5 «Порождение лексического анализатора с помощью flex»
% 20 марта 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является изучение генератора лексических анализаторов flex.

# Индивидуальный вариант
- Идентификаторы: последовательности латинских букв и цифр, начинающиеся с буквы.

- Строковые константы — последовательности строковых секций, записанных слитно. Строковые секции: либо последовательность символов, ограниченных апострофами, апостроф внутри строки описывается как два апострофа подряд, не пересекают границы строк текста, либо знак «#», за которым следует десятичная константа (код символа).

- Пример строковой константы: «'hello'#10#13'world'» (эта строковая константа состоит из 4 строковых секций, однако является единым токеном).
# Реализация

```lex
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

```

# Тестирование

Входные данные

```
Abacabau7t1
dsl'ndsl'k
dlkdgnkl
#60'''aaaaaa'''#62
#sdkj
879asd
#123'some ''string'''#125
''''
```

Вывод на `stdout`

```
IDENT (1,1)-(1,12): Abacabau7t1
IDENT (2,1)-(2,4): dsl
STRING (2,4)-(2,10): ndsl
IDENT (2,10)-(2,11): k
IDENT (3,1)-(3,9): dlkdgnkl
STRING (4,1)-(4,19): <'aaaaaa'>
ERROR(5,2): unknown symbol
IDENT (5,2)-(5,6): sdkj
ERROR(6,2): unknown symbol
ERROR(6,3): unknown symbol
ERROR(6,4): unknown symbol
IDENT (6,4)-(6,7): asd
STRING (7,1)-(7,26): {some 'string'}
STRING (8,1)-(8,5): ''
```

# Вывод
В результате выполнения лабораторной работы ознакомился с генератором лексических анализаторов flex.
Разработал лексический анализатор для идентификаторов и строковых констант.

Самым сложным оказалось вспоминать, как писать на C (в частности, выделение и освобождение памяти) и 
работать на нём со строками. Более простым вариантом было изначально выбирать C++, поскольку 
мне пришлось дописывать функционал перевода символов юникода в строковых константах в непосредственно символы.

Также тестировал программу с помощью valgrind, утечек памяти не было обнаружено.
