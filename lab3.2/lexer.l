%option reentrant noyywrap bison-bridge bison-locations
%option extra-type="struct Extra *"

/* Подавление предупреждений для -Wall */
%option noinput nounput

%{

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.tab.h"  /* файл генерируется Bison’ом */

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

[\t ]+    /* Пропуск пробелов и табуляций */

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
    yylval->number = yytext;  // предполагая, что yylval.number это int
    return NUMBER;
}

([A-Za-z_\?\$\@\.\#\~][A-Za-z_\?\$\@\.\#\~]*)  {
    yylval->varname = yytext;  // предполагая, что yylval.varname это char*
    return VARNAME;
}

\".*\"   {
    yylval->string = yytext;  // предполагая, что yylval.string это char*
    return STRING_CONST;
}

(\'.?\')|(\$.+\$)   {
    yylval->char_const = yytext;  // предполагая, что yylval.char_const это char*
    return CHAR_CONST;
}

\(\*.*\*\) {
    yylval->comment = yytext;  // предполагая, что yylval.comment это char*
    return COMMENT;
}

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
