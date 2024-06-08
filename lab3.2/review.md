% "Лабораторная работа 3.2 «Форматтер исходных текстов»"
% 7 июня 2024 г.
% Егор Поршенко, ИУ9-61Б

# Цель работы
Целью данной работы является приобретение навыков использования генератора синтаксических анализаторов bison.

# Индивидуальный вариант
Язык L3.

# Реализация

Грамматика
```
Program -> Program Function | Program Procedure | Function | Procedure

Function -> FunctionHeader Statements endfunc
Procedure -> ProcedureHeader Statements endproc
FunctionHeader -> func VARNAME (Sections) -> Type
ProcedureHeader -> proc VARNAME (Sections)

Sections -> Sections; Section | Section
Section -> Parameters, VARNAME -> Type | VARNAME -> Type
Parameters -> Parameters, VARNAME | VARNAME

Type -> PrimitiveType | [Type]
PrimitiveType -> int | char | bool

Statements -> Statements; Statement | Statement
Statement -> 
	DeclarationStatement |
	AssignmentStatement |
	ArrayAssignmentStatement |
	FunctionCallStatement |
	IfStatement | 
	LoopWithPreconditionStatements | 
	LoopWithPostconditionStatement |
	check Expression
	
DeclarationStatement -> VarDeclarations, VarDeclaration -> Type | VarDeclaration -> Type
VarDeclarations ->  VarDeclarations, VarDeclaration | VarDeclaration
VarDeclaration -> VARNAME | AssignmentStatement

AssignmentStatement -> ExtendedVar = Expression
ArrayAssignmentStatement -> ArrayCall = Expression
FunctionCallStatement -> VARNAME(Args)
Args -> Args, Expression | Expression

ExtendedVar -> VARNAME 
ArrayCall -> Spec[Expression]
Spec -> FunctionCallStatement | [Type VARNAME] | [Type INT_CONST] | ExtendedVar | ArrayCall | Const


Const -> INT_CONST | CHAR_CONST | STRING_CONST | REF_CONST | TRUE | FALSE

Expression -> 
	LogicalExpression |
	Expression || LogicalExpression |
	Expression ^^ LogicalExpression
	
LogicalExpression -> LogicalExpression && CompareExpression | CompareExpression
CompareExpression -> ArithmeticExpression CompareOperator ArithmeticExpression | ArithmeticExpression
CompareOperator -> == | != | < | > | <= | >=
ArithmeticExpression -> PowExpression | ArithmeticExpression AdditiveOperator PowExpression
AdditiveOperator -> + | -
PowExpression -> Term | Term ^ PowExpression
Term -> Factor | Term MultiplicativeOperator Factor
MultiplicativeOperator -> * | / | %
Factor -> !Spec | -Spec | Spec


IfStatement -> if Expression then Statements ElseBlock endif
ElseBlock -> else Statements | elseif Expression then Statements ElseBlock

LoopWithPreconditionStatements -> 
	while Expression do Statements endwhile |
	ForCycleHead step INT_CONST do Statements endfor |
	ForCycleHead do Statements endfor
ForCycleHead -> for ForCycleVarDeclaration to ForCycleTo


ForCycleVarDeclaration -> VARNAME = Expression | VARNAME = INT_CONST -> INTEGER | VARNAME = CHAR_CONST -> CHAR
ForCycleTo = Expression

LoopWithPostconditionStatement -> repeat Statements until Expression
```
Лексическая структура
```
VARNAME = [a-zA-Z\_\?\$\@\.\#\~][a-zA-Z0-9\_\?\$\@\.\#\~]*
REF_CONST = nil
INT_CONST = (0x([0-9a-fA-F]{1,8}))|\d+
CHAR_CONST = \'.?\'
STRING_CONST = \"\.*\"
```
Лексер
```
%option reentrant noyywrap bison-bridge bison-locations
%option extra-type="struct Extra *"

%option noinput nounput

%{

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.tab.h"

#define YY_USER_ACTION \
  { \
    int i; \
    struct Extra *extra = yyextra; \
    if (! extra->continued ) { \
      yylloc->first_line = extra->cur_line; \
      yylloc->first_column = extra->cur_column; \
    } \
    extra->continued = false; \
    for (i = 0; i < yyleng; ++i) { \
      if (yytext[i] == '\n') { \
        extra->cur_line += 1; \
        extra->cur_column = 1; \
      } else { \
        extra->cur_column += 1; \
      } \
    } \
    yylloc->last_line = extra->cur_line; \
    yylloc->last_column = extra->cur_column; \
  }

void yyerror(YYLTYPE *loc, yyscan_t scanner, long env[26], int tab, bool need_tab, const char *message) {
    printf("\nError (%d,%d): %s\n", loc->first_line, loc->first_column, message);
}
%}

%%

[\t ]+ {}

[\n]+ {
    printf("\n");
    return NEW_LINE;
}

"int" { return INT; }
"char" { return CHAR; }
"bool" { return BOOL; }

"&&" { return AND; }
"==" { return EQ; }
">=" { return GE; }
">" { return GT; }
"<" { return LT; }
"<=" { return LE; }
"%" { return MOD; }
"!=" { return NE; }
"||" { return OR; }
"^^" { return XOR; }
"^" { return POW; }
"!" { return NOT; }

";" { return STATEMENT_END; }
"check" { return CHECK; }
"=" { return ASSIGN; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MUL; }
"/" { return DIV; }
"(" { return L_BRACKET_ROUND; }
")" { return R_BRACKET_ROUND; }
"[" { return L_BRACKET_SQUARE; }
"]" { return R_BRACKET_SQUARE; }
"," { return COMMA; }
"tt" { return TRUE; }
"ff" { return FALSE; }
"nil" { return REF_CONST; }
"->" { return TYPE_DECL; }

"func" { return FUNC; }
"endfunc" { return ENDFUNC; }
"proc" { return PROC; }
"endproc" { return ENDPROC; }
"if" { return IF; }
"then" {return THEN;}
"endif" { return ENDIF; }
"else" { return ELSE; }
"elseif" { return ELSEIF; }
"while" { return WHILE; }
"do" { return DO; }
"endwhile" { return ENDWHILE; }
"repeat" { return REPEAT; }
"until" { return UNTIL; }
"for" { return FOR; }
"to" { return TO; }
"endfor" { return ENDFOR; }

((0x[0-9a-fA-F]{1,8})|[0-9]+) {
    yylval->int_const = strndup(yytext, yyleng);
    return INT_CONST;
}

([A-Za-z_?$@.#~][A-Za-z_?$@.#~]*)  {
    yylval->varname = strndup(yytext, yyleng);
    return VARNAME; 
}

\".*\"   {
    yylval->string = strndup(yytext, yyleng);
    return STRING_CONST;
}

(\'.?\')|(\$.+\$)   {
    yylval->char_const = strndup(yytext, yyleng);
    return CHAR_CONST;
}

\(\*.*\*\) {
    yylval->comment = strndup(yytext, yyleng);
    return COMMENT;
}
. {}
%%

void init_scanner(FILE *input, yyscan_t *scanner, struct Extra *extra) {
    extra->continued = false;
    extra->cur_line = 1;
    extra->cur_column = 1;

    yylex_init(scanner);
    yylex_init_extra(extra, scanner);
    yyset_in(input, *scanner);
}

void destroy_scanner(yyscan_t scanner) {
    yylex_destroy(scanner);
}
```
Парсер
```
%{
#include <stdio.h>
#include "lexer.h"
%}

%define parse.error verbose
%define api.pure
%locations
%lex-param {yyscan_t scanner}  /* параметр для yylex() */
/* параметры для yyparse() */
%parse-param {yyscan_t scanner}
%parse-param {long env[26]}
%parse-param {int tab}
%parse-param {bool need_tab}

%union {
    char* int_const;
    char* char_const;
    char* string;
    char* varname;
    char* comment;
}

%left OR XOR
%left AND
%left EQ NE LT GT LE GE
%left PLUS MINUS
%right POW
%left MUL DIV MOD
%left NOT UNARY_MINUS

%token L_BRACKET_ROUND R_BRACKET_ROUND L_BRACKET_SQUARE R_BRACKET_SQUARE
%token INT CHAR BOOL
%token STATEMENT_END CHECK NEW_LINE
%left COMMA
%left ASSIGN
%token TRUE FALSE REF_CONST TYPE_DECL

%token FUNC ENDFUNC PROC ENDPROC
%token IF THEN ENDIF ELSEIF ELSE
%left ELSE
%token WHILE DO ENDWHILE
%token REPEAT UNTIL
%token FOR TO ENDFOR

%token PASS

%token <varname> VARNAME
%token <int_const> INT_CONST
%token <char_const> CHAR_CONST
%token <string> STRING_CONST
%token <comment> COMMENT

%{
int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t scanner);
void yyerror(YYLTYPE *loc, yyscan_t scanner, long env[26], int tab, bool need_tab, const char *message);
%}

%{
void print_tabs(int tab) {
    for(int i = 0; i < tab; i++) {
        printf("    ");
    }
}
%}


%%
Program:
        Program 
        CheckIfNewLine {printf("\n");tab=0;}
        |
        Program
        CheckIfComment
        |
        Program 
        Function
        | 
        Program 
        Procedure
        |
        Function
        |
        Procedure
        |
        CheckIfComment
        ;
Function:
        FuncHeader CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment Body ENDFUNC {printf("endfunc\n");}
        ;
Procedure:   
        ProcHeader CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment Body ENDPROC {printf("endproc\n");}
CheckIfComment:
        | COMMENT {if (need_tab) { print_tabs(tab); need_tab = false;} printf("%s", $COMMENT);} CheckIfNewLine CheckIfComment
        ;
CheckIfNewLine:
        NEW_LINE {need_tab=true; /*printf("\nneed tab: %d\n", need_tab);*/}
        | {need_tab = false; /*printf("\nneed tab: %d\n", need_tab);*/}
        ;

ProcHeader:
        PROC VARNAME[NAME] {printf("proc %s", $NAME);} CheckIfNewLine CheckIfComment 
                L_BRACKET_ROUND {printf("(");} Sections {if (need_tab) {tab=1; print_tabs(tab);}}
                R_BRACKET_ROUND {printf(")");}
        ;
FuncHeader:
        FUNC VARNAME[NAME] {printf("func %s", $NAME);} CheckIfNewLine CheckIfComment 
                L_BRACKET_ROUND {printf("(");} Sections {if (need_tab) {tab=1; print_tabs(tab);}}
                R_BRACKET_ROUND {printf(")");} TYPE_DECL {printf(" -> ");} Type
        ;
Sections:
        Sections STATEMENT_END {printf("; ");} CheckIfNewLine CheckIfComment {if (need_tab) {tab=1; print_tabs(tab);}} Section
        | Section
        ;
Section:
        Parameters TYPE_DECL {if (need_tab) {tab=1; print_tabs(tab); tab=0;} printf(" -> ");} Type
        ;
Parameters:
        Var
        |
        Parameters COMMA {printf(", ");} Var
        ;
Var:
        VARNAME[NAME] {printf("%s", $NAME);} //CheckIfNewLine CheckIfComment
        ;
Type:
        PrimitiveType
        |
        L_BRACKET_SQUARE {printf("[");} Type R_BRACKET_SQUARE {printf("]");}
        ;
PrimitiveType:
        INT {printf("int");} | CHAR {printf("char");} | BOOL {printf("bool");}
        ;
Body:
        Statements CheckIfNewLine CheckIfComment
        ;
Statements:
        {if (need_tab) {print_tabs(tab);}} Statement
        |
        Statements STATEMENT_END {printf(";");} CheckIfNewLine {if (!need_tab) {printf(" ");}} CheckIfComment {if (!need_tab) {printf(" ");} else {print_tabs(tab);}} Statement CheckIfNewLine
        ;
Statement:
        DeclarationStatement |
        AssignmentStatement |
        ArrayAssignmentStatement |
        FunctionCallStatement |
        IfStatement |
        LoopWithPreconditionStatement |
        LoopWithPostconditionStatement |
        CHECK {printf("check");} Expression
        ;
DeclarationStatement:
        VarDeclarations TYPE_DECL {printf(" -> ");} Type
        ;
VarDeclarations:
        VarDeclaration |
        VarDeclarations COMMA {printf(", ");} VarDeclaration
        ;
VarDeclaration:
        Var |
        AssignmentStatement
        ;
AssignmentStatement:
        Var ASSIGN {printf(" = ");} Expression //{printf(" <- ASSIGNMENT");}
        ;
ArrayAssignmentStatement:
        ArrayCall ASSIGN {printf(" = ");} Expression
        ;
IfStatement:
        IF {printf("if ");} Expression THEN {printf(" then ");} CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment 
        Body /*CheckIfNewLine*/ {if (!need_tab) printf(" "); tab--;} /*CheckIfComment*/ IfStatementTail
        /* CheckIfNewLine {if (!need_tab) printf(" ");} CheckIfComment */
        ;
IfStatementTail:
        {if (!need_tab) printf(" "); else print_tabs(tab);} ENDIF {printf("endif");} |
        ElseIfBlock |
        ElseBlock {print_tabs(tab);} ENDIF {printf("endif");} CheckIfNewLine CheckIfComment
        ;
ElseBlock:
        ELSE {if (need_tab) print_tabs(tab); printf("else");} CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment Body
        CheckIfNewLine {tab--;} CheckIfComment
        ;
ElseIfBlock:
        ELSEIF {if (need_tab) print_tabs(tab); printf("elseif");} Expression THEN {printf(" then ");} CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment Body
        CheckIfNewLine {if (!need_tab) printf(" "); tab--;} CheckIfComment IfStatementTail
        ;
FunctionCallStatement:
        VARNAME[FUNC] L_BRACKET_ROUND {printf("%s(", $FUNC);} Args R_BRACKET_ROUND {printf(")");}
        ;
Args:
        Expression | 
        Args COMMA {printf(", ");} Expression
ArrayCall:
        Spec L_BRACKET_SQUARE {printf("[");} Expression R_BRACKET_SQUARE {printf("]");}
Spec:
        FunctionCallStatement |
        L_BRACKET_SQUARE {printf("[");} Type ArrayAllocationVar R_BRACKET_SQUARE {printf("]");} |
        Var |
        ArrayCall |
        Const
        ;
ArrayAllocationVar:
        VARNAME[NAME] {printf(" %s", $NAME);} |
        INT_CONST[INT] {printf(" %s", $INT);}
        ;

Expression:
        LogicalExpression |
        Expression OR {printf(" || ");} LogicalExpression |
        Expression XOR {printf(" ^^ ");} LogicalExpression
        ;
LogicalExpression:
        CompareExpression |
        CompareExpression AND {printf(" && ");} CompareExpression
CompareExpression:
        ArithmeticExpression |
        CompareExpression CompareOperator ArithmeticExpression
        ;
CompareOperator:
        EQ {printf(" == ");} |
        NE {printf(" != ");} |
        LT {printf(" < ");} |
        LE {printf(" <= ");} | 
        GT {printf(" > ");} |
        GE {printf(" >= ");}
        ;
ArithmeticExpression:
        MultiplicativeExpression |
        MultiplicativeExpression AdditiveOperator MultiplicativeExpression
AdditiveOperator:
        PLUS {printf(" + ");} |
        MINUS {printf(" - ");}
        ;
MultiplicativeExpression:
        Term |
        MultiplicativeExpression MultiplicativeOperator Term
        ;
MultiplicativeOperator:
        MUL {printf(" * ");} |
        DIV {printf(" / ");} |
        MOD {printf(" %% ");}
        ;
Term:
        Factor | 
        Factor POW {printf(" ^ ");} Term
        ;
Factor:
        NOT {printf("!");} Spec |
        MINUS {printf("-");} Spec |
        Spec
        ;
Const:
        INT_CONST[INT] {printf("%s", $INT);} |
        CHAR_CONST[CHAR] {printf("%s", $CHAR);} | 
        STRING_CONST[STRING] {printf("%s", $STRING);} |
        REF_CONST {printf("nil");} |
        TRUE {printf("tt");} |
        FALSE {printf("ff");}
        ;
LoopWithPreconditionStatement:
        WHILE {printf("while ");} Expression DO {printf(" do");} CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment  Body
        CheckIfNewLine {tab--;} CheckIfComment
        {print_tabs(tab);} ENDWHILE {printf("endwhile");}
        |
        FOR {printf("for ");} Var ASSIGN {printf(" = ");} Expression ForHeadExt TO {printf(" to ");} Expression DO {printf(" do");} CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment  Body
        CheckIfNewLine {tab--;} CheckIfComment
        {print_tabs(tab);} ENDFOR {printf("endfor");}
        ;
ForHeadExt:
        TYPE_DECL {printf(" -> ");} Type
        | {}
        ;
LoopWithPostconditionStatement:
        REPEAT {printf("repeat ");} CheckIfNewLine {if (!need_tab) printf(" "); tab++;} CheckIfComment Body
        CheckIfNewLine {tab--;} CheckIfComment
        {print_tabs(tab);} UNTIL {printf("until ");} Expression

%%



```
# Тестирование

Входные данные

```
func c(c,c -> int) -> int
c -> char;
c = 'A';
A = [int 5], B = [int 10] -> [int];
x, y = B[3], z = y -> int;
y = y % 10;
x = a * 2 + 10 / 5;
if a < b then
a = a + 1
else
b = b + 1
endif;
if a < b then
a = a + 1
else
b = b * 10
endif;
c = 10;
while a < b do
a = a + 1
endwhile;
repeat 
a = a + 1
until a < b;
c = 11
endfunc

proc example(a -> [int])
for letter = 'A' -> char to 'Z' do
print(letter)
endfor
endproc

func SumVectors(A,B->[int])->[int]
size=length(A)->int;
check size==length(B);
C=[int size]->[int];
for i=0->int to size-1 do
C[i]=A[i]+B[i]
endfor;
SumVectors=C
endfunc

proc example(a -> char)
	string = "We say \"Hello, World!\"\n" -> [char]
endproc



```

Вывод на `stdout`

```
func c(c, c -> int) -> int
    c -> char;
    c = 'A';
    A = [int 5], B = [int 10] -> [int];
    x, y = B[3], z = y -> int;
    y = y % 10;
    x = a * 2 + 10 / 5;
    if a < b then 
        a = a + 1
    else
        b = b + 1
    endif;
    if a < b then 
        a = a + 1
    else
        b = b * 10
    endif;
    c = 10;
    while a < b do
        a = a + 1
    endwhile;
    repeat 
        a = a + 1
    until a < b;
    c = 11
endfunc


proc example(a -> [int])
    for letter = 'A' -> char to 'Z' do
        print(letter)
    endfor
endproc


func SumVectors(A, B -> [int]) -> [int]
    size = length(A) -> int;
    checksize == length(B);
    C = [int size] -> [int];
    for i = 0 -> int to size - 1 do
        C[i] = A[i] + B[i]
    endfor;
    SumVectors = C
endfunc


proc example(a -> char)
    string = "We say \"Hello, World!\"\n" -> [char]
endproc



```

# Вывод
В результате выполнения лабораторной работы был получен навык генерации синтаксического анализатора с помощью bison. В силу того, что выданный вариант представляет из себя почти целостный язык программирования с основными конструкциями (и даже в некоторых местах усложнёнными, например, секции параметров в объявлении функций/процедур, усложнённое ветвление с `elseif`, несколько видов циклов и проч.), выполнение данной лабораторной работы оказалось трудоёмкой задачей, но стоящей затраченных усилий. В некоторых местах пришлось изменять правила грамматики, использованной в работах 2.2 и 3.3 из-за конфликтов и "бесполезных" правил. Разработанный слабый форматтер преобразует исходный код, добавляя табуляции и пробелы там, где это необходимо. Навык написания форматтера считаю очень полезным, т.к. они широко используются в промышленной разработке, и может возникнуть необходимость написать, например, форматтер для кастомного формата конфигурационных файлов.