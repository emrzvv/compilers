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
  YYSYMBOL_ASSIGN = 29,                    /* ASSIGN  */
  YYSYMBOL_COMMA = 30,                     /* COMMA  */
  YYSYMBOL_NEW_LINE = 31,                  /* NEW_LINE  */
  YYSYMBOL_TRUE = 32,                      /* TRUE  */
  YYSYMBOL_FALSE = 33,                     /* FALSE  */
  YYSYMBOL_REF_CONST = 34,                 /* REF_CONST  */
  YYSYMBOL_TYPE_DECL = 35,                 /* TYPE_DECL  */
  YYSYMBOL_FUNC = 36,                      /* FUNC  */
  YYSYMBOL_ENDFUNC = 37,                   /* ENDFUNC  */
  YYSYMBOL_PROC = 38,                      /* PROC  */
  YYSYMBOL_ENDPROC = 39,                   /* ENDPROC  */
  YYSYMBOL_IF = 40,                        /* IF  */
  YYSYMBOL_ENDIF = 41,                     /* ENDIF  */
  YYSYMBOL_ELSE = 42,                      /* ELSE  */
  YYSYMBOL_ELSEIF = 43,                    /* ELSEIF  */
  YYSYMBOL_WHILE = 44,                     /* WHILE  */
  YYSYMBOL_DO = 45,                        /* DO  */
  YYSYMBOL_ENDWHILE = 46,                  /* ENDWHILE  */
  YYSYMBOL_REPEAT = 47,                    /* REPEAT  */
  YYSYMBOL_UNTIL = 48,                     /* UNTIL  */
  YYSYMBOL_FOR = 49,                       /* FOR  */
  YYSYMBOL_TO = 50,                        /* TO  */
  YYSYMBOL_ENDFOR = 51,                    /* ENDFOR  */
  YYSYMBOL_PASS = 52,                      /* PASS  */
  YYSYMBOL_VARNAME = 53,                   /* VARNAME  */
  YYSYMBOL_INT_CONST = 54,                 /* INT_CONST  */
  YYSYMBOL_CHAR_CONST = 55,                /* CHAR_CONST  */
  YYSYMBOL_STRING_CONST = 56,              /* STRING_CONST  */
  YYSYMBOL_COMMENT = 57,                   /* COMMENT  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_Program = 59,                   /* Program  */
  YYSYMBOL_60_1 = 60,                      /* $@1  */
  YYSYMBOL_61_2 = 61,                      /* $@2  */
  YYSYMBOL_Func = 62,                      /* Func  */
  YYSYMBOL_63_3 = 63,                      /* $@3  */
  YYSYMBOL_Proc = 64,                      /* Proc  */
  YYSYMBOL_65_4 = 65,                      /* $@4  */
  YYSYMBOL_CommentCheck = 66,              /* CommentCheck  */
  YYSYMBOL_67_5 = 67,                      /* $@5  */
  YYSYMBOL_NewLineCheck = 68,              /* NewLineCheck  */
  YYSYMBOL_ProcHeader = 69,                /* ProcHeader  */
  YYSYMBOL_70_6 = 70,                      /* $@6  */
  YYSYMBOL_71_7 = 71,                      /* $@7  */
  YYSYMBOL_72_8 = 72,                      /* $@8  */
  YYSYMBOL_FuncHeader = 73,                /* FuncHeader  */
  YYSYMBOL_74_9 = 74,                      /* $@9  */
  YYSYMBOL_75_10 = 75,                     /* $@10  */
  YYSYMBOL_76_11 = 76,                     /* $@11  */
  YYSYMBOL_77_12 = 77,                     /* $@12  */
  YYSYMBOL_78_13 = 78,                     /* $@13  */
  YYSYMBOL_Sections = 79,                  /* Sections  */
  YYSYMBOL_80_14 = 80,                     /* $@14  */
  YYSYMBOL_81_15 = 81,                     /* $@15  */
  YYSYMBOL_Section = 82,                   /* Section  */
  YYSYMBOL_83_16 = 83,                     /* $@16  */
  YYSYMBOL_Parameters = 84,                /* Parameters  */
  YYSYMBOL_85_17 = 85,                     /* $@17  */
  YYSYMBOL_Var = 86,                       /* Var  */
  YYSYMBOL_87_18 = 87,                     /* $@18  */
  YYSYMBOL_Type = 88,                      /* Type  */
  YYSYMBOL_89_19 = 89,                     /* $@19  */
  YYSYMBOL_PrimitiveType = 90,             /* PrimitiveType  */
  YYSYMBOL_Body = 91,                      /* Body  */
  YYSYMBOL_Statements = 92,                /* Statements  */
  YYSYMBOL_93_20 = 93,                     /* $@20  */
  YYSYMBOL_94_21 = 94,                     /* $@21  */
  YYSYMBOL_95_22 = 95,                     /* $@22  */
  YYSYMBOL_96_23 = 96,                     /* $@23  */
  YYSYMBOL_Statement = 97,                 /* Statement  */
  YYSYMBOL_98_24 = 98,                     /* $@24  */
  YYSYMBOL_DeclarationStatement = 99,      /* DeclarationStatement  */
  YYSYMBOL_100_25 = 100,                   /* $@25  */
  YYSYMBOL_VarDeclarations = 101,          /* VarDeclarations  */
  YYSYMBOL_102_26 = 102,                   /* $@26  */
  YYSYMBOL_VarDeclaration = 103,           /* VarDeclaration  */
  YYSYMBOL_104_27 = 104,                   /* $@27  */
  YYSYMBOL_FunctionCallStatement = 105,    /* FunctionCallStatement  */
  YYSYMBOL_106_28 = 106,                   /* $@28  */
  YYSYMBOL_Args = 107,                     /* Args  */
  YYSYMBOL_108_29 = 108,                   /* $@29  */
  YYSYMBOL_ArrayCall = 109,                /* ArrayCall  */
  YYSYMBOL_110_30 = 110,                   /* $@30  */
  YYSYMBOL_Spec = 111,                     /* Spec  */
  YYSYMBOL_112_31 = 112,                   /* $@31  */
  YYSYMBOL_113_32 = 113,                   /* $@32  */
  YYSYMBOL_114_33 = 114,                   /* $@33  */
  YYSYMBOL_115_34 = 115,                   /* $@34  */
  YYSYMBOL_Expression = 116,               /* Expression  */
  YYSYMBOL_117_35 = 117,                   /* $@35  */
  YYSYMBOL_118_36 = 118,                   /* $@36  */
  YYSYMBOL_LogicalExpression = 119,        /* LogicalExpression  */
  YYSYMBOL_120_37 = 120,                   /* $@37  */
  YYSYMBOL_CompareExpression = 121,        /* CompareExpression  */
  YYSYMBOL_CompareOperator = 122,          /* CompareOperator  */
  YYSYMBOL_ArithmeticExpression = 123,     /* ArithmeticExpression  */
  YYSYMBOL_AdditiveOperator = 124,         /* AdditiveOperator  */
  YYSYMBOL_MultiplicativeExpression = 125, /* MultiplicativeExpression  */
  YYSYMBOL_MultiplicativeOperator = 126,   /* MultiplicativeOperator  */
  YYSYMBOL_127_38 = 127,                   /* $@38  */
  YYSYMBOL_128_39 = 128,                   /* $@39  */
  YYSYMBOL_Term = 129,                     /* Term  */
  YYSYMBOL_130_40 = 130,                   /* $@40  */
  YYSYMBOL_Factor = 131,                   /* Factor  */
  YYSYMBOL_132_41 = 132,                   /* $@41  */
  YYSYMBOL_133_42 = 133,                   /* $@42  */
  YYSYMBOL_Const = 134                     /* Const  */
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

#line 256 "parser.tab.c"


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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   140

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   312


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
      55,    56,    57
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    71,    71,    70,    79,    78,    86,    88,    91,    91,
      94,    94,    95,    96,    96,    99,   100,   104,   105,   105,
     104,   109,   110,   110,   111,   111,   109,   119,   119,   119,
     120,   123,   123,   128,   130,   130,   133,   133,   136,   138,
     138,   141,   141,   141,   144,   147,   147,   149,   149,   149,
     149,   152,   159,   159,   162,   162,   165,   166,   166,   168,
     169,   169,   172,   172,   175,   176,   176,   178,   178,   180,
     181,   181,   181,   182,   182,   182,   183,   184,   185,   188,
     189,   189,   190,   190,   193,   194,   194,   196,   197,   200,
     201,   202,   203,   204,   205,   208,   209,   211,   212,   215,
     216,   219,   220,   219,   224,   225,   225,   228,   228,   229,
     229,   230,   233,   234,   235,   236,   237,   238
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
  "STATEMENT_END", "CHECK", "ASSIGN", "COMMA", "NEW_LINE", "TRUE", "FALSE",
  "REF_CONST", "TYPE_DECL", "FUNC", "ENDFUNC", "PROC", "ENDPROC", "IF",
  "ENDIF", "ELSE", "ELSEIF", "WHILE", "DO", "ENDWHILE", "REPEAT", "UNTIL",
  "FOR", "TO", "ENDFOR", "PASS", "VARNAME", "INT_CONST", "CHAR_CONST",
  "STRING_CONST", "COMMENT", "$accept", "Program", "$@1", "$@2", "Func",
  "$@3", "Proc", "$@4", "CommentCheck", "$@5", "NewLineCheck",
  "ProcHeader", "$@6", "$@7", "$@8", "FuncHeader", "$@9", "$@10", "$@11",
  "$@12", "$@13", "Sections", "$@14", "$@15", "Section", "$@16",
  "Parameters", "$@17", "Var", "$@18", "Type", "$@19", "PrimitiveType",
  "Body", "Statements", "$@20", "$@21", "$@22", "$@23", "Statement",
  "$@24", "DeclarationStatement", "$@25", "VarDeclarations", "$@26",
  "VarDeclaration", "$@27", "FunctionCallStatement", "$@28", "Args",
  "$@29", "ArrayCall", "$@30", "Spec", "$@31", "$@32", "$@33", "$@34",
  "Expression", "$@35", "$@36", "LogicalExpression", "$@37",
  "CompareExpression", "CompareOperator", "ArithmeticExpression",
  "AdditiveOperator", "MultiplicativeExpression", "MultiplicativeOperator",
  "$@38", "$@39", "Term", "$@40", "Factor", "$@41", "$@42", "Const", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-5)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -10,   -32,   -26,     6,  -107,  -107,     4,     4,  -107,  -107,
    -107,  -107,    10,  -107,  -107,     4,     4,   -15,   -15,   -15,
     -15,   -15,   -15,  -107,    32,    28,  -107,  -107,    36,    47,
       4,  -107,  -107,    37,    42,    -9,    38,  -107,  -107,   -15,
    -107,  -107,  -107,  -107,    48,  -107,  -107,   -23,  -107,  -107,
      35,    35,  -107,     4,    18,     4,  -107,  -107,  -107,    62,
    -107,    -5,  -107,    62,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,    63,  -107,  -107,  -107,  -107,  -107,  -107,    69,    30,
    -107,    97,  -107,    34,  -107,    78,  -107,   -15,    18,    35,
      56,  -107,    72,  -107,  -107,    73,   -15,    31,    31,    56,
      56,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,    18,  -107,  -107,  -107,    18,    18,  -107,  -107,
      30,  -107,  -107,  -107,  -107,  -107,  -107,  -107,     4,  -107,
      35,    56,  -107,  -107,    69,    69,    43,    44,    18,    18,
      18,    18,    18,  -107,    81,    84,  -107,    18,    56,   -15,
      65,  -107,  -107,    -9,  -107,  -107,    -1,    30,    20,  -107,
    -107,   103,  -107,  -107,    92,  -107,  -107,  -107,    93,    94,
    -107,  -107,  -107,   102,  -107,    35,    56,  -107,  -107,    18,
    -107,  -107,  -107,    30
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    16,     6,     7,    16,    16,    21,    17,
       1,    15,     2,    10,     8,    16,    16,    12,    12,    12,
      12,    12,    12,    13,     0,     0,    45,    45,     0,     0,
      16,     3,     5,     0,    44,     0,     0,    22,    18,    12,
      11,    47,    52,    36,    59,    46,    51,     0,    56,     9,
       0,     0,    14,    16,     0,    16,    60,    57,    54,    23,
      30,     0,    33,    19,    48,   109,   107,    70,   116,   117,
     115,    36,   112,   113,   114,    76,    69,    77,   111,    53,
      79,    84,    87,    95,    99,   104,    78,    12,     0,     0,
       0,    27,     0,    34,    31,     0,    12,     0,     0,     0,
       0,    62,    67,    80,    82,    85,    89,    90,    91,    93,
      92,    94,     0,    97,    98,   101,     0,     0,   105,    37,
      61,    58,    39,    41,    42,    43,    55,    38,    16,    24,
       0,     0,    20,    49,   110,   108,     0,     0,     0,     0,
       0,     0,     0,    88,     0,    96,   100,     0,     0,    12,
       0,    35,    32,     0,    71,    74,     0,    64,     0,    81,
      83,    86,   102,   106,     0,    28,    25,    50,     0,     0,
      63,    65,    68,     0,    40,     0,     0,    72,    75,     0,
     103,    29,    26,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -107,  -107,  -107,  -107,    96,  -107,    98,  -107,   -17,  -107,
       2,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,    70,  -107,  -107,   -53,  -107,  -107,  -107,   -35,  -107,
     -86,  -107,  -107,    99,  -107,  -107,  -107,  -107,  -107,   -29,
    -107,  -107,  -107,  -107,  -107,    39,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,   -59,  -107,  -107,  -107,  -107,   -78,  -107,
    -107,   -82,  -107,   -13,  -107,    13,  -107,    11,  -107,  -107,
    -107,  -106,  -107,  -107,  -107,  -107,  -107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,    17,    18,     4,    20,     5,    19,    24,    30,
      12,     6,    16,    51,    95,     7,    15,    50,    92,   150,
     176,    59,   128,   175,    60,   131,    61,   130,    75,    55,
     126,   148,   127,    33,    34,    35,    53,    96,   153,    45,
      54,    46,    90,    47,    89,    48,    88,    76,   138,   156,
     179,    77,   139,    78,    99,   168,   100,   169,    79,   140,
     141,    80,   142,    81,   112,    82,   116,    83,   117,   144,
     173,    84,   147,    85,    98,    97,    86
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,    25,    26,    27,    28,    29,    10,    57,    13,    14,
     120,   146,    58,   136,   137,    62,    62,    21,    22,    42,
     170,     8,    52,   103,   104,    93,     1,     9,     2,   171,
      94,    65,    39,   103,   104,    11,    66,    11,   134,   135,
      67,   163,    23,   172,    43,   152,   113,   114,    -4,   115,
      68,    69,    70,    67,    44,    64,    37,    87,   159,   160,
     157,   158,   164,    68,    69,    70,     2,    38,     1,    41,
     119,    71,    72,    73,    74,    49,    40,    56,   122,   133,
     123,   124,   125,   101,    71,    72,    73,    74,    43,    91,
     182,   102,   118,   129,   132,   151,   154,   162,   155,   115,
     166,   183,   105,   106,   107,   108,   109,   110,   111,   106,
     107,   108,   109,   110,   111,   174,   177,   178,    44,   180,
      31,    63,   181,    32,   167,   143,    36,   145,   121,   161,
     149,     0,   165,     0,     0,     0,     0,     0,     0,     0,
      62
};

static const yytype_int16 yycheck[] =
{
      35,    18,    19,    20,    21,    22,     0,    30,     6,     7,
      88,   117,    35,    99,   100,    50,    51,    15,    16,    28,
      21,    53,    39,     3,     4,    30,    36,    53,    38,    30,
      35,    13,    30,     3,     4,    31,    18,    31,    97,    98,
      22,   147,    57,    23,    53,   131,    12,    13,    38,    15,
      32,    33,    34,    22,    89,    53,    20,    55,   140,   141,
     138,   139,   148,    32,    33,    34,    38,    20,    36,    27,
      87,    53,    54,    55,    56,    37,    39,    29,    22,    96,
      24,    25,    26,    20,    53,    54,    55,    56,    53,    27,
     176,    22,    14,    21,    21,   130,    53,    16,    54,    15,
      35,   179,     5,     6,     7,     8,     9,    10,    11,     6,
       7,     8,     9,    10,    11,    23,    23,    23,   153,    17,
      24,    51,   175,    25,   153,   112,    27,   116,    89,   142,
     128,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     175
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    38,    59,    62,    64,    69,    73,    53,    53,
       0,    31,    68,    68,    68,    74,    70,    60,    61,    65,
      63,    68,    68,    57,    66,    66,    66,    66,    66,    66,
      67,    62,    64,    91,    92,    93,    91,    20,    20,    68,
      39,    27,    28,    53,    86,    97,    99,   101,   103,    37,
      75,    71,    66,    94,    98,    87,    29,    30,    35,    79,
      82,    84,    86,    79,    68,    13,    18,    22,    32,    33,
      34,    53,    54,    55,    56,    86,   105,   109,   111,   116,
     119,   121,   123,   125,   129,   131,   134,    68,   104,   102,
     100,    27,    76,    30,    35,    72,    95,   133,   132,   112,
     114,    20,    22,     3,     4,     5,     6,     7,     8,     9,
      10,    11,   122,    12,    13,    15,   124,   126,    14,    66,
     116,   103,    22,    24,    25,    26,    88,    90,    80,    21,
      85,    83,    21,    66,   111,   111,    88,    88,   106,   110,
     117,   118,   120,   123,   127,   125,   129,   130,    89,    68,
      77,    86,    88,    96,    53,    54,   107,   116,   116,   119,
     119,   121,    16,   129,    88,    66,    35,    97,   113,   115,
      21,    30,    23,   128,    23,    81,    78,    23,    23,   108,
      17,    82,    88,   116
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    60,    59,    61,    59,    59,    59,    63,    62,
      65,    64,    66,    67,    66,    68,    68,    70,    71,    72,
      69,    74,    75,    76,    77,    78,    73,    80,    81,    79,
      79,    83,    82,    84,    85,    84,    87,    86,    88,    89,
      88,    90,    90,    90,    91,    93,    92,    94,    95,    96,
      92,    97,    98,    97,   100,    99,   101,   102,   101,   103,
     104,   103,   106,   105,   107,   108,   107,   110,   109,   111,
     112,   113,   111,   114,   115,   111,   111,   111,   111,   116,
     117,   116,   118,   116,   119,   120,   119,   121,   121,   122,
     122,   122,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   127,   128,   126,   129,   130,   129,   132,   131,   133,
     131,   131,   134,   134,   134,   134,   134,   134
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     5,     0,     5,     1,     1,     0,     6,
       0,     6,     0,     0,     4,     1,     0,     0,     0,     0,
      10,     0,     0,     0,     0,     0,    14,     0,     0,     7,
       1,     0,     4,     1,     0,     4,     0,     4,     1,     0,
       4,     1,     1,     1,     1,     0,     2,     0,     0,     0,
       8,     1,     0,     3,     0,     4,     1,     0,     4,     1,
       0,     4,     0,     5,     1,     0,     4,     0,     5,     1,
       0,     0,     6,     0,     0,     6,     1,     1,     1,     1,
       0,     4,     0,     4,     1,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
       3,     0,     0,     5,     1,     0,     4,     0,     3,     0,
       3,     1,     1,     1,     1,     1,     1,     1
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
  case 2: /* $@1: %empty  */
#line 71 "parser.y"
                     {
            printf("\n"); 
            tab=0;
        }
#line 1757 "parser.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 79 "parser.y"
                     {
            printf("\n"); 
            tab=0;
        }
#line 1766 "parser.tab.c"
    break;

  case 8: /* $@3: %empty  */
#line 91 "parser.y"
                                {if (!need_tab) printf(" "); tab++;}
#line 1772 "parser.tab.c"
    break;

  case 9: /* Func: FuncHeader NewLineCheck $@3 CommentCheck Body ENDFUNC  */
#line 91 "parser.y"
                                                                                               {printf("endfunc");}
#line 1778 "parser.tab.c"
    break;

  case 10: /* $@4: %empty  */
#line 94 "parser.y"
                                {if (!need_tab) printf(" "); tab++;}
#line 1784 "parser.tab.c"
    break;

  case 11: /* Proc: ProcHeader NewLineCheck $@4 CommentCheck Body ENDPROC  */
#line 94 "parser.y"
                                                                                               {printf("endproc");}
#line 1790 "parser.tab.c"
    break;

  case 13: /* $@5: %empty  */
#line 96 "parser.y"
                  {if (need_tab) { print_tabs(tab); need_tab = false;} printf("%s", (yyvsp[0].comment));}
#line 1796 "parser.tab.c"
    break;

  case 15: /* NewLineCheck: NEW_LINE  */
#line 99 "parser.y"
                 {need_tab=true; /*printf("\nneed tab: %d\n", need_tab);*/}
#line 1802 "parser.tab.c"
    break;

  case 16: /* NewLineCheck: %empty  */
#line 100 "parser.y"
          {need_tab = false; /*printf("\nneed tab: %d\n", need_tab);*/}
#line 1808 "parser.tab.c"
    break;

  case 17: /* $@6: %empty  */
#line 104 "parser.y"
                           {printf("proc %s", (yyvsp[0].varname));}
#line 1814 "parser.tab.c"
    break;

  case 18: /* $@7: %empty  */
#line 105 "parser.y"
                                {printf("(");}
#line 1820 "parser.tab.c"
    break;

  case 19: /* $@8: %empty  */
#line 105 "parser.y"
                                                        {if (need_tab) {tab=1; print_tabs(tab);}}
#line 1826 "parser.tab.c"
    break;

  case 20: /* ProcHeader: PROC VARNAME $@6 NewLineCheck CommentCheck L_BRACKET_ROUND $@7 Sections $@8 R_BRACKET_ROUND  */
#line 106 "parser.y"
                                {printf(")");}
#line 1832 "parser.tab.c"
    break;

  case 21: /* $@9: %empty  */
#line 109 "parser.y"
                           {printf("func %s", (yyvsp[0].varname));}
#line 1838 "parser.tab.c"
    break;

  case 22: /* $@10: %empty  */
#line 110 "parser.y"
                                {printf("(");}
#line 1844 "parser.tab.c"
    break;

  case 23: /* $@11: %empty  */
#line 110 "parser.y"
                                                        {if (need_tab) {tab=1; print_tabs(tab);}}
#line 1850 "parser.tab.c"
    break;

  case 24: /* $@12: %empty  */
#line 111 "parser.y"
                                {printf(")");}
#line 1856 "parser.tab.c"
    break;

  case 25: /* $@13: %empty  */
#line 111 "parser.y"
                                                         {printf(" -> ");}
#line 1862 "parser.tab.c"
    break;

  case 27: /* $@14: %empty  */
#line 119 "parser.y"
                               {printf("; ");}
#line 1868 "parser.tab.c"
    break;

  case 28: /* $@15: %empty  */
#line 119 "parser.y"
                                                                         {if (need_tab) {tab=1; print_tabs(tab);}}
#line 1874 "parser.tab.c"
    break;

  case 31: /* $@16: %empty  */
#line 123 "parser.y"
                             {if (need_tab) {tab=1; print_tabs(tab); tab=0;} printf(" -> ");}
#line 1880 "parser.tab.c"
    break;

  case 34: /* $@17: %empty  */
#line 130 "parser.y"
                         {printf(", ");}
#line 1886 "parser.tab.c"
    break;

  case 36: /* $@18: %empty  */
#line 133 "parser.y"
                      {printf("%s", (yyvsp[0].varname));}
#line 1892 "parser.tab.c"
    break;

  case 39: /* $@19: %empty  */
#line 138 "parser.y"
                         {printf("[");}
#line 1898 "parser.tab.c"
    break;

  case 40: /* Type: L_BRACKET_SQUARE $@19 Type R_BRACKET_SQUARE  */
#line 138 "parser.y"
                                                              {printf("]");}
#line 1904 "parser.tab.c"
    break;

  case 41: /* PrimitiveType: INT  */
#line 141 "parser.y"
            {printf("int");}
#line 1910 "parser.tab.c"
    break;

  case 42: /* PrimitiveType: CHAR  */
#line 141 "parser.y"
                                    {printf("char");}
#line 1916 "parser.tab.c"
    break;

  case 43: /* PrimitiveType: BOOL  */
#line 141 "parser.y"
                                                             {printf("bool");}
#line 1922 "parser.tab.c"
    break;

  case 45: /* $@20: %empty  */
#line 147 "parser.y"
        {if (need_tab) {print_tabs(tab);}}
#line 1928 "parser.tab.c"
    break;

  case 47: /* $@21: %empty  */
#line 149 "parser.y"
                                 {printf(";");}
#line 1934 "parser.tab.c"
    break;

  case 48: /* $@22: %empty  */
#line 149 "parser.y"
                                                             {if (!need_tab) {printf(" ");}}
#line 1940 "parser.tab.c"
    break;

  case 49: /* $@23: %empty  */
#line 149 "parser.y"
                                                                                                          {if (!need_tab) {printf(" ");} else {print_tabs(tab);}}
#line 1946 "parser.tab.c"
    break;

  case 52: /* $@24: %empty  */
#line 159 "parser.y"
              {printf("check");}
#line 1952 "parser.tab.c"
    break;

  case 54: /* $@25: %empty  */
#line 162 "parser.y"
                                  {printf(" -> ");}
#line 1958 "parser.tab.c"
    break;

  case 57: /* $@26: %empty  */
#line 166 "parser.y"
                              {printf(", ");}
#line 1964 "parser.tab.c"
    break;

  case 60: /* $@27: %empty  */
#line 169 "parser.y"
                   {printf(" = ");}
#line 1970 "parser.tab.c"
    break;

  case 62: /* $@28: %empty  */
#line 172 "parser.y"
                                      {printf("(");}
#line 1976 "parser.tab.c"
    break;

  case 63: /* FunctionCallStatement: VARNAME L_BRACKET_ROUND $@28 Args R_BRACKET_ROUND  */
#line 172 "parser.y"
                                                                          {printf(")");}
#line 1982 "parser.tab.c"
    break;

  case 65: /* $@29: %empty  */
#line 176 "parser.y"
                   {printf(", ");}
#line 1988 "parser.tab.c"
    break;

  case 67: /* $@30: %empty  */
#line 178 "parser.y"
                              {printf("[");}
#line 1994 "parser.tab.c"
    break;

  case 68: /* ArrayCall: Spec L_BRACKET_SQUARE $@30 Expression R_BRACKET_SQUARE  */
#line 178 "parser.y"
                                                                         {printf("]");}
#line 2000 "parser.tab.c"
    break;

  case 70: /* $@31: %empty  */
#line 181 "parser.y"
                         {printf("[");}
#line 2006 "parser.tab.c"
    break;

  case 71: /* $@32: %empty  */
#line 181 "parser.y"
                                                           {printf(" %s", (yyvsp[0].varname));}
#line 2012 "parser.tab.c"
    break;

  case 72: /* Spec: L_BRACKET_SQUARE $@31 Type VARNAME $@32 R_BRACKET_SQUARE  */
#line 181 "parser.y"
                                                                                                    {printf("]");}
#line 2018 "parser.tab.c"
    break;

  case 73: /* $@33: %empty  */
#line 182 "parser.y"
                         {printf("[");}
#line 2024 "parser.tab.c"
    break;

  case 74: /* $@34: %empty  */
#line 182 "parser.y"
                                                            {printf(" %s", (yyvsp[0].int_const));}
#line 2030 "parser.tab.c"
    break;

  case 75: /* Spec: L_BRACKET_SQUARE $@33 Type INT_CONST $@34 R_BRACKET_SQUARE  */
#line 182 "parser.y"
                                                                                                    {printf("]");}
#line 2036 "parser.tab.c"
    break;

  case 80: /* $@35: %empty  */
#line 189 "parser.y"
                      {printf(" || ");}
#line 2042 "parser.tab.c"
    break;

  case 82: /* $@36: %empty  */
#line 190 "parser.y"
                       {printf(" ^^ ");}
#line 2048 "parser.tab.c"
    break;

  case 85: /* $@37: %empty  */
#line 194 "parser.y"
                              {printf(" && ");}
#line 2054 "parser.tab.c"
    break;

  case 89: /* CompareOperator: EQ  */
#line 200 "parser.y"
           {printf(" == ");}
#line 2060 "parser.tab.c"
    break;

  case 90: /* CompareOperator: NE  */
#line 201 "parser.y"
           {printf(" != ");}
#line 2066 "parser.tab.c"
    break;

  case 91: /* CompareOperator: LT  */
#line 202 "parser.y"
           {printf(" < ");}
#line 2072 "parser.tab.c"
    break;

  case 92: /* CompareOperator: LE  */
#line 203 "parser.y"
           {printf(" <= ");}
#line 2078 "parser.tab.c"
    break;

  case 93: /* CompareOperator: GT  */
#line 204 "parser.y"
           {printf(" > ");}
#line 2084 "parser.tab.c"
    break;

  case 94: /* CompareOperator: GE  */
#line 205 "parser.y"
           {printf(" >= ");}
#line 2090 "parser.tab.c"
    break;

  case 97: /* AdditiveOperator: PLUS  */
#line 211 "parser.y"
             {printf(" + ");}
#line 2096 "parser.tab.c"
    break;

  case 98: /* AdditiveOperator: MINUS  */
#line 212 "parser.y"
              {printf(" - ");}
#line 2102 "parser.tab.c"
    break;

  case 101: /* $@38: %empty  */
#line 219 "parser.y"
            {printf(" * ");}
#line 2108 "parser.tab.c"
    break;

  case 102: /* $@39: %empty  */
#line 220 "parser.y"
            {printf(" / ");}
#line 2114 "parser.tab.c"
    break;

  case 103: /* MultiplicativeOperator: MUL $@38 DIV $@39 MOD  */
#line 221 "parser.y"
            {printf(" % ");}
#line 2120 "parser.tab.c"
    break;

  case 105: /* $@40: %empty  */
#line 225 "parser.y"
                   {printf(" ^ ");}
#line 2126 "parser.tab.c"
    break;

  case 107: /* $@41: %empty  */
#line 228 "parser.y"
            {printf("!");}
#line 2132 "parser.tab.c"
    break;

  case 109: /* $@42: %empty  */
#line 229 "parser.y"
              {printf("-");}
#line 2138 "parser.tab.c"
    break;

  case 112: /* Const: INT_CONST  */
#line 233 "parser.y"
                       {printf("%s", (yyvsp[0].int_const));}
#line 2144 "parser.tab.c"
    break;

  case 113: /* Const: CHAR_CONST  */
#line 234 "parser.y"
                         {printf("%s", (yyvsp[0].char_const));}
#line 2150 "parser.tab.c"
    break;

  case 114: /* Const: STRING_CONST  */
#line 235 "parser.y"
                             {printf("%s", (yyvsp[0].string));}
#line 2156 "parser.tab.c"
    break;

  case 115: /* Const: REF_CONST  */
#line 236 "parser.y"
                  {printf("nil");}
#line 2162 "parser.tab.c"
    break;

  case 116: /* Const: TRUE  */
#line 237 "parser.y"
             {printf("tt");}
#line 2168 "parser.tab.c"
    break;

  case 117: /* Const: FALSE  */
#line 238 "parser.y"
              {printf("ff");}
#line 2174 "parser.tab.c"
    break;


#line 2178 "parser.tab.c"

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

#line 240 "parser.y"




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
