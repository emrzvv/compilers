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
/* %token IF ELSE STATEMENT_EXPR_END
%token WHILE WARNING RETURN COLON TRUE FALSE NEW_LINE */
%token STATEMENT_END CHECK ASSIGN COMMA NEW_LINE
%token TRUE FALSE REF_CONST TYPE_DECL

%token FUNC ENDFUNC PROC ENDPROC
%token IF ENDIF ELSE ELSEIF
%token WHILE DO ENDWHILE
%token REPEAT UNTIL
%token FOR TO ENDFOR

%token PASS

%token <varname> VARNAME
%token <int_const> INT_CONST
%token <char_const> CHAR_CONST
%token <string> STRING_CONST
/* %token <ref_const> REF_CONST */
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
        NewLineCheck {
            printf("\n"); 
            tab=0;
        } 
        CommentCheck 
        Func
        | 
        Program
        NewLineCheck {
            printf("\n"); 
            tab=0;
        } 
        CommentCheck 
        Proc
        |
        Func
        |
        Proc
        ;
Func:
        FuncHeader NewLineCheck {if (!need_tab) printf(" "); tab++;} CommentCheck Body ENDFUNC {printf("endfunc");}
        ;
Proc:   
        ProcHeader NewLineCheck {if (!need_tab) printf(" "); tab++;} CommentCheck Body ENDPROC {printf("endproc");}
CommentCheck:
        | COMMENT {if (need_tab) { print_tabs(tab); need_tab = false;} printf("%s", $COMMENT);} NewLineCheck CommentCheck
        ;
NewLineCheck:
        NEW_LINE {need_tab=true; /*printf("\nneed tab: %d\n", need_tab);*/}
        | {need_tab = false; /*printf("\nneed tab: %d\n", need_tab);*/}
        ;

ProcHeader:
        PROC VARNAME[NAME] {printf("proc %s", $NAME);} NewLineCheck CommentCheck 
                L_BRACKET_ROUND {printf("(");} Sections {if (need_tab) {tab=1; print_tabs(tab);}}
                R_BRACKET_ROUND {printf(")");}
        ;
FuncHeader:
        FUNC VARNAME[NAME] {printf("func %s", $NAME);} NewLineCheck CommentCheck 
                L_BRACKET_ROUND {printf("(");} Sections {if (need_tab) {tab=1; print_tabs(tab);}}
                R_BRACKET_ROUND {printf(")");} TYPE_DECL {printf(" -> ");} Type
        ;

/* FuncParams:
        FuncParams {if (need_tab) print_tabs(tab); else printf(" ");} BasicVar
        | {if (need_tab) {tab++; print_tabs(tab);}} BasicVar
        ; */
Sections:
        Sections STATEMENT_END {printf("; ");} NewLineCheck CommentCheck {if (need_tab) {tab=1; print_tabs(tab);}} Section
        | Section
        ;
Section:
        Parameters TYPE_DECL {if (need_tab) {tab=1; print_tabs(tab); tab=0;} printf(" -> ");} Type
        /* | */
        /* Parameters COMMA {printf(", ");} Var TYPE_DECL {if (need_tab) {tab=1; print_tabs(tab);tab=0;} printf(" -> ");} Type */
        ;
Parameters:
        Var
        |
        Parameters COMMA {printf(", ");} Var
        ;
Var:
        VARNAME[NAME] {printf("%s", $NAME);} NewLineCheck CommentCheck
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
        Statements
        ;
Statements:
        {if (need_tab) {print_tabs(tab);}} Statement
        |
        Statements STATEMENT_END {printf(";");} NewLineCheck {if (!need_tab) {printf(" ");}} CommentCheck {if (!need_tab) {printf(" ");} else {print_tabs(tab);}} Statement
        ;
Statement:
        DeclarationStatement |
        /* AssignmentStatement | */
        /* ArrayAssignmentStatement | */
        /* FunctionCallStatement | */
        /* IfStatement | */
        /* LoopWithPreconditionStatement | */
        /* LoopWithPostconditionStatement | */
        CHECK {printf("check");} Expression
        ;
DeclarationStatement:
        VarDeclarations TYPE_DECL {printf(" -> ");} Type
        ;
VarDeclarations:
        VarDeclaration |
        VarDeclarations COMMA {printf(", ");} VarDeclaration
VarDeclaration:
        Var |
        Var ASSIGN {printf(" = ");} Expression
        ;
FunctionCallStatement:
        VARNAME[FUNC] L_BRACKET_ROUND {printf("(");} Args R_BRACKET_ROUND {printf(")");}
        ;
Args:
        Expression | 
        Args COMMA {printf(", ");} Expression
ArrayCall:
        Spec L_BRACKET_SQUARE {printf("[");} Expression R_BRACKET_SQUARE {printf("]");}
Spec:
        FunctionCallStatement |
        L_BRACKET_SQUARE {printf("[");} Type VARNAME[NAME] {printf(" %s", $NAME);} R_BRACKET_SQUARE {printf("]");} |
        L_BRACKET_SQUARE {printf("[");} Type INT_CONST[INT] {printf(" %s", $INT);} R_BRACKET_SQUARE {printf("]");} |
        Var |
        ArrayCall |
        Const
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
        MUL {printf(" * ");}
        DIV {printf(" / ");}
        MOD {printf(" % ");}
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
%%



int main(int argc, char *argv[]) {
    FILE *input = 0;
    long env[26] = { 0 };
    int tab = 0;
    bool need_tab = false;
    yyscan_t scanner;
    struct Extra extra;

    if (argc > 1) {
        printf("Read file %s\n", argv[1]);
        input = fopen(argv[1], "r");
    } else {
        printf("No file in command line, use stdin\n");
        input = stdin;
    }

    init_scanner(input, &scanner, &extra);
    yyparse(scanner, env, tab, need_tab);
    destroy_scanner(scanner);

    if (input != stdin) {
        fclose(input);
    }

    return 0;
}