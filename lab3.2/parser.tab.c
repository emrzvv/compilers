/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include "lexer.h"

#line 76 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_OR = 3,                         /* OR  */
  YYSYMBOL_XOR = 4,                        /* XOR  */
  YYSYMBOL_AND = 5,                        /* AND  */
  YYSYMBOL_EQ = 6,                         /* EQ  */
  YYSYMBOL_NE = 7,                         /* NE  */
  YYSYMBOL_LT = 8,                         /* LT  */
  YYSYMBOL_GT = 9,                         /* GT  */
  YYSYMBOL_LE = 10,                        /* LE  */
  YYSYMBOL_GE = 11,                        /* GE  */
  YYSYMBOL_PLUS = 12,                      /* PLUS  */
  YYSYMBOL_MINUS = 13,                     /* MINUS  */
  YYSYMBOL_POW = 14,                       /* POW  */
  YYSYMBOL_MUL = 15,                       /* MUL  */
  YYSYMBOL_DIV = 16,                       /* DIV  */
  YYSYMBOL_MOD = 17,                       /* MOD  */
  YYSYMBOL_NOT = 18,                       /* NOT  */
  YYSYMBOL_UNARY_MINUS = 19,               /* UNARY_MINUS  */
  YYSYMBOL_L_BRACKET_ROUND = 20,           /* L_BRACKET_ROUND  */
  YYSYMBOL_R_BRACKET_ROUND = 21,           /* R_BRACKET_ROUND  */
  YYSYMBOL_L_BRACKET_SQUARE = 22,          /* L_BRACKET_SQUARE  */
  YYSYMBOL_R_BRACKET_SQUARE = 23,          /* R_BRACKET_SQUARE  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_CHAR = 25,                      /* CHAR  */
  YYSYMBOL_BOOL = 26,                      /* BOOL  */
  YYSYMBOL_STATEMENT_END = 27,             /* STATEMENT_END  */
  YYSYMBOL_CHECK = 28,                     /* CHECK  */
  YYSYMBOL_NEW_LINE = 29,                  /* NEW_LINE  */
  YYSYMBOL_COMMA = 30,                     /* COMMA  */
  YYSYMBOL_ASSIGN = 31,                    /* ASSIGN  */
  YYSYMBOL_TRUE = 32,                      /* TRUE  */
  YYSYMBOL_FALSE = 33,                     /* FALSE  */
  YYSYMBOL_REF_CONST = 34,                 /* REF_CONST  */
  YYSYMBOL_TYPE_DECL = 35,                 /* TYPE_DECL  */
  YYSYMBOL_FUNC = 36,                      /* FUNC  */
  YYSYMBOL_ENDFUNC = 37,                   /* ENDFUNC  */
  YYSYMBOL_PROC = 38,                      /* PROC  */
  YYSYMBOL_ENDPROC = 39,                   /* ENDPROC  */
  YYSYMBOL_IF = 40,                        /* IF  */
  YYSYMBOL_THEN = 41,                      /* THEN  */
  YYSYMBOL_ENDIF = 42,                     /* ENDIF  */
  YYSYMBOL_ELSEIF = 43,                    /* ELSEIF  */
  YYSYMBOL_ELSE = 44,                      /* ELSE  */
  YYSYMBOL_WHILE = 45,                     /* WHILE  */
  YYSYMBOL_DO = 46,                        /* DO  */
  YYSYMBOL_ENDWHILE = 47,                  /* ENDWHILE  */
  YYSYMBOL_REPEAT = 48,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 49,                     /* UNTIL  */
  YYSYMBOL_FOR = 50,                       /* FOR  */
  YYSYMBOL_TO = 51,                        /* TO  */
  YYSYMBOL_ENDFOR = 52,                    /* ENDFOR  */
  YYSYMBOL_PASS = 53,                      /* PASS  */
  YYSYMBOL_VARNAME = 54,                   /* VARNAME  */
  YYSYMBOL_INT_CONST = 55,                 /* INT_CONST  */
  YYSYMBOL_CHAR_CONST = 56,                /* CHAR_CONST  */
  YYSYMBOL_STRING_CONST = 57,              /* STRING_CONST  */
  YYSYMBOL_COMMENT = 58,                   /* COMMENT  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_Program = 60,                   /* Program  */
  YYSYMBOL_Function = 61,                  /* Function  */
  YYSYMBOL_62_1 = 62,                      /* $@1  */
  YYSYMBOL_Procedure = 63,                 /* Procedure  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_CheckIfComment = 65,            /* CheckIfComment  */
  YYSYMBOL_66_3 = 66,                      /* $@3  */
  YYSYMBOL_CheckIfNewLine = 67,            /* CheckIfNewLine  */
  YYSYMBOL_ProcHeader = 68,                /* ProcHeader  */
  YYSYMBOL_69_4 = 69,                      /* $@4  */
  YYSYMBOL_70_5 = 70,                      /* $@5  */
  YYSYMBOL_71_6 = 71,                      /* $@6  */
  YYSYMBOL_FuncHeader = 72,                /* FuncHeader  */
  YYSYMBOL_73_7 = 73,                      /* $@7  */
  YYSYMBOL_74_8 = 74,                      /* $@8  */
  YYSYMBOL_75_9 = 75,                      /* $@9  */
  YYSYMBOL_76_10 = 76,                     /* $@10  */
  YYSYMBOL_77_11 = 77,                     /* $@11  */
  YYSYMBOL_Sections = 78,                  /* Sections  */
  YYSYMBOL_79_12 = 79,                     /* $@12  */
  YYSYMBOL_80_13 = 80,                     /* $@13  */
  YYSYMBOL_Section = 81,                   /* Section  */
  YYSYMBOL_82_14 = 82,                     /* $@14  */
  YYSYMBOL_Parameters = 83,                /* Parameters  */
  YYSYMBOL_84_15 = 84,                     /* $@15  */
  YYSYMBOL_Var = 85,                       /* Var  */
  YYSYMBOL_Type = 86,                      /* Type  */
  YYSYMBOL_87_16 = 87,                     /* $@16  */
  YYSYMBOL_PrimitiveType = 88,             /* PrimitiveType  */
  YYSYMBOL_Body = 89,                      /* Body  */
  YYSYMBOL_Statements = 90,                /* Statements  */
  YYSYMBOL_91_17 = 91,                     /* $@17  */
  YYSYMBOL_92_18 = 92,                     /* $@18  */
  YYSYMBOL_93_19 = 93,                     /* $@19  */
  YYSYMBOL_94_20 = 94,                     /* $@20  */
  YYSYMBOL_Statement = 95,                 /* Statement  */
  YYSYMBOL_96_21 = 96,                     /* $@21  */
  YYSYMBOL_DeclarationStatement = 97,      /* DeclarationStatement  */
  YYSYMBOL_98_22 = 98,                     /* $@22  */
  YYSYMBOL_VarDeclarations = 99,           /* VarDeclarations  */
  YYSYMBOL_100_23 = 100,                   /* $@23  */
  YYSYMBOL_VarDeclaration = 101,           /* VarDeclaration  */
  YYSYMBOL_AssignmentStatement = 102,      /* AssignmentStatement  */
  YYSYMBOL_103_24 = 103,                   /* $@24  */
  YYSYMBOL_ArrayAssignmentStatement = 104, /* ArrayAssignmentStatement  */
  YYSYMBOL_105_25 = 105,                   /* $@25  */
  YYSYMBOL_IfStatement = 106,              /* IfStatement  */
  YYSYMBOL_107_26 = 107,                   /* $@26  */
  YYSYMBOL_108_27 = 108,                   /* $@27  */
  YYSYMBOL_109_28 = 109,                   /* $@28  */
  YYSYMBOL_110_29 = 110,                   /* $@29  */
  YYSYMBOL_IfStatementTail = 111,          /* IfStatementTail  */
  YYSYMBOL_112_30 = 112,                   /* $@30  */
  YYSYMBOL_113_31 = 113,                   /* $@31  */
  YYSYMBOL_114_32 = 114,                   /* $@32  */
  YYSYMBOL_ElseBlock = 115,                /* ElseBlock  */
  YYSYMBOL_116_33 = 116,                   /* $@33  */
  YYSYMBOL_117_34 = 117,                   /* $@34  */
  YYSYMBOL_118_35 = 118,                   /* $@35  */
  YYSYMBOL_ElseIfBlock = 119,              /* ElseIfBlock  */
  YYSYMBOL_120_36 = 120,                   /* $@36  */
  YYSYMBOL_121_37 = 121,                   /* $@37  */
  YYSYMBOL_122_38 = 122,                   /* $@38  */
  YYSYMBOL_123_39 = 123,                   /* $@39  */
  YYSYMBOL_FunctionCallStatement = 124,    /* FunctionCallStatement  */
  YYSYMBOL_125_40 = 125,                   /* $@40  */
  YYSYMBOL_Args = 126,                     /* Args  */
  YYSYMBOL_127_41 = 127,                   /* $@41  */
  YYSYMBOL_ArrayCall = 128,                /* ArrayCall  */
  YYSYMBOL_129_42 = 129,                   /* $@42  */
  YYSYMBOL_Spec = 130,                     /* Spec  */
  YYSYMBOL_131_43 = 131,                   /* $@43  */
  YYSYMBOL_ArrayAllocationVar = 132,       /* ArrayAllocationVar  */
  YYSYMBOL_Expression = 133,               /* Expression  */
  YYSYMBOL_134_44 = 134,                   /* $@44  */
  YYSYMBOL_135_45 = 135,                   /* $@45  */
  YYSYMBOL_LogicalExpression = 136,        /* LogicalExpression  */
  YYSYMBOL_137_46 = 137,                   /* $@46  */
  YYSYMBOL_CompareExpression = 138,        /* CompareExpression  */
  YYSYMBOL_CompareOperator = 139,          /* CompareOperator  */
  YYSYMBOL_ArithmeticExpression = 140,     /* ArithmeticExpression  */
  YYSYMBOL_AdditiveOperator = 141,         /* AdditiveOperator  */
  YYSYMBOL_MultiplicativeExpression = 142, /* MultiplicativeExpression  */
  YYSYMBOL_MultiplicativeOperator = 143,   /* MultiplicativeOperator  */
  YYSYMBOL_Term = 144,                     /* Term  */
  YYSYMBOL_145_47 = 145,                   /* $@47  */
  YYSYMBOL_Factor = 146,                   /* Factor  */
  YYSYMBOL_147_48 = 147,                   /* $@48  */
  YYSYMBOL_148_49 = 148,                   /* $@49  */
  YYSYMBOL_Const = 149,                    /* Const  */
  YYSYMBOL_LoopWithPreconditionStatement = 150, /* LoopWithPreconditionStatement  */
  YYSYMBOL_151_50 = 151,                   /* $@50  */
  YYSYMBOL_152_51 = 152,                   /* $@51  */
  YYSYMBOL_153_52 = 153,                   /* $@52  */
  YYSYMBOL_154_53 = 154,                   /* $@53  */
  YYSYMBOL_155_54 = 155,                   /* $@54  */
  YYSYMBOL_156_55 = 156,                   /* $@55  */
  YYSYMBOL_157_56 = 157,                   /* $@56  */
  YYSYMBOL_158_57 = 158,                   /* $@57  */
  YYSYMBOL_159_58 = 159,                   /* $@58  */
  YYSYMBOL_160_59 = 160,                   /* $@59  */
  YYSYMBOL_161_60 = 161,                   /* $@60  */
  YYSYMBOL_162_61 = 162,                   /* $@61  */
  YYSYMBOL_ForHeadExt = 163,               /* ForHeadExt  */
  YYSYMBOL_164_62 = 164,                   /* $@62  */
  YYSYMBOL_LoopWithPostconditionStatement = 165, /* LoopWithPostconditionStatement  */
  YYSYMBOL_166_63 = 166,                   /* $@63  */
  YYSYMBOL_167_64 = 167,                   /* $@64  */
  YYSYMBOL_168_65 = 168,                   /* $@65  */
  YYSYMBOL_169_66 = 169,                   /* $@66  */
  YYSYMBOL_170_67 = 170                    /* $@67  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 54 "parser.y"

int yylex(YYSTYPE *yylval_param, YYLTYPE *yylloc_param, yyscan_t scanner);
void yyerror(YYLTYPE *loc, yyscan_t scanner, long env[26], int tab, bool need_tab, const char *message);
#line 59 "parser.y"

void print_tabs(int tab) {
    for(int i = 0; i < tab; i++) {
        printf("    ");
    }
}

#line 292 "parser.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  112
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  282

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    70,    70,    73,    76,    79,    82,    84,    86,    89,
      89,    92,    92,    93,    94,    94,    97,    98,   102,   103,
     103,   102,   107,   108,   108,   109,   109,   107,   112,   112,
     112,   113,   116,   116,   119,   121,   121,   124,   127,   129,
     129,   132,   132,   132,   135,   138,   138,   140,   140,   140,
     140,   143,   144,   145,   146,   147,   148,   149,   150,   150,
     153,   153,   156,   157,   157,   160,   161,   164,   164,   167,
     167,   170,   170,   170,   171,   170,   175,   175,   176,   177,
     177,   177,   180,   180,   181,   180,   184,   184,   184,   185,
     184,   188,   188,   191,   192,   192,   194,   194,   196,   197,
     197,   198,   199,   200,   203,   204,   208,   209,   209,   210,
     210,   213,   214,   214,   216,   217,   220,   221,   222,   223,
     224,   225,   228,   229,   231,   232,   235,   236,   239,   240,
     241,   244,   245,   245,   248,   248,   249,   249,   250,   253,
     254,   255,   256,   257,   258,   261,   261,   261,   262,   263,
     261,   265,   265,   265,   265,   265,   266,   267,   265,   270,
     270,   271,   274,   274,   275,   276,   276,   274
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "OR", "XOR", "AND",
  "EQ", "NE", "LT", "GT", "LE", "GE", "PLUS", "MINUS", "POW", "MUL", "DIV",
  "MOD", "NOT", "UNARY_MINUS", "L_BRACKET_ROUND", "R_BRACKET_ROUND",
  "L_BRACKET_SQUARE", "R_BRACKET_SQUARE", "INT", "CHAR", "BOOL",
  "STATEMENT_END", "CHECK", "NEW_LINE", "COMMA", "ASSIGN", "TRUE", "FALSE",
  "REF_CONST", "TYPE_DECL", "FUNC", "ENDFUNC", "PROC", "ENDPROC", "IF",
  "THEN", "ENDIF", "ELSEIF", "ELSE", "WHILE", "DO", "ENDWHILE", "REPEAT",
  "UNTIL", "FOR", "TO", "ENDFOR", "PASS", "VARNAME", "INT_CONST",
  "CHAR_CONST", "STRING_CONST", "COMMENT", "$accept", "Program",
  "Function", "$@1", "Procedure", "$@2", "CheckIfComment", "$@3",
  "CheckIfNewLine", "ProcHeader", "$@4", "$@5", "$@6", "FuncHeader", "$@7",
  "$@8", "$@9", "$@10", "$@11", "Sections", "$@12", "$@13", "Section",
  "$@14", "Parameters", "$@15", "Var", "Type", "$@16", "PrimitiveType",
  "Body", "Statements", "$@17", "$@18", "$@19", "$@20", "Statement",
  "$@21", "DeclarationStatement", "$@22", "VarDeclarations", "$@23",
  "VarDeclaration", "AssignmentStatement", "$@24",
  "ArrayAssignmentStatement", "$@25", "IfStatement", "$@26", "$@27",
  "$@28", "$@29", "IfStatementTail", "$@30", "$@31", "$@32", "ElseBlock",
  "$@33", "$@34", "$@35", "ElseIfBlock", "$@36", "$@37", "$@38", "$@39",
  "FunctionCallStatement", "$@40", "Args", "$@41", "ArrayCall", "$@42",
  "Spec", "$@43", "ArrayAllocationVar", "Expression", "$@44", "$@45",
  "LogicalExpression", "$@46", "CompareExpression", "CompareOperator",
  "ArithmeticExpression", "AdditiveOperator", "MultiplicativeExpression",
  "MultiplicativeOperator", "Term", "$@47", "Factor", "$@48", "$@49",
  "Const", "LoopWithPreconditionStatement", "$@50", "$@51", "$@52", "$@53",
  "$@54", "$@55", "$@56", "$@57", "$@58", "$@59", "$@60", "$@61",
  "ForHeadExt", "$@62", "LoopWithPostconditionStatement", "$@63", "$@64",
  "$@65", "$@66", "$@67", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-102)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -20,   -23,     7,  -114,    24,  -114,  -114,  -114,    67,    67,
    -114,  -114,    67,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,    67,    67,    45,    45,    45,    45,    45,  -114,  -114,
    -114,    97,   101,    83,    51,    57,    94,  -114,  -114,  -114,
    -114,    45,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,   112,  -114,  -114,  -114,    41,  -114,  -114,    65,  -114,
      74,  -114,  -114,   111,   104,   114,  -114,  -114,  -114,  -114,
      84,    84,    67,  -114,   142,    12,    12,    12,    67,    84,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,   126,  -114,    80,
    -114,   126,  -114,  -114,  -114,  -114,  -114,   -45,  -114,  -114,
    -114,  -114,  -114,  -114,   114,    55,  -114,   119,  -114,   139,
    -114,   125,    29,     8,  -114,   130,    12,    12,    84,   142,
      12,    12,  -114,   144,  -114,  -114,   148,    45,   142,  -114,
    -114,   150,    86,    86,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,    12,  -114,  -114,  -114,  -114,  -114,    12,
      12,  -114,  -114,  -114,    45,  -114,    54,    55,    55,   140,
    -114,  -114,  -114,    55,    53,    67,  -114,    84,   142,  -114,
    -114,   151,  -114,   114,   114,    12,    12,    12,  -114,    77,
    -114,    12,    67,    67,  -114,    12,  -114,  -114,  -114,    45,
     141,  -114,  -114,    57,  -114,  -114,  -114,   138,  -114,  -114,
    -114,    67,    39,    12,  -114,  -114,    67,    45,    45,  -114,
    -114,   124,    55,    84,   142,  -114,  -114,  -114,    45,   142,
    -114,  -114,  -114,  -114,    67,  -114,  -114,    12,    21,  -114,
     129,    25,  -114,  -114,  -114,   137,  -114,  -114,    45,  -114,
    -114,    12,    67,  -114,   149,  -114,    12,    67,    32,  -114,
    -114,   133,    55,  -114,  -114,    45,    67,  -114,    45,    67,
    -114,    45,  -114,  -114,    67,  -114,    67,    45,  -114,  -114,
    -114,    45,    45,    67,  -114,  -114,  -114,   132,    45,  -114,
      21,  -114
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      13,     0,     0,    14,     0,     6,     7,     8,    17,    17,
      22,    18,    17,     1,    16,     4,     5,     3,     2,    11,
       9,    17,    17,    13,    13,    13,    13,    13,    15,    45,
      45,     0,     0,     0,    17,     0,     0,    23,    19,    12,
      47,    13,    99,    58,   143,   144,   142,    71,   145,   162,
     151,    37,   139,   140,   141,    65,    46,    51,     0,    62,
      52,    53,    55,    54,   102,     0,   103,    56,    57,    10,
       0,     0,    17,    44,     0,     0,     0,     0,    17,     0,
      91,    67,    63,    60,    69,    96,    37,    24,    31,     0,
      34,    20,    48,    39,    41,    42,    43,     0,    38,   136,
     134,   101,    98,   102,   138,    59,   106,   111,   114,   122,
     126,   131,     0,     0,   163,     0,     0,     0,     0,     0,
       0,     0,    28,     0,    35,    32,     0,    13,     0,   104,
     105,     0,     0,     0,   107,   109,   112,   116,   117,   118,
     120,   119,   121,     0,   124,   125,   128,   129,   130,     0,
       0,   132,    72,   146,    13,   152,     0,    93,    68,    65,
      64,    66,    61,    70,     0,    17,    25,     0,     0,    21,
      49,     0,   100,   137,   135,     0,     0,     0,   115,   123,
     127,     0,    17,    17,    45,     0,    92,    94,    97,    13,
       0,    36,    33,     0,    40,   108,   110,   113,   133,    73,
     147,    17,   161,     0,    29,    26,    17,    13,    13,   164,
     159,     0,    95,     0,     0,    50,    45,    45,    13,     0,
     153,    30,    27,    74,    17,   165,   160,     0,    76,   148,
       0,     0,    86,    82,    75,     0,    79,    78,    13,   166,
     154,     0,    17,    77,     0,   149,     0,    17,     0,    83,
      80,     0,   167,   155,    87,    13,    17,   150,    13,    17,
      45,    13,    45,    88,    17,    81,    17,    13,    84,   156,
      45,    13,    13,    17,    85,   157,    89,     0,    13,   158,
      76,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,   177,  -114,   178,  -114,    -4,  -114,     5,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   115,
    -114,  -114,   -21,  -114,  -114,  -114,   -30,  -113,  -114,  -114,
     -27,  -114,  -114,  -114,  -114,  -114,     0,  -114,  -114,  -114,
    -114,  -114,    76,    78,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,   -85,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,   -33,  -114,  -114,  -114,   -31,
    -114,   -34,  -114,  -114,   -69,  -114,  -114,   -89,  -114,    20,
    -114,    56,  -114,    49,  -114,  -100,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
    -114,  -114
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     4,     5,    25,     6,    24,     7,    12,    18,     8,
      22,    71,   126,     9,    21,    70,   123,   190,   214,    87,
     165,   213,    88,   168,    89,   167,   101,    97,   128,    98,
      33,    34,    35,    72,   127,   193,    56,    75,    57,   119,
      58,   118,    59,    60,   117,    61,   120,    62,    76,   182,
     207,   228,   234,   235,   244,   256,   236,   242,   255,   271,
     237,   241,   259,   267,   278,   102,   116,   156,   203,   103,
     121,   104,    74,   131,   105,   175,   176,   106,   177,   107,
     143,   108,   149,   109,   150,   110,   181,   111,   133,   132,
      66,    67,    77,   183,   208,   238,   251,    79,   185,   227,
     247,   258,   272,   277,   211,   219,    68,    78,   154,   218,
     230,   246
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    65,    63,    36,    64,    55,   162,   112,   113,   129,
     130,   134,   135,    19,    20,   171,     1,    23,     2,    28,
      29,    30,    31,    32,    13,    99,    26,    27,   134,   135,
     100,    10,   134,   135,    42,   134,   135,    73,     3,    41,
      90,    90,   134,   135,    44,    45,    46,   157,   158,   115,
     180,   163,   164,    14,   153,   192,   134,   135,   134,   135,
       1,    11,     2,  -101,   232,   233,    51,    52,    53,    54,
     152,   240,    81,   254,   210,   186,   188,    92,    40,    42,
      14,   198,     3,   114,   187,    43,   195,   196,   159,    44,
      45,    46,   146,   147,   148,    82,    14,    47,   173,   174,
      83,   222,    48,     3,   -66,    49,   226,    50,    42,   -66,
     124,    51,    52,    53,    54,   125,   202,    37,    44,    45,
      46,    38,    39,   170,   136,   137,   138,   139,   140,   141,
     142,    69,    80,   -98,   212,    84,    85,   191,    86,   151,
      51,    52,    53,    54,   137,   138,   139,   140,   141,   142,
     184,   144,   145,   122,   146,   147,   148,   201,   231,    65,
      63,   155,    64,    55,    93,   166,    94,    95,    96,   169,
     189,    81,   248,   172,   194,   220,   205,   252,   239,   243,
     257,    15,    16,    90,   279,   204,    91,   199,   200,   223,
     224,   250,   221,   206,   160,   281,   161,   197,   179,   178,
       0,     0,     0,   216,   217,     0,   209,     0,     0,     0,
       0,   215,     0,     0,   225,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   229,
       0,     0,     0,   264,   245,   266,     0,     0,     0,     0,
       0,     0,     0,   273,     0,     0,     0,   249,     0,     0,
       0,   260,   253,     0,   262,     0,     0,   265,     0,     0,
       0,   261,     0,   270,   263,     0,     0,   274,   275,   268,
       0,   269,     0,     0,   280,     0,     0,     0,   276
};

static const yytype_int16 yycheck[] =
{
       4,    35,    35,    30,    35,    35,   119,    76,    77,    54,
      55,     3,     4,     8,     9,   128,    36,    12,    38,    23,
      24,    25,    26,    27,     0,    13,    21,    22,     3,     4,
      18,    54,     3,     4,    22,     3,     4,    41,    58,    34,
      70,    71,     3,     4,    32,    33,    34,   116,   117,    79,
     150,   120,   121,    29,    46,   168,     3,     4,     3,     4,
      36,    54,    38,    22,    43,    44,    54,    55,    56,    57,
      41,    46,    31,    41,    35,    21,    23,    72,    27,    22,
      29,   181,    58,    78,    30,    28,   175,   176,   118,    32,
      33,    34,    15,    16,    17,    30,    29,    40,   132,   133,
      35,   214,    45,    58,    30,    48,   219,    50,    22,    35,
      30,    54,    55,    56,    57,    35,   185,    20,    32,    33,
      34,    20,    39,   127,     5,     6,     7,     8,     9,    10,
      11,    37,    20,    22,   203,    31,    22,   167,    54,    14,
      54,    55,    56,    57,     6,     7,     8,     9,    10,    11,
     154,    12,    13,    27,    15,    16,    17,   184,   227,   193,
     193,    31,   193,   193,    22,    21,    24,    25,    26,    21,
     165,    31,   241,    23,    23,    51,    35,   246,    49,    42,
      47,     4,     4,   213,    52,   189,    71,   182,   183,   216,
     217,    42,   213,   193,   118,   280,   118,   177,   149,   143,
      -1,    -1,    -1,   207,   208,    -1,   201,    -1,    -1,    -1,
      -1,   206,    -1,    -1,   218,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   224,
      -1,    -1,    -1,   260,   238,   262,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   270,    -1,    -1,    -1,   242,    -1,    -1,
      -1,   255,   247,    -1,   258,    -1,    -1,   261,    -1,    -1,
      -1,   256,    -1,   267,   259,    -1,    -1,   271,   272,   264,
      -1,   266,    -1,    -1,   278,    -1,    -1,    -1,   273
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    38,    58,    60,    61,    63,    65,    68,    72,
      54,    54,    66,     0,    29,    61,    63,    65,    67,    67,
      67,    73,    69,    67,    64,    62,    67,    67,    65,    65,
      65,    65,    65,    89,    90,    91,    89,    20,    20,    39,
      27,    67,    22,    28,    32,    33,    34,    40,    45,    48,
      50,    54,    55,    56,    57,    85,    95,    97,    99,   101,
     102,   104,   106,   124,   128,   130,   149,   150,   165,    37,
      74,    70,    92,    65,   131,    96,   107,   151,   166,   156,
      20,    31,    30,    35,    31,    22,    54,    78,    81,    83,
      85,    78,    67,    22,    24,    25,    26,    86,    88,    13,
      18,    85,   124,   128,   130,   133,   136,   138,   140,   142,
     144,   146,   133,   133,    67,    85,   125,   103,   100,    98,
     105,   129,    27,    75,    30,    35,    71,    93,    87,    54,
      55,   132,   148,   147,     3,     4,     5,     6,     7,     8,
       9,    10,    11,   139,    12,    13,    15,    16,    17,   141,
     143,    14,    41,    46,   167,    31,   126,   133,   133,    85,
     101,   102,    86,   133,   133,    79,    21,    84,    82,    21,
      65,    86,    23,   130,   130,   134,   135,   137,   140,   142,
     144,   145,   108,   152,    65,   157,    21,    30,    23,    67,
      76,    85,    86,    94,    23,   136,   136,   138,   144,    67,
      67,    89,   133,   127,    65,    35,    95,   109,   153,    67,
      35,   163,   133,    80,    77,    67,    65,    65,   168,   164,
      51,    81,    86,    89,    89,    65,    86,   158,   110,    67,
     169,   133,    43,    44,   111,   112,   115,   119,   154,    49,
      46,   120,   116,    42,   113,    65,   170,   159,   133,    67,
      42,   155,   133,    67,    41,   117,   114,    47,   160,   121,
      65,    67,    65,    67,    89,    65,    89,   122,    67,    67,
      65,   118,   161,    89,    65,    65,    67,   162,   123,    52,
      65,   111
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    60,    60,    60,    60,    60,    60,    62,
      61,    64,    63,    65,    66,    65,    67,    67,    69,    70,
      71,    68,    73,    74,    75,    76,    77,    72,    79,    80,
      78,    78,    82,    81,    83,    84,    83,    85,    86,    87,
      86,    88,    88,    88,    89,    91,    90,    92,    93,    94,
      90,    95,    95,    95,    95,    95,    95,    95,    96,    95,
      98,    97,    99,   100,    99,   101,   101,   103,   102,   105,
     104,   107,   108,   109,   110,   106,   112,   111,   111,   113,
     114,   111,   116,   117,   118,   115,   120,   121,   122,   123,
     119,   125,   124,   126,   127,   126,   129,   128,   130,   131,
     130,   130,   130,   130,   132,   132,   133,   134,   133,   135,
     133,   136,   137,   136,   138,   138,   139,   139,   139,   139,
     139,   139,   140,   140,   141,   141,   142,   142,   143,   143,
     143,   144,   145,   144,   147,   146,   148,   146,   146,   149,
     149,   149,   149,   149,   149,   151,   152,   153,   154,   155,
     150,   156,   157,   158,   159,   160,   161,   162,   150,   164,
     163,   163,   166,   167,   168,   169,   170,   165
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     2,     1,     1,     1,     0,
       6,     0,     6,     0,     0,     4,     1,     0,     0,     0,
       0,    10,     0,     0,     0,     0,     0,    14,     0,     0,
       7,     1,     0,     4,     1,     0,     4,     1,     1,     0,
       4,     1,     1,     1,     3,     0,     2,     0,     0,     0,
       9,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     4,     1,     0,     4,     1,     1,     0,     4,     0,
       4,     0,     0,     0,     0,    11,     0,     2,     1,     0,
       0,     6,     0,     0,     0,     9,     0,     0,     0,     0,
      13,     0,     5,     1,     0,     4,     0,     5,     1,     0,
       5,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     1,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     0,     4,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     0,     0,     0,
      14,     0,     0,     0,     0,     0,     0,     0,    21,     0,
       3,     0,     0,     0,     0,     0,     0,    13
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, env, tab, need_tab, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner, env, tab, need_tab); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, long env[26], int tab, bool need_tab)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (env);
  YY_USE (tab);
  YY_USE (need_tab);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner, long env[26], int tab, bool need_tab)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner, env, tab, need_tab);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner, long env[26], int tab, bool need_tab)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner, env, tab, need_tab);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, env, tab, need_tab); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, long env[26], int tab, bool need_tab)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  YY_USE (env);
  YY_USE (tab);
  YY_USE (need_tab);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner, long env[26], int tab, bool need_tab)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Program CheckIfNewLine  */
#line 71 "parser.y"
                       {printf("\n");tab=0;}
#line 1876 "parser.tab.c"
    break;

  case 9: /* $@1: %empty  */
#line 89 "parser.y"
                                  {if (!need_tab) printf(" "); tab++;}
#line 1882 "parser.tab.c"
    break;

  case 10: /* Function: FuncHeader CheckIfNewLine $@1 CheckIfComment Body ENDFUNC  */
#line 89 "parser.y"
                                                                                                   {printf("endfunc\n");}
#line 1888 "parser.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 92 "parser.y"
                                  {if (!need_tab) printf(" "); tab++;}
#line 1894 "parser.tab.c"
    break;

  case 12: /* Procedure: ProcHeader CheckIfNewLine $@2 CheckIfComment Body ENDPROC  */
#line 92 "parser.y"
                                                                                                   {printf("endproc\n");}
#line 1900 "parser.tab.c"
    break;

  case 14: /* $@3: %empty  */
#line 94 "parser.y"
                  {if (need_tab) { print_tabs(tab); need_tab = false;} printf("%s", (yyvsp[0].comment));}
#line 1906 "parser.tab.c"
    break;

  case 16: /* CheckIfNewLine: NEW_LINE  */
#line 97 "parser.y"
                 {need_tab=true; /*printf("\nneed tab: %d\n", need_tab);*/}
#line 1912 "parser.tab.c"
    break;

  case 17: /* CheckIfNewLine: %empty  */
#line 98 "parser.y"
          {need_tab = false; /*printf("\nneed tab: %d\n", need_tab);*/}
#line 1918 "parser.tab.c"
    break;

  case 18: /* $@4: %empty  */
#line 102 "parser.y"
                           {printf("proc %s", (yyvsp[0].varname));}
#line 1924 "parser.tab.c"
    break;

  case 19: /* $@5: %empty  */
#line 103 "parser.y"
                                {printf("(");}
#line 1930 "parser.tab.c"
    break;

  case 20: /* $@6: %empty  */
#line 103 "parser.y"
                                                        {if (need_tab) {tab=1; print_tabs(tab);}}
#line 1936 "parser.tab.c"
    break;

  case 21: /* ProcHeader: PROC VARNAME $@4 CheckIfNewLine CheckIfComment L_BRACKET_ROUND $@5 Sections $@6 R_BRACKET_ROUND  */
#line 104 "parser.y"
                                {printf(")");}
#line 1942 "parser.tab.c"
    break;

  case 22: /* $@7: %empty  */
#line 107 "parser.y"
                           {printf("func %s", (yyvsp[0].varname));}
#line 1948 "parser.tab.c"
    break;

  case 23: /* $@8: %empty  */
#line 108 "parser.y"
                                {printf("(");}
#line 1954 "parser.tab.c"
    break;

  case 24: /* $@9: %empty  */
#line 108 "parser.y"
                                                        {if (need_tab) {tab=1; print_tabs(tab);}}
#line 1960 "parser.tab.c"
    break;

  case 25: /* $@10: %empty  */
#line 109 "parser.y"
                                {printf(")");}
#line 1966 "parser.tab.c"
    break;

  case 26: /* $@11: %empty  */
#line 109 "parser.y"
                                                         {printf(" -> ");}
#line 1972 "parser.tab.c"
    break;

  case 28: /* $@12: %empty  */
#line 112 "parser.y"
                               {printf("; ");}
#line 1978 "parser.tab.c"
    break;

  case 29: /* $@13: %empty  */
#line 112 "parser.y"
                                                                             {if (need_tab) {tab=1; print_tabs(tab);}}
#line 1984 "parser.tab.c"
    break;

  case 32: /* $@14: %empty  */
#line 116 "parser.y"
                             {if (need_tab) {tab=1; print_tabs(tab); tab=0;} printf(" -> ");}
#line 1990 "parser.tab.c"
    break;

  case 35: /* $@15: %empty  */
#line 121 "parser.y"
                         {printf(", ");}
#line 1996 "parser.tab.c"
    break;

  case 37: /* Var: VARNAME  */
#line 124 "parser.y"
                      {printf("%s", (yyvsp[0].varname));}
#line 2002 "parser.tab.c"
    break;

  case 39: /* $@16: %empty  */
#line 129 "parser.y"
                         {printf("[");}
#line 2008 "parser.tab.c"
    break;

  case 40: /* Type: L_BRACKET_SQUARE $@16 Type R_BRACKET_SQUARE  */
#line 129 "parser.y"
                                                              {printf("]");}
#line 2014 "parser.tab.c"
    break;

  case 41: /* PrimitiveType: INT  */
#line 132 "parser.y"
            {printf("int");}
#line 2020 "parser.tab.c"
    break;

  case 42: /* PrimitiveType: CHAR  */
#line 132 "parser.y"
                                    {printf("char");}
#line 2026 "parser.tab.c"
    break;

  case 43: /* PrimitiveType: BOOL  */
#line 132 "parser.y"
                                                             {printf("bool");}
#line 2032 "parser.tab.c"
    break;

  case 45: /* $@17: %empty  */
#line 138 "parser.y"
        {if (need_tab) {print_tabs(tab);}}
#line 2038 "parser.tab.c"
    break;

  case 47: /* $@18: %empty  */
#line 140 "parser.y"
                                 {printf(";");}
#line 2044 "parser.tab.c"
    break;

  case 48: /* $@19: %empty  */
#line 140 "parser.y"
                                                               {if (!need_tab) {printf(" ");}}
#line 2050 "parser.tab.c"
    break;

  case 49: /* $@20: %empty  */
#line 140 "parser.y"
                                                                                                              {if (!need_tab) {printf(" ");} else {print_tabs(tab);}}
#line 2056 "parser.tab.c"
    break;

  case 58: /* $@21: %empty  */
#line 150 "parser.y"
              {printf("check");}
#line 2062 "parser.tab.c"
    break;

  case 60: /* $@22: %empty  */
#line 153 "parser.y"
                                  {printf(" -> ");}
#line 2068 "parser.tab.c"
    break;

  case 63: /* $@23: %empty  */
#line 157 "parser.y"
                              {printf(", ");}
#line 2074 "parser.tab.c"
    break;

  case 67: /* $@24: %empty  */
#line 164 "parser.y"
                   {printf(" = ");}
#line 2080 "parser.tab.c"
    break;

  case 69: /* $@25: %empty  */
#line 167 "parser.y"
                         {printf(" = ");}
#line 2086 "parser.tab.c"
    break;

  case 71: /* $@26: %empty  */
#line 170 "parser.y"
           {printf("if ");}
#line 2092 "parser.tab.c"
    break;

  case 72: /* $@27: %empty  */
#line 170 "parser.y"
                                            {printf(" then ");}
#line 2098 "parser.tab.c"
    break;

  case 73: /* $@28: %empty  */
#line 170 "parser.y"
                                                                               {if (!need_tab) printf(" "); tab++;}
#line 2104 "parser.tab.c"
    break;

  case 74: /* $@29: %empty  */
#line 171 "parser.y"
                                {if (!need_tab) printf(" "); tab--;}
#line 2110 "parser.tab.c"
    break;

  case 76: /* $@30: %empty  */
#line 175 "parser.y"
        {if (!need_tab) printf(" "); else print_tabs(tab);}
#line 2116 "parser.tab.c"
    break;

  case 77: /* IfStatementTail: $@30 ENDIF  */
#line 175 "parser.y"
                                                                  {printf("endif");}
#line 2122 "parser.tab.c"
    break;

  case 79: /* $@31: %empty  */
#line 177 "parser.y"
                  {print_tabs(tab);}
#line 2128 "parser.tab.c"
    break;

  case 80: /* $@32: %empty  */
#line 177 "parser.y"
                                           {printf("endif");}
#line 2134 "parser.tab.c"
    break;

  case 82: /* $@33: %empty  */
#line 180 "parser.y"
             {if (need_tab) print_tabs(tab); printf("else");}
#line 2140 "parser.tab.c"
    break;

  case 83: /* $@34: %empty  */
#line 180 "parser.y"
                                                                             {if (!need_tab) printf(" "); tab++;}
#line 2146 "parser.tab.c"
    break;

  case 84: /* $@35: %empty  */
#line 181 "parser.y"
                       {tab--;}
#line 2152 "parser.tab.c"
    break;

  case 86: /* $@36: %empty  */
#line 184 "parser.y"
               {if (need_tab) print_tabs(tab); printf("elseif");}
#line 2158 "parser.tab.c"
    break;

  case 87: /* $@37: %empty  */
#line 184 "parser.y"
                                                                                  {printf(" then ");}
#line 2164 "parser.tab.c"
    break;

  case 88: /* $@38: %empty  */
#line 184 "parser.y"
                                                                                                                     {if (!need_tab) printf(" "); tab++;}
#line 2170 "parser.tab.c"
    break;

  case 89: /* $@39: %empty  */
#line 185 "parser.y"
                       {if (!need_tab) printf(" "); tab--;}
#line 2176 "parser.tab.c"
    break;

  case 91: /* $@40: %empty  */
#line 188 "parser.y"
                                      {printf("%s(", (yyvsp[-1].varname));}
#line 2182 "parser.tab.c"
    break;

  case 92: /* FunctionCallStatement: VARNAME L_BRACKET_ROUND $@40 Args R_BRACKET_ROUND  */
#line 188 "parser.y"
                                                                                   {printf(")");}
#line 2188 "parser.tab.c"
    break;

  case 94: /* $@41: %empty  */
#line 192 "parser.y"
                   {printf(", ");}
#line 2194 "parser.tab.c"
    break;

  case 96: /* $@42: %empty  */
#line 194 "parser.y"
                              {printf("[");}
#line 2200 "parser.tab.c"
    break;

  case 97: /* ArrayCall: Spec L_BRACKET_SQUARE $@42 Expression R_BRACKET_SQUARE  */
#line 194 "parser.y"
                                                                         {printf("]");}
#line 2206 "parser.tab.c"
    break;

  case 99: /* $@43: %empty  */
#line 197 "parser.y"
                         {printf("[");}
#line 2212 "parser.tab.c"
    break;

  case 100: /* Spec: L_BRACKET_SQUARE $@43 Type ArrayAllocationVar R_BRACKET_SQUARE  */
#line 197 "parser.y"
                                                                                 {printf("]");}
#line 2218 "parser.tab.c"
    break;

  case 104: /* ArrayAllocationVar: VARNAME  */
#line 203 "parser.y"
                      {printf(" %s", (yyvsp[0].varname));}
#line 2224 "parser.tab.c"
    break;

  case 105: /* ArrayAllocationVar: INT_CONST  */
#line 204 "parser.y"
                       {printf(" %s", (yyvsp[0].int_const));}
#line 2230 "parser.tab.c"
    break;

  case 107: /* $@44: %empty  */
#line 209 "parser.y"
                      {printf(" || ");}
#line 2236 "parser.tab.c"
    break;

  case 109: /* $@45: %empty  */
#line 210 "parser.y"
                       {printf(" ^^ ");}
#line 2242 "parser.tab.c"
    break;

  case 112: /* $@46: %empty  */
#line 214 "parser.y"
                              {printf(" && ");}
#line 2248 "parser.tab.c"
    break;

  case 116: /* CompareOperator: EQ  */
#line 220 "parser.y"
           {printf(" == ");}
#line 2254 "parser.tab.c"
    break;

  case 117: /* CompareOperator: NE  */
#line 221 "parser.y"
           {printf(" != ");}
#line 2260 "parser.tab.c"
    break;

  case 118: /* CompareOperator: LT  */
#line 222 "parser.y"
           {printf(" < ");}
#line 2266 "parser.tab.c"
    break;

  case 119: /* CompareOperator: LE  */
#line 223 "parser.y"
           {printf(" <= ");}
#line 2272 "parser.tab.c"
    break;

  case 120: /* CompareOperator: GT  */
#line 224 "parser.y"
           {printf(" > ");}
#line 2278 "parser.tab.c"
    break;

  case 121: /* CompareOperator: GE  */
#line 225 "parser.y"
           {printf(" >= ");}
#line 2284 "parser.tab.c"
    break;

  case 124: /* AdditiveOperator: PLUS  */
#line 231 "parser.y"
             {printf(" + ");}
#line 2290 "parser.tab.c"
    break;

  case 125: /* AdditiveOperator: MINUS  */
#line 232 "parser.y"
              {printf(" - ");}
#line 2296 "parser.tab.c"
    break;

  case 128: /* MultiplicativeOperator: MUL  */
#line 239 "parser.y"
            {printf(" * ");}
#line 2302 "parser.tab.c"
    break;

  case 129: /* MultiplicativeOperator: DIV  */
#line 240 "parser.y"
            {printf(" / ");}
#line 2308 "parser.tab.c"
    break;

  case 130: /* MultiplicativeOperator: MOD  */
#line 241 "parser.y"
            {printf(" %% ");}
#line 2314 "parser.tab.c"
    break;

  case 132: /* $@47: %empty  */
#line 245 "parser.y"
                   {printf(" ^ ");}
#line 2320 "parser.tab.c"
    break;

  case 134: /* $@48: %empty  */
#line 248 "parser.y"
            {printf("!");}
#line 2326 "parser.tab.c"
    break;

  case 136: /* $@49: %empty  */
#line 249 "parser.y"
              {printf("-");}
#line 2332 "parser.tab.c"
    break;

  case 139: /* Const: INT_CONST  */
#line 253 "parser.y"
                       {printf("%s", (yyvsp[0].int_const));}
#line 2338 "parser.tab.c"
    break;

  case 140: /* Const: CHAR_CONST  */
#line 254 "parser.y"
                         {printf("%s", (yyvsp[0].char_const));}
#line 2344 "parser.tab.c"
    break;

  case 141: /* Const: STRING_CONST  */
#line 255 "parser.y"
                             {printf("%s", (yyvsp[0].string));}
#line 2350 "parser.tab.c"
    break;

  case 142: /* Const: REF_CONST  */
#line 256 "parser.y"
                  {printf("nil");}
#line 2356 "parser.tab.c"
    break;

  case 143: /* Const: TRUE  */
#line 257 "parser.y"
             {printf("tt");}
#line 2362 "parser.tab.c"
    break;

  case 144: /* Const: FALSE  */
#line 258 "parser.y"
              {printf("ff");}
#line 2368 "parser.tab.c"
    break;

  case 145: /* $@50: %empty  */
#line 261 "parser.y"
              {printf("while ");}
#line 2374 "parser.tab.c"
    break;

  case 146: /* $@51: %empty  */
#line 261 "parser.y"
                                                {printf(" do");}
#line 2380 "parser.tab.c"
    break;

  case 147: /* $@52: %empty  */
#line 261 "parser.y"
                                                                                {if (!need_tab) printf(" "); tab++;}
#line 2386 "parser.tab.c"
    break;

  case 148: /* $@53: %empty  */
#line 262 "parser.y"
                       {tab--;}
#line 2392 "parser.tab.c"
    break;

  case 149: /* $@54: %empty  */
#line 263 "parser.y"
        {print_tabs(tab);}
#line 2398 "parser.tab.c"
    break;

  case 150: /* LoopWithPreconditionStatement: WHILE $@50 Expression DO $@51 CheckIfNewLine $@52 CheckIfComment Body CheckIfNewLine $@53 CheckIfComment $@54 ENDWHILE  */
#line 263 "parser.y"
                                    {printf("endwhile");}
#line 2404 "parser.tab.c"
    break;

  case 151: /* $@55: %empty  */
#line 265 "parser.y"
            {printf("for ");}
#line 2410 "parser.tab.c"
    break;

  case 152: /* $@56: %empty  */
#line 265 "parser.y"
                                         {printf(" = ");}
#line 2416 "parser.tab.c"
    break;

  case 153: /* $@57: %empty  */
#line 265 "parser.y"
                                                                                   {printf(" to ");}
#line 2422 "parser.tab.c"
    break;

  case 154: /* $@58: %empty  */
#line 265 "parser.y"
                                                                                                                   {printf(" do");}
#line 2428 "parser.tab.c"
    break;

  case 155: /* $@59: %empty  */
#line 265 "parser.y"
                                                                                                                                                   {if (!need_tab) printf(" "); tab++;}
#line 2434 "parser.tab.c"
    break;

  case 156: /* $@60: %empty  */
#line 266 "parser.y"
                       {tab--;}
#line 2440 "parser.tab.c"
    break;

  case 157: /* $@61: %empty  */
#line 267 "parser.y"
        {print_tabs(tab);}
#line 2446 "parser.tab.c"
    break;

  case 158: /* LoopWithPreconditionStatement: FOR $@55 Var ASSIGN $@56 Expression ForHeadExt TO $@57 Expression DO $@58 CheckIfNewLine $@59 CheckIfComment Body CheckIfNewLine $@60 CheckIfComment $@61 ENDFOR  */
#line 267 "parser.y"
                                  {printf("endfor");}
#line 2452 "parser.tab.c"
    break;

  case 159: /* $@62: %empty  */
#line 270 "parser.y"
                  {printf(" -> ");}
#line 2458 "parser.tab.c"
    break;

  case 161: /* ForHeadExt: %empty  */
#line 271 "parser.y"
          {}
#line 2464 "parser.tab.c"
    break;

  case 162: /* $@63: %empty  */
#line 274 "parser.y"
               {printf("repeat ");}
#line 2470 "parser.tab.c"
    break;

  case 163: /* $@64: %empty  */
#line 274 "parser.y"
                                                   {if (!need_tab) printf(" "); tab++;}
#line 2476 "parser.tab.c"
    break;

  case 164: /* $@65: %empty  */
#line 275 "parser.y"
                       {tab--;}
#line 2482 "parser.tab.c"
    break;

  case 165: /* $@66: %empty  */
#line 276 "parser.y"
        {print_tabs(tab);}
#line 2488 "parser.tab.c"
    break;

  case 166: /* $@67: %empty  */
#line 276 "parser.y"
                                 {printf("until ");}
#line 2494 "parser.tab.c"
    break;


#line 2498 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, scanner, env, tab, need_tab, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner, env, tab, need_tab);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner, env, tab, need_tab);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, env, tab, need_tab, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner, env, tab, need_tab);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner, env, tab, need_tab);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 278 "parser.y"




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
