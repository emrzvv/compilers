/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    OR = 258,                      /* OR  */
    XOR = 259,                     /* XOR  */
    AND = 260,                     /* AND  */
    EQ = 261,                      /* EQ  */
    NE = 262,                      /* NE  */
    LT = 263,                      /* LT  */
    GT = 264,                      /* GT  */
    LE = 265,                      /* LE  */
    GE = 266,                      /* GE  */
    PLUS = 267,                    /* PLUS  */
    MINUS = 268,                   /* MINUS  */
    POW = 269,                     /* POW  */
    MUL = 270,                     /* MUL  */
    DIV = 271,                     /* DIV  */
    MOD = 272,                     /* MOD  */
    NOT = 273,                     /* NOT  */
    UNARY_MINUS = 274,             /* UNARY_MINUS  */
    L_BRACKET_ROUND = 275,         /* L_BRACKET_ROUND  */
    R_BRACKET_ROUND = 276,         /* R_BRACKET_ROUND  */
    L_BRACKET_SQUARE = 277,        /* L_BRACKET_SQUARE  */
    R_BRACKET_SQUARE = 278,        /* R_BRACKET_SQUARE  */
    INT = 279,                     /* INT  */
    CHAR = 280,                    /* CHAR  */
    BOOL = 281,                    /* BOOL  */
    STATEMENT_END = 282,           /* STATEMENT_END  */
    CHECK = 283,                   /* CHECK  */
    NEW_LINE = 284,                /* NEW_LINE  */
    COMMA = 285,                   /* COMMA  */
    ASSIGN = 286,                  /* ASSIGN  */
    TRUE = 287,                    /* TRUE  */
    FALSE = 288,                   /* FALSE  */
    REF_CONST = 289,               /* REF_CONST  */
    TYPE_DECL = 290,               /* TYPE_DECL  */
    FUNC = 291,                    /* FUNC  */
    ENDFUNC = 292,                 /* ENDFUNC  */
    PROC = 293,                    /* PROC  */
    ENDPROC = 294,                 /* ENDPROC  */
    IF = 295,                      /* IF  */
    THEN = 296,                    /* THEN  */
    ENDIF = 297,                   /* ENDIF  */
    ELSEIF = 298,                  /* ELSEIF  */
    ELSE = 299,                    /* ELSE  */
    WHILE = 300,                   /* WHILE  */
    DO = 301,                      /* DO  */
    ENDWHILE = 302,                /* ENDWHILE  */
    REPEAT = 303,                  /* REPEAT  */
    UNTIL = 304,                   /* UNTIL  */
    FOR = 305,                     /* FOR  */
    TO = 306,                      /* TO  */
    ENDFOR = 307,                  /* ENDFOR  */
    PASS = 308,                    /* PASS  */
    VARNAME = 309,                 /* VARNAME  */
    INT_CONST = 310,               /* INT_CONST  */
    CHAR_CONST = 311,              /* CHAR_CONST  */
    STRING_CONST = 312,            /* STRING_CONST  */
    COMMENT = 313                  /* COMMENT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "parser.y"

    char* int_const;
    char* char_const;
    char* string;
    char* varname;
    char* comment;

#line 130 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (yyscan_t scanner, long env[26], int tab, bool need_tab);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
