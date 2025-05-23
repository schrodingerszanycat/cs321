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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "ll1.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// --- Constants and Type Definitions ---
#define MAX_RULE_SYMBOLS 10
#define MAX_TOKENS 10
#define MAX_PRODUCTION_DISPLAY_LENGTH 100
#define MAX_NAME_LENGTH 20
#define INVALID_LOOKUP -1

typedef enum {
    EXPR,
    EXPR_PRIME,
    TERM,
    TERM_PRIME,
    FACTOR,
    NUM_NONTERMINALS
} GrammarSymbol;

typedef enum{
    VAR_INDEX,
    PLUS_INDEX,
    STAR_INDEX,
    OPEN_INDEX,
    CLOSE_INDEX,
    END_INDEX,
    EMPTY_INDEX,
    NUM_TERMINALS_ENUM
} TokenIndex;

typedef struct ProductionRule {
    GrammarSymbol leftSide;
    char* rightSide[MAX_RULE_SYMBOLS];
    int rightSideLength;
} ProductionRule;

typedef struct StackNode {
    char *symbol;
    struct StackNode *next;
} StackNode;


// --- Global Variables ---
ProductionRule grammar[] = {
    {EXPR, {"TERM", "EXPR'", NULL}, 2},
    {EXPR_PRIME, {"PLUS", "TERM", "EXPR'", NULL}, 3},
    {EXPR_PRIME, {"EMPTY", NULL}, 1},
    {TERM, {"FACTOR", "TERM'", NULL}, 2},
    {TERM_PRIME, {"STAR", "FACTOR", "TERM'", NULL}, 3},
    {TERM_PRIME, {"EMPTY", NULL}, 1},
    {FACTOR, {"OPEN", "EXPR", "CLOSE", NULL}, 3},
    {FACTOR, {"VAR", NULL}, 1},
    {FACTOR, {NULL}, 0} // Sentinel
};

char *parseTable[NUM_NONTERMINALS][MAX_TOKENS];
char *tokens[] = {"VAR", "PLUS", "STAR", "OPEN", "CLOSE", "END", "EMPTY", NULL};

char *firstSet[NUM_NONTERMINALS][MAX_TOKENS];
char *followSet[NUM_NONTERMINALS][MAX_TOKENS];

StackNode *stack = NULL;

// --- Function Declarations ---
void initializeSymbolSets();
void clearParseTable();
void releaseMemory();
void safeStringCopy(char** destination, const char* source, const char* context);

void calculateFirstSets();
void calculateFollowSets();
void constructParseTable();
void displayParseTable();

int getTokenIndex(const char *token);
GrammarSymbol getGrammarSymbol(const char *nonTerminal);
bool isNonTerminal(const char* symbol);

char* getProductionRuleString(int ruleIndex);
void stackPush(const char *symbol);
char *stackPop();
bool isStackEmpty();
void releaseStack();
void analyzeInput();
void reportError(const char *message);

int resetLexer();
TokenIndex getTokenTypeIndex(int tokenType);

extern int yylex();
extern char *yytext;

// --- Reset Mechanism ---
int parseDoneFlag = 0;


#line 171 "ll1.tab.c"

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

#include "ll1.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VAR = 3,                        /* VAR  */
  YYSYMBOL_PLUS = 4,                       /* PLUS  */
  YYSYMBOL_STAR = 5,                       /* STAR  */
  YYSYMBOL_OPEN = 6,                       /* OPEN  */
  YYSYMBOL_CLOSE = 7,                      /* CLOSE  */
  YYSYMBOL_END = 8,                        /* END  */
  YYSYMBOL_END_OF_INPUT = 9,               /* END_OF_INPUT  */
  YYSYMBOL_YYACCEPT = 10,                  /* $accept  */
  YYSYMBOL_program = 11                    /* program  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   0

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  10
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  2
/* YYNRULES -- Number of rules.  */
#define YYNRULES  2
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  3

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   264


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
       5,     6,     7,     8,     9
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,   114,   114
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VAR", "PLUS", "STAR",
  "OPEN", "CLOSE", "END", "END_OF_INPUT", "$accept", "program", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-1)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -1,     0,    -1
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -1,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       2
};

static const yytype_int8 yycheck[] =
{
       0
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    11,     0
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    10,    11
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: %empty  */
#line 114 "ll1.y"
           {
            initializeSymbolSets();
            clearParseTable();

            calculateFirstSets();
            calculateFollowSets();
            constructParseTable();
            displayParseTable();

            while(1){
                analyzeInput();
                if (parseDoneFlag) {
                    resetLexer();
                }
            }
           }
#line 1171 "ll1.tab.c"
    break;


#line 1175 "ll1.tab.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 131 "ll1.y"


// --- Function Definitions ---

void initializeSymbolSets() {
    // Initialize first and follow sets to NULL
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < MAX_TOKENS; j++) {
            firstSet[i][j] = NULL;
            followSet[i][j] = NULL;
        }
    }
}

void clearParseTable() {
    // Initialize parsing table to NULL
    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        for (int j = 0; j < MAX_TOKENS; j++) {
            parseTable[i][j] = NULL;
        }
    }
}

void safeStringCopy(char** destination, const char* source, const char* context) {
    *destination = strdup(source);
    if (*destination == NULL) {
        fprintf(stderr, "Memory allocation error (strdup) in %s!\n", context);
        exit(EXIT_FAILURE);
    }
}

void calculateFirstSets() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; grammar[i].rightSideLength != 0 ; i++) { // Use rightSideLength
            ProductionRule *rule = &grammar[i];

            //Rule 1: If X is a terminal, FIRST(X) = {X}
            if(!isNonTerminal(rule->rightSide[0])){
                int terminalIndex = getTokenIndex(rule->rightSide[0]);
                if(firstSet[rule->leftSide][terminalIndex] == NULL){
                     safeStringCopy(&firstSet[rule->leftSide][terminalIndex], rule->rightSide[0], "calculateFirstSets");
                     changed = true;
                }
            } else {
                //Rule 2: If X->EMPTY, add EMPTY to FIRST(X)
                if(strcmp(rule->rightSide[0], "EMPTY")==0){
                    int emptyIndex = getTokenIndex("EMPTY");
                    if(firstSet[rule->leftSide][emptyIndex] == NULL){
                        safeStringCopy(&firstSet[rule->leftSide][emptyIndex], "EMPTY", "calculateFirstSets");
                        changed = true;
                    }
                } else {
                    //Rule 3: If X is a non-terminal, and X-> Y1 Y2...Yk
                    int k=0;
                    while(rule->rightSide[k]!=NULL){
                        if(!isNonTerminal(rule->rightSide[k])){
                            int terminalIndex = getTokenIndex(rule->rightSide[k]);
                            if(firstSet[rule->leftSide][terminalIndex] == NULL){
                                safeStringCopy(&firstSet[rule->leftSide][terminalIndex], rule->rightSide[k], "calculateFirstSets");
                                changed = true;
                            }
                            break; //No more processing.
                        }

                        GrammarSymbol Y = getGrammarSymbol(rule->rightSide[k]);

                        //Add all of FIRST(Yi) except EMPTY
                        for(int j=0; j<MAX_TOKENS; ++j){
                            if(firstSet[Y][j] != NULL && strcmp(firstSet[Y][j], "EMPTY") != 0){
                                if(firstSet[rule->leftSide][j] == NULL){
                                     safeStringCopy(&firstSet[rule->leftSide][j], firstSet[Y][j], "calculateFirstSets");
                                     changed = true;
                                }
                            }
                        }

                        //If FIRST(Yi) does not contain empty, stop.
                        if(firstSet[Y][getTokenIndex("EMPTY")] == NULL) break;

                        k++;
                        //if all Y1...Yk have EMPTY in FIRST, add EMPTY to FIRST(X)
                        if(rule->rightSide[k] == NULL && firstSet[Y][getTokenIndex("EMPTY")] != NULL){
                             if(firstSet[rule->leftSide][getTokenIndex("EMPTY")] == NULL){
                                 safeStringCopy(&firstSet[rule->leftSide][getTokenIndex("EMPTY")], "EMPTY", "calculateFirstSets");
                                 changed = true;
                             }
                        }
                    }
                }
            }
        }
    }
}

void calculateFollowSets() {
    // Rule 1: FOLLOW(S) = {$}
    safeStringCopy(&followSet[EXPR][getTokenIndex("END")], "END", "calculateFollowSets");

    bool changed = true;
    while(changed){
        changed = false;

        for(int i=0; grammar[i].rightSideLength != 0; ++i){ // Use rightSideLength
            ProductionRule *rule = &grammar[i];
            //Iterate through symbols on RHS.
            for(int j=0; j<rule->rightSideLength; ++j){
                if(isNonTerminal(rule->rightSide[j])){
                    GrammarSymbol B = getGrammarSymbol(rule->rightSide[j]);

                    //Rule 2: If A->alpha B beta, FOLLOW(B) = {FIRST(beta) - EMPTY}
                    int k = j+1;
                    while(rule->rightSide[k] != NULL){ //While there is a beta
                        if(!isNonTerminal(rule->rightSide[k])){ //If beta is terminal
                            int terminalIndex = getTokenIndex(rule->rightSide[k]);
                            if(followSet[B][terminalIndex] == NULL){
                                 safeStringCopy(&followSet[B][terminalIndex], rule->rightSide[k], "calculateFollowSets");
                                 changed = true;
                            }
                            break; //No more processing of beta
                        }

                        GrammarSymbol beta = getGrammarSymbol(rule->rightSide[k]);

                        for(int m=0; m<MAX_TOKENS; ++m){
                             if(firstSet[beta][m] != NULL && strcmp(firstSet[beta][m], "EMPTY") !=0){ //Add FIRST(beta) - EMPTY
                                if(followSet[B][m] == NULL){
                                    safeStringCopy(&followSet[B][m], firstSet[beta][m], "calculateFollowSets");
                                    changed = true;
                                }
                             }
                        }
                        //If EMPTY not in FIRST(beta), stop.
                        if(firstSet[beta][getTokenIndex("EMPTY")] == NULL) break;
                        k++;
                    }
                    //Rule 3: If A->alpha B or A->alpha B beta where EMPTY is in FIRST(beta), FOLLOW(B) = FOLLOW(B) U FOLLOW(A)
                    if(rule->rightSide[k] == NULL){ //If beta is empty or all beta have empty
                        GrammarSymbol A = rule->leftSide;
                        for(int m=0; m<MAX_TOKENS; ++m){
                            if(followSet[A][m] != NULL){ //Everything in FOLLOW(A) is in FOLLOW(B)
                                if(followSet[B][m] == NULL){
                                    safeStringCopy(&followSet[B][m], followSet[A][m], "calculateFollowSets");
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void constructParseTable() {
    // Iterate through productions
    for (int i = 0; grammar[i].rightSideLength != 0; i++) {  // Use rightSideLength
        ProductionRule *rule = &grammar[i];
        GrammarSymbol A = rule->leftSide;

        // Rule 1: For each terminal a in FIRST(alpha), add A -> alpha to M[A, a]
        //Process RHS
        if(strcmp(rule->rightSide[0], "EMPTY") == 0){
            // Rule 2: If ε is in FIRST(α), for each terminal b in FOLLOW(A), add A -> α to M[A, b]
            for(int j = 0; j<MAX_TOKENS; ++j){ //Find FOLLOW(A)
                if(followSet[A][j]!=NULL){
                    int terminalIndex = getTokenIndex(followSet[A][j]);
                    if (terminalIndex == INVALID_LOOKUP) continue; //Skip if invalid index.
                    char ruleString[MAX_NAME_LENGTH] = "";
                    snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                    safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable");
                }
            }
        } else { //Not empty
            int k=0;
            while(rule->rightSide[k] != NULL){
                if(!isNonTerminal(rule->rightSide[k])){ //If terminal
                    int terminalIndex = getTokenIndex(rule->rightSide[k]);
                    if(terminalIndex == INVALID_LOOKUP) break; //invalid terminal
                    char ruleString[MAX_NAME_LENGTH] = "";
                    snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                    safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable"); //Add the production
                    break;
                }
                //If NonTerminal
                GrammarSymbol X = getGrammarSymbol(rule->rightSide[k]);

                for(int j=0; j<MAX_TOKENS; j++){//For each terminal in FIRST(X)
                    if(firstSet[X][j] != NULL && strcmp(firstSet[X][j], "EMPTY")!=0 ){
                        int terminalIndex = getTokenIndex(firstSet[X][j]);
                        if(terminalIndex == INVALID_LOOKUP) continue;
                        char ruleString[MAX_NAME_LENGTH] = "";
                        snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                        safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable");
                    }
                }

                if(firstSet[X][getTokenIndex("EMPTY")] == NULL) break; //If no empty, break
                k++;
                //If all symbols have empty, then use follow set
                if(rule->rightSide[k] == NULL && firstSet[X][getTokenIndex("EMPTY")] != NULL){
                    for(int j = 0; j<MAX_TOKENS; ++j){ //Find FOLLOW(A)
                        if(followSet[A][j]!=NULL){
                            int terminalIndex = getTokenIndex(followSet[A][j]);
                            if (terminalIndex == INVALID_LOOKUP) continue;
                            char ruleString[MAX_NAME_LENGTH] = "";
                            snprintf(ruleString, sizeof(ruleString), "%d", i); // Convert production index to string
                            safeStringCopy(&parseTable[A][terminalIndex], ruleString, "constructParseTable");
                        }
                    }
                }
            }
        }
    }
}


char* getProductionRuleString(int ruleIndex) {
    if (ruleIndex < 0 || grammar[ruleIndex].rightSideLength == 0) {
        return "Invalid Production"; // Handle invalid index
    }

    ProductionRule *rule = &grammar[ruleIndex];
    static char productionStr[MAX_PRODUCTION_DISPLAY_LENGTH]; // Static buffer to store the string
    char nonTerminalStr[MAX_NAME_LENGTH];

    //Map NonTerminal to String
    if(rule->leftSide == EXPR) strcpy(nonTerminalStr, "EXPR");
    else if (rule->leftSide == EXPR_PRIME) strcpy(nonTerminalStr, "EXPR'");
    else if (rule->leftSide == TERM) strcpy(nonTerminalStr, "TERM");
    else if (rule->leftSide == TERM_PRIME) strcpy(nonTerminalStr, "TERM'");
    else if(rule->leftSide == FACTOR) strcpy(nonTerminalStr, "FACTOR");
    else {
        strcpy(nonTerminalStr, "UNKNOWN");
    }

    snprintf(productionStr, sizeof(productionStr), "%s -> ", nonTerminalStr);

    for (int i = 0; i < rule->rightSideLength; i++) {
        strncat(productionStr, rule->rightSide[i], sizeof(productionStr) - strlen(productionStr) - 1);
        if (i < rule->rightSideLength - 1) {
            strncat(productionStr, " ", sizeof(productionStr) - strlen(productionStr) - 1);
        }
    }

    return productionStr;
}


void displayParseTable() {
    // Modified to print production strings
    printf("\nParsing Table:\n");
    printf("------------------------------------------------------------\n");
    printf("%-10s", ""); // Empty space for row labels

    // Print terminal headers
    for(int j=0; j<MAX_TOKENS; ++j){
       if(tokens[j]!=NULL) printf("%-20s", tokens[j]);
    }
    printf("\n");


    for (int i = 0; i < NUM_NONTERMINALS; i++) {
        // Print non-terminal label
        if(i == EXPR) printf("%-10s", "EXPR");
        else if (i == EXPR_PRIME) printf("%-10s", "EXPR'");
        else if (i == TERM) printf("%-10s", "TERM");
        else if (i == TERM_PRIME) printf("%-10s", "TERM'");
        else if (i == FACTOR) printf("%-10s", "FACTOR");


        for (int j = 0; j < MAX_TOKENS; j++) {
            if (parseTable[i][j] != NULL) {
                int ruleIndex = atoi(parseTable[i][j]);
                printf("%-20s", getProductionRuleString(ruleIndex)); // Print string
            } else {
                printf("%-20s", "-"); // Indicate error/empty entry
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------------------\n");
}

int getTokenIndex(const char *token) {
    for (int i = 0; tokens[i] != NULL; i++) {
        if (strcmp(token, tokens[i]) == 0) {
            return i;
        }
    }
    return INVALID_LOOKUP; // Not found
}

GrammarSymbol getGrammarSymbol(const char *nonTerminal) {
    if (strcmp(nonTerminal, "EXPR") == 0) return EXPR;
    if (strcmp(nonTerminal, "EXPR'") == 0) return EXPR_PRIME;
    if (strcmp(nonTerminal, "TERM") == 0) return TERM;
    if (strcmp(nonTerminal, "TERM'") == 0) return TERM_PRIME;
    if (strcmp(nonTerminal, "FACTOR") == 0) return FACTOR;
    fprintf(stderr, "Invalid non-terminal: %s\n", nonTerminal);
    return -1;
}

bool isNonTerminal(const char* symbol){
    if (strcmp(symbol, "EXPR") == 0) return true;
    if (strcmp(symbol, "EXPR'") == 0) return true;
    if (strcmp(symbol, "TERM") == 0) return true;
    if (strcmp(symbol, "TERM'") == 0) return true;
    if (strcmp(symbol, "FACTOR") == 0) return true;
    return false;
}

TokenIndex getTokenTypeIndex(int tokenType) {
    switch (tokenType) {
        case VAR: return VAR_INDEX;
        case PLUS:       return PLUS_INDEX;
        case STAR:      return STAR_INDEX;
        case OPEN:     return OPEN_INDEX;
        case CLOSE:     return CLOSE_INDEX;
        case END:  return END_INDEX;
        default:         return INVALID_LOOKUP; // Invalid token
    }
}

void stackPush(const char *symbol) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed in stackPush()\n");
        exit(EXIT_FAILURE);
    }
    safeStringCopy(&newNode->symbol, symbol, "stackPush");
    newNode->next = stack;
    stack = newNode;
}

char *stackPop() {
    if (stack == NULL) {
        return NULL;
    }
    StackNode *temp = stack;
    stack = stack->next;
    char *symbol = temp->symbol;
    free(temp);
    return symbol;
}

bool isStackEmpty() {
    return stack == NULL;
}

void releaseStack() {
    while (!isStackEmpty()) {
        char* temp = stackPop();
        if(temp!=NULL) free(temp);
    }
}

void analyzeInput() {
    stackPush("END");  // Push end onto the stack
    stackPush("EXPR");      // Push the start symbol onto the stack

    int nextToken = yylex();  // Get the first token *type*
    int lookahead = getTokenTypeIndex(nextToken); // Get the *index*

    while (!isStackEmpty()) {
        char *top = stackPop();

        if (isNonTerminal(top)) {
            int nonTermIndex = getGrammarSymbol(top);
            if (nonTermIndex == -1) {
                fprintf(stderr, "Invalid NonTerminal index!\n");
                free(top);
                releaseStack();
                return;
            }
            if (lookahead == INVALID_LOOKUP) { //CRITICAL CHECK
                fprintf(stderr, "Invalid lookahead index!\n");
                free(top);
                releaseStack();
                return;
            }

            char *ruleIndexStr = parseTable[nonTermIndex][lookahead];

            if (ruleIndexStr != NULL) {
                int ruleIndex = atoi(ruleIndexStr);
                ProductionRule *rule = &grammar[ruleIndex];

                // Push RHS symbols onto stack in reverse order
                for (int i = rule->rightSideLength - 1; i >= 0; i--) {
                    if (strcmp(rule->rightSide[i], "EMPTY") != 0) {
                        stackPush(rule->rightSide[i]);
                    }
                }
                free(top);
            } else {
                printf("Syntax Error: No production for %s with lookahead %s\n", top, tokens[lookahead]);
                free(top);
                releaseStack();
                return;
            }
        } else if (strcmp(top, tokens[lookahead]) == 0) {
            // Matched lookahead, consume token
            if (strcmp(tokens[lookahead], "END") == 0) {
                printf("Parsing successful!\n");
                free(top);
                releaseStack();
                return;
            }
            free(top);
            nextToken = yylex(); // Get next token *type*
            lookahead = getTokenTypeIndex(nextToken); // Get *index*

        } else {
            printf("Syntax Error: Expected %s, but got %s (%d)\n", top, tokens[lookahead], lookahead);
            free(top);
            releaseStack();
            return;
        }
    }
    printf("Parsing failed (unexpected end of input or stack not empty).\n");
    releaseStack();
}

void reportError(const char *message) {
    fprintf(stderr, "Error: %s near token %s\n", message, yytext);
}

int resetLexer() {
    parseDoneFlag = 0;
    while (getchar() != '\n');
    return 0;
}

void releaseMemory() {
    //Free allocated memory (FIRST, FOLLOW, and Parse Table)
    for(int i=0; i<NUM_NONTERMINALS; ++i){
        for(int j=0; j<MAX_TOKENS; ++j){
            if(firstSet[i][j] != NULL) free(firstSet[i][j]);
            if(followSet[i][j] != NULL) free(followSet[i][j]);
            if(parseTable[i][j] != NULL) free(parseTable[i][j]);
        }
    }
}

int main() {
    yyparse();
    releaseMemory();
    return 0;
}
