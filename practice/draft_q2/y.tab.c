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

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yylex(void);
extern char *yytext;
extern YY_BUFFER_STATE yy_create_buffer(FILE *file, int size);
extern void yy_switch_to_buffer(YY_BUFFER_STATE new_buffer);
extern void yy_delete_buffer(YY_BUFFER_STATE b);
extern YY_BUFFER_STATE yy_scan_string(const char *yy_str);
extern YY_BUFFER_STATE yy_current_buffer;

typedef enum {
    NONTERMINAL_SENTINEL, // Start symbol
    TOTAL_NONTERMINALS  
} SymbolCategory;

typedef struct GrammarRule {  
    int head; // Left-hand side 
    char* body[10]; // Right-hand side (RHS)
    int body_length; 
} GrammarRule;

GrammarRule *grammar_rules = NULL; 
int rule_count = 0;
int rule_capacity = 0;

#define MAX_TERMINALS 10 
#define MAX_DERIVATION_DEPTH 100 

char *predictive_parsing_table[MAX_DERIVATION_DEPTH][MAX_TERMINALS]; 

char **terminal_symbols = NULL; 
int terminal_count = 0;
int terminal_capacity = 0;

char ***first_sets; 
char ***follow_sets; 
char** nonterminal_symbols = NULL; 
int nonterminal_count = 0;


typedef struct TokenNode {  
    char *data;
    struct TokenNode *next_node;  
} TokenNode;

TokenNode *parse_stack = NULL;  

void stack_push(const char *symbol) {  
    TokenNode *new_node = (TokenNode *)malloc(sizeof(TokenNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failure in stack_push()\n");
        exit(1);
    }
    new_node->data = strdup(symbol);
    if (new_node->data == NULL) {
        fprintf(stderr, "Memory allocation error (strdup)!\n");
        exit(1);
    }
    new_node->next_node = parse_stack;
    parse_stack = new_node;
}

char *stack_pop() {
    if (parse_stack == NULL) {
        return NULL;
    }
    TokenNode *temp = parse_stack;
    parse_stack = parse_stack->next_node;
    char *symbol = temp->data;
    free(temp);
    return symbol;
}

bool is_stack_empty() {
    return parse_stack == NULL;
}

void free_stack() {  
    while (!is_stack_empty()) {
        char* temp = stack_pop();
        if (temp != NULL) free(temp);
    }
}

void calculate_first_sets();
void calculate_follow_sets();
void construct_parsing_table();
void display_parsing_table();
int retrieve_terminal_index(const char *terminal);
int retrieve_nonterminal_index(const char *nonTerminal);
int retrieve_rule_index(int head, const char** body, int body_length);
bool is_nonterminal(const char* symbol);
void perform_parse();
void report_syntax_error(const char *message);
int get_token_index(const char* token);
char* rule_to_string(int rule_index);
void display_first_sets();
void display_follow_sets();
char* nonterminal_to_string(int nt);
void show_derivation(int derivation[], int derivation_length);
void load_grammar();
void insert_terminal(const char* terminal);
void insert_nonterminal(const char* nonTerminal);
void insert_rule(int head, char** body, int body_length);
void release_memory();
void yyerror(const char *s);

#ifdef __cplusplus
extern "C" int yylex(void);
#endif

int parsing_complete = 0; 

int reset_lexer() {  
    parsing_complete = 0;
    return 0;
}

#line 196 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    TERMINAL = 258,                /* TERMINAL  */
    ADD = 259,                     /* ADD  */
    MULTIPLY = 260,                /* MULTIPLY  */
    LEFT_PAREN = 261,              /* LEFT_PAREN  */
    RIGHT_PAREN = 262,             /* RIGHT_PAREN  */
    END_OF_STREAM = 263,           /* END_OF_STREAM  */
    END_OF_INPUT = 264             /* END_OF_INPUT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define TERMINAL 258
#define ADD 259
#define MULTIPLY 260
#define LEFT_PAREN 261
#define RIGHT_PAREN 262
#define END_OF_STREAM 263
#define END_OF_INPUT 264

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 126 "ll1.y"

    char *string; 
    int   token_code;

#line 272 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TERMINAL = 3,                   /* TERMINAL  */
  YYSYMBOL_ADD = 4,                        /* ADD  */
  YYSYMBOL_MULTIPLY = 5,                   /* MULTIPLY  */
  YYSYMBOL_LEFT_PAREN = 6,                 /* LEFT_PAREN  */
  YYSYMBOL_RIGHT_PAREN = 7,                /* RIGHT_PAREN  */
  YYSYMBOL_END_OF_STREAM = 8,              /* END_OF_STREAM  */
  YYSYMBOL_END_OF_INPUT = 9,               /* END_OF_INPUT  */
  YYSYMBOL_YYACCEPT = 10,                  /* $accept  */
  YYSYMBOL_compilation_unit = 11           /* compilation_unit  */
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
static const yytype_uint8 yyrline[] =
{
       0,   140,   140
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
  "\"end of file\"", "error", "\"invalid token\"", "TERMINAL", "ADD",
  "MULTIPLY", "LEFT_PAREN", "RIGHT_PAREN", "END_OF_STREAM", "END_OF_INPUT",
  "$accept", "compilation_unit", YY_NULLPTR
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
  case 2: /* compilation_unit: %empty  */
#line 140 "ll1.y"
        {
            load_grammar();
            calculate_first_sets();
            calculate_follow_sets();
            construct_parsing_table();
            display_first_sets();
            display_follow_sets();
            display_parsing_table();

            printf("Terminals: ");
            for (int i = 0; i < terminal_count; i++) {
                printf("%s ", terminal_symbols[i]);
            }
            printf("\n");

            char input_buffer[1000];
            printf("Enter input string (or 'quit' to exit):\n");
            while (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
                input_buffer[strcspn(input_buffer, "\n")] = 0; // Remove trailing newline

                if (strcmp(input_buffer, "quit") == 0) {
                    break;
                }

                if (strlen(input_buffer) > 0) {
                    YY_BUFFER_STATE buffer = yy_scan_string(input_buffer);
                    perform_parse();
                    yy_delete_buffer(buffer);
                    reset_lexer();
                } else {
                    printf("Please enter a non-empty string.\n");
                }
                printf("Enter input string (or 'quit' to exit):\n");
            }
            release_memory();
        }
#line 1285 "y.tab.c"
    break;


#line 1289 "y.tab.c"

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

#line 178 "ll1.y"


void insert_terminal(const char* terminal) {  
    // Check if terminal already exists to avoid duplicates
    for (int i = 0; i < terminal_count; i++) {
        if (strcmp(terminal_symbols[i], terminal) == 0) {
            return; // Terminal already exists, no need to add
        }
    }

    if (terminal_count == terminal_capacity) {
        terminal_capacity = (terminal_capacity == 0) ? 1 : terminal_capacity * 2; // Initial or Double
        terminal_symbols = (char**)realloc(terminal_symbols, terminal_capacity * sizeof(char*));
        if (!terminal_symbols) {
            fprintf(stderr, "Memory allocation error for terminal_symbols.\n");
            exit(1);
        }
    }

    terminal_symbols[terminal_count++] = strdup(terminal);
    if (!terminal_symbols[terminal_count-1]) {
        fprintf(stderr, "Memory allocation error for strdup.\n");
        exit(1);
    }
}

void insert_nonterminal(const char* nonTerminal) {  
    if (nonterminal_count == 0 || retrieve_nonterminal_index(nonTerminal) == -1)
    {
        nonterminal_count++;
        nonterminal_symbols = (char**)realloc(nonterminal_symbols, nonterminal_count * sizeof(char*));
         if (!nonterminal_symbols) {
             fprintf(stderr, "Memory allocation error for Non-Terminals.\n");
             exit(1);
         }
        nonterminal_symbols[nonterminal_count-1] = strdup(nonTerminal);
        if (!nonterminal_symbols[nonterminal_count-1]) {
           fprintf(stderr, "Memory allocation error for strdup.\n");
           exit(1);
        }
    }
}

void insert_rule(int head, char** body, int body_length) { 
    if (rule_count == rule_capacity) {
        rule_capacity = (rule_capacity == 0) ? 1 : rule_capacity * 2;
        grammar_rules = (GrammarRule*)realloc(grammar_rules, rule_capacity * sizeof(GrammarRule));
         if (!grammar_rules) {
           fprintf(stderr, "Memory allocation error for Grammar.\n");
           exit(1);
         }
    }

    grammar_rules[rule_count].head = head;
    grammar_rules[rule_count].body_length = body_length;
    for (int i = 0; i < body_length; i++) {
        grammar_rules[rule_count].body[i] = strdup(body[i]);
        if (!grammar_rules[rule_count].body[i]) {
            fprintf(stderr, "Memory allocation error for strdup.\n");
            exit(1);
        }
    }
    grammar_rules[rule_count].body[body_length] = NULL;

    rule_count++;
}

void load_grammar() {  
    char input_buffer[1000];
    int num_grammar_rules;

    printf("Enter the number of productions: ");
    fgets(input_buffer, sizeof(input_buffer), stdin);
    sscanf(input_buffer, "%d", &num_grammar_rules);

    insert_terminal("END_OF_STREAM");
    insert_terminal("EPS");

    printf("Enter the productions (e.g., E -> T E'  |  EPS):\n");

    for (int i = 0; i < num_grammar_rules; i++) {
        printf("Production %d: ", i + 1);
        fgets(input_buffer, sizeof(input_buffer), stdin);
        input_buffer[strcspn(input_buffer, "\n")] = 0;

        char lhs_str[100];
        char rhs_str[1000];
        if (sscanf(input_buffer, "%s -> %[^\n]", lhs_str, rhs_str) != 2) {
            fprintf(stderr, "Invalid production format.\n");
            exit(1);
        }

        insert_nonterminal(lhs_str);
        int head = retrieve_nonterminal_index(lhs_str);

        char *rhs_tokens[10]; // Maximum 10 tokens on the RHS
        int body_token_count = 0;
        char *token = strtok(rhs_str, " ");
        while (token != NULL) {
            if (strcmp(token, "|") != 0) {
                if (!is_nonterminal(token)) {
                    insert_terminal(token);
                } else {
                    insert_nonterminal(token);
                }
                rhs_tokens[body_token_count++] = token;
            }
            token = strtok(NULL, " ");
        }

        insert_rule(head, rhs_tokens, body_token_count);
    }

    if (rule_count == rule_capacity) {
        rule_capacity += 1;
        grammar_rules = (GrammarRule*)realloc(grammar_rules, rule_capacity * sizeof(GrammarRule));
         if (!grammar_rules) {
           fprintf(stderr, "Memory allocation error for Grammar.\n");
           exit(1);
         }
    }
    grammar_rules[rule_count].head = -1; 
    grammar_rules[rule_count].body_length = 0;
    rule_count++;
}

void calculate_first_sets() { 
    first_sets = (char***)malloc(nonterminal_count * sizeof(char**));
    if (!first_sets) {
        fprintf(stderr, "Memory allocation error for first_sets.\n");
        exit(1);
    }
    for (int i = 0; i < nonterminal_count; i++) {
        first_sets[i] = (char**)malloc(terminal_count * sizeof(char*));
        if (!first_sets[i]) {
            fprintf(stderr, "Memory allocation error for first_sets.\n");
            exit(1);
        }
        for (int j = 0; j < terminal_count; j++) {
            first_sets[i][j] = NULL;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < rule_count && grammar_rules[i].body_length != 0; i++) {
            GrammarRule *rule = &grammar_rules[i];
            if (!is_nonterminal(rule->body[0])) {
                if (first_sets[rule->head][retrieve_terminal_index(rule->body[0])] == NULL) {
                    first_sets[rule->head][retrieve_terminal_index(rule->body[0])] = strdup(rule->body[0]);
                    if (first_sets[rule->head][retrieve_terminal_index(rule->body[0])] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                        exit(1);
                    }
                    changed = true;
                }
            } else {
                if (strcmp(rule->body[0], "EPS") == 0) {
                    if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                        first_sets[rule->head][retrieve_terminal_index("EPS")] = strdup("EPS");
                        if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                            exit(1);
                        }
                        changed = true;
                    }
                } else {
                    int k = 0;
                    while (rule->body[k] != NULL) {
                        if (!is_nonterminal(rule->body[k])) {
                            if (first_sets[rule->head][retrieve_terminal_index(rule->body[k])] == NULL) {
                                first_sets[rule->head][retrieve_terminal_index(rule->body[k])] = strdup(rule->body[k]);
                                if (first_sets[rule->head][retrieve_terminal_index(rule->body[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                            break;
                        }
                        int Y = retrieve_nonterminal_index(rule->body[k]);
                        for (int j = 0; j < terminal_count; ++j) {
                            if (first_sets[Y][j] != NULL && strcmp(first_sets[Y][j], "EPS") != 0) {
                                if (first_sets[rule->head][j] == NULL) {
                                    first_sets[rule->head][j] = strdup(first_sets[Y][j]);
                                    if (first_sets[rule->head][j] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                                        exit(1);
                                    }
                                    changed = true;
                                }
                            }
                        }
                        if (first_sets[Y][retrieve_terminal_index("EPS")] == NULL) break;
                        k++;
                        if (rule->body[k] == NULL && first_sets[Y][retrieve_terminal_index("EPS")] != NULL) {
                            if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                                first_sets[rule->head][retrieve_terminal_index("EPS")] = strdup("EPS");
                                if (first_sets[rule->head][retrieve_terminal_index("EPS")] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup) in calculate_first_sets!\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void calculate_follow_sets() { 
    follow_sets = (char***)malloc(nonterminal_count * sizeof(char**));
    if (!follow_sets) {
        fprintf(stderr, "Memory allocation error for follow_sets.\n");
        exit(1);
    }
    for (int i = 0; i < nonterminal_count; i++) {
        follow_sets[i] = (char**)malloc(terminal_count * sizeof(char*));
        if (!follow_sets[i]) {
            fprintf(stderr, "Memory allocation error for follow_sets.\n");
            exit(1);
        }
        for (int j = 0; j < terminal_count; j++) {
            follow_sets[i][j] = NULL;
        }
    }

    follow_sets[0][retrieve_terminal_index("END_OF_STREAM")] = strdup("END_OF_STREAM");
    if (follow_sets[0][retrieve_terminal_index("END_OF_STREAM")] == NULL) {
        fprintf(stderr, "Memory allocation error (strdup).\n");
        exit(1);
    }
    bool changed = true;
    while (changed) {
        changed = false;

        for (int i = 0; i < rule_count && grammar_rules[i].body_length != 0; ++i) {
            GrammarRule* rule = &grammar_rules[i];

            for (int j = 0; j < rule->body_length; ++j) {
                if (is_nonterminal(rule->body[j])) {
                    int B = retrieve_nonterminal_index(rule->body[j]);

                    int k = j + 1;
                    while (rule->body[k] != NULL) {
                        if (!is_nonterminal(rule->body[k])) {
                            if (follow_sets[B][retrieve_terminal_index(rule->body[k])] == NULL) {
                                follow_sets[B][retrieve_terminal_index(rule->body[k])] = strdup(rule->body[k]);
                                if (follow_sets[B][retrieve_terminal_index(rule->body[k])] == NULL) {
                                    fprintf(stderr, "Memory allocation error (strdup).\n");
                                    exit(1);
                                }
                                changed = true;
                            }
                            break;
                        }

                        int beta = retrieve_nonterminal_index(rule->body[k]);

                        for (int m = 0; m < terminal_count; ++m) {
                            if (first_sets[beta][m] != NULL && strcmp(first_sets[beta][m], "EPS") != 0) {
                                if (follow_sets[B][m] == NULL) {
                                    follow_sets[B][m] = strdup(first_sets[beta][m]);
                                    if (follow_sets[B][m] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup).\n");
                                        exit(1);
                                    }
                                    changed = true;
                                }
                            }
                        }
                        if (first_sets[beta][retrieve_terminal_index("EPS")] == NULL) break;
                        k++;
                    }

                    if (rule->body[k] == NULL) {
                        int A = rule->head;
                        for (int m = 0; m < terminal_count; ++m) {
                            if (follow_sets[A][m] != NULL) {
                                if (follow_sets[B][m] == NULL) {
                                    follow_sets[B][m] = strdup(follow_sets[A][m]);
                                    if (follow_sets[B][m] == NULL) {
                                        fprintf(stderr, "Memory allocation error (strdup).\n");
                                        exit(1);
                                    }
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

void construct_parsing_table() {  
    for (int i = 0; i < nonterminal_count; ++i) {
        for (int j = 0; j < terminal_count; ++j) {
            predictive_parsing_table[i][j] = NULL;
        }
    }

    for (int i = 0; i < rule_count && grammar_rules[i].body_length != 0; i++) {
        GrammarRule *rule = &grammar_rules[i];
        int A = rule->head;

        if (strcmp(rule->body[0], "EPS") == 0) {
            for (int j = 0; j < terminal_count; ++j) {
                if (follow_sets[A][j] != NULL) {
                    int terminal_index = retrieve_terminal_index(follow_sets[A][j]);
                    if (terminal_index == -1) continue;
                    char rule_str[50] = "";
                    sprintf(rule_str, "%d", i);
                    predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                    if (predictive_parsing_table[A][terminal_index] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup).\n");
                        exit(1);
                    }
                }
            }
        } else {
            int k = 0;
            while (rule->body[k] != NULL) {
                if (!is_nonterminal(rule->body[k])) {
                    int terminal_index = retrieve_terminal_index(rule->body[k]);
                    if (terminal_index == -1) break;
                    char rule_str[50] = "";
                    sprintf(rule_str, "%d", i);
                    predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                    if (predictive_parsing_table[A][terminal_index] == NULL) {
                        fprintf(stderr, "Memory allocation error (strdup).\n");
                        exit(1);
                    }
                    break;
                }
                int X = retrieve_nonterminal_index(rule->body[k]);

                for (int j = 0; j < terminal_count; j++) {
                    if (first_sets[X][j] != NULL && strcmp(first_sets[X][j], "EPS") != 0) {
                        int terminal_index = retrieve_terminal_index(first_sets[X][j]);
                        if (terminal_index == -1) continue;
                        char rule_str[50] = "";
                        sprintf(rule_str, "%d", i);
                        predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                        if (predictive_parsing_table[A][terminal_index] == NULL) {
                            fprintf(stderr, "Memory allocation error (strdup).\n");
                            exit(1);
                        }
                    }
                }

                if (first_sets[X][retrieve_terminal_index("EPS")] == NULL) break;
                k++;
                if (rule->body[k] == NULL && first_sets[X][retrieve_terminal_index("EPS")] != NULL) {
                    for (int j = 0; j < terminal_count; ++j) {
                        if (follow_sets[A][j] != NULL) {
                            int terminal_index = retrieve_terminal_index(follow_sets[A][j]);
                            if (terminal_index == -1) continue;
                            char rule_str[50] = "";
                            sprintf(rule_str, "%d", i);
                            predictive_parsing_table[A][terminal_index] = strdup(rule_str);
                            if (predictive_parsing_table[A][terminal_index] == NULL) {
                                fprintf(stderr, "Memory allocation error (strdup).\n");
                                exit(1);
                            }
                        }
                    }
                }
            }
        }
    }
}

char* rule_to_string(int rule_index) { 
    if (rule_index < 0 || rule_index >= rule_count || grammar_rules[rule_index].body_length == 0) {
        return "Invalid Production";
    }

    GrammarRule *rule = &grammar_rules[rule_index];
    static char rule_string[100];
    char* nonTerminalStr = nonterminal_to_string(rule->head);

    snprintf(rule_string, sizeof(rule_string), "%s -> ", nonTerminalStr);

    for (int i = 0; i < rule->body_length; i++) {
        strncat(rule_string, rule->body[i], sizeof(rule_string) - strlen(rule_string) - 1);
        if (i < rule->body_length - 1) {
            strncat(rule_string, " ", sizeof(rule_string) - strlen(rule_string) - 1);
        }
    }

    return rule_string;
}

void display_parsing_table() { 
    printf("\nParsing Table:\n");
    printf("------------------------------------------------------------\n");
    printf("%-15s", ""); // Empty space for row labels

    // Print column headers (only terminals)
    for (int j = 0; j < terminal_count; j++) {
        if (!is_nonterminal(terminal_symbols[j]) && strcmp(terminal_symbols[j], "EPS") != 0) {
            printf("%-20s", terminal_symbols[j]);
        }
    }
    printf("\n");

    // Print table rows
    for (int i = 0; i < nonterminal_count; i++) {
        printf("%-15s", nonterminal_to_string(i));

        // Print table entries (only for terminals, excluding EPS)
        for (int j = 0; j < terminal_count; j++) {
            if (!is_nonterminal(terminal_symbols[j]) && strcmp(terminal_symbols[j], "EPS") != 0) {
                if (predictive_parsing_table[i][j] != NULL) {
                    int rule_index = atoi(predictive_parsing_table[i][j]);
                    printf("%-20s", rule_to_string(rule_index));
                } else {
                    printf("%-20s", "-");
                }
            }
        }
        printf("\n");
    }
    printf("------------------------------------------------------------\n");
}

int retrieve_terminal_index(const char *terminal) { 
    for (int i = 0; i < terminal_count; i++) {
        if (strcmp(terminal_symbols[i], terminal) == 0) {
            return i;
        }
    }
    return -1;
}

int retrieve_nonterminal_index(const char *nonTerminal) {
    for (int i = 0; i < nonterminal_count; ++i) {
        if (strcmp(nonterminal_symbols[i], nonTerminal) == 0) return i;
    }
    return -1;
}

bool is_nonterminal(const char* symbol) {  
    for (int i = 0; i < nonterminal_count; ++i) {
        if (strcmp(nonterminal_symbols[i], symbol) == 0) return true;
    }
    return false;
}

int retrieve_rule_index(int head, const char** body, int body_length) {  
    for (int i = 0; i < rule_count; i++) {
        if (grammar_rules[i].head == head && grammar_rules[i].body_length == body_length) {
            bool match = true;
            for (int j = 0; j < body_length; j++) {
                if (strcmp(grammar_rules[i].body[j], body[j]) != 0) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
    }
    return -1;
}

int get_token_index(const char* token) { 
    for (int i = 0; i < terminal_count; ++i) {
        if (strcmp(terminal_symbols[i], token) == 0) return i;
    }
    return -1;
}

void perform_parse() {  
    stack_push("END_OF_STREAM");
    stack_push(nonterminal_symbols[0]);

    int lookahead_token = yylex();

    int derivation[MAX_DERIVATION_DEPTH];
    int derivation_length = 0;

    while (!is_stack_empty()) {
        char *top = stack_pop();

        // Debug: Print current state
        printf("Stack top: %s, Lookahead: %s\n", top, yytext);

        if (is_nonterminal(top)) {
            int nonterm_index = retrieve_nonterminal_index(top);
            if (nonterm_index == -1) {
                fprintf(stderr, "Invalid NonTerminal index!\n");
                free(top);
                free_stack();
                return;
            }

            int lookahead = get_token_index(yytext);
            if (lookahead == -1) {
                fprintf(stderr, "Invalid lookahead index! Token '%s' not in terminals.\n", yytext);
                free(top);
                free_stack();
                return;
            }

            char *rule_index_str = predictive_parsing_table[nonterm_index][lookahead];
            if (rule_index_str != NULL) {
                int rule_index = atoi(rule_index_str);
                GrammarRule *rule = &grammar_rules[rule_index];

                if (derivation_length < MAX_DERIVATION_DEPTH) {
                    derivation[derivation_length++] = rule_index;
                } else {
                    fprintf(stderr, "Derivation too long!\n");
                    free(top);
                    free_stack();
                    return;
                }

                for (int i = rule->body_length - 1; i >= 0; i--) {
                    if (strcmp(rule->body[i], "EPS") != 0) {
                        stack_push(rule->body[i]);
                    }
                }
                free(top);
            } else {
                printf("Syntax Error: No production for %s with lookahead %s\n", top, yytext);
                free(top);
                free_stack();
                return;
            }
        } else {
            // Special handling for END_OF_STREAM
            if (strcmp(top, "END_OF_STREAM") == 0) {
                if (strcmp(yytext, "$") == 0 || yytext[0] == '\0') {
                    printf("Parsing successful!\n");
                    show_derivation(derivation, derivation_length);
                    free(top);
                    free_stack();
                    return;
                } else {
                    printf("Syntax Error: Expected END_OF_STREAM, but got %s\n", yytext);
                    free(top);
                    free_stack();
                    return;
                }
            } else if (strcmp(top, yytext) == 0) {
                free(top);
                lookahead_token = yylex();
            } else {
                printf("Syntax Error: Expected %s, but got %s\n", top, yytext);
                free(top);
                free_stack();
                return;
            }
        }
    }
    printf("Parsing failed (unexpected end of input or stack not empty).\n");
    free_stack();
}

void show_derivation(int derivation[], int derivation_length) { 
    printf("Derivation:\n");
    if (derivation_length > 0) {
        printf("%s", nonterminal_symbols[0]);
        for (int i = 0; i < derivation_length; ++i) {
            printf(" => %s", rule_to_string(derivation[i]));
        }
        printf("\n");
    }
}

void display_first_sets() { 
    printf("\nFIRST Sets:\n");
    printf("---------------------\n");
    for (int i = 0; i < nonterminal_count; i++) {
        printf("FIRST(%s) = { ", nonterminal_to_string(i));
        for (int j = 0; j < terminal_count; j++) {
            if (first_sets[i][j] != NULL) {
                printf("%s", first_sets[i][j]);
                int k = j + 1;
                while (k < terminal_count && first_sets[i][k] == NULL) {
                    k++;
                }
                if (k < terminal_count && first_sets[i][k] != NULL) {
                    printf(", ");
                }
            }
        }
        printf(" }\n");
    }
    printf("---------------------\n");
}

void display_follow_sets() { 
    printf("\nFOLLOW Sets:\n");
    printf("---------------------\n");
    for (int i = 0; i < nonterminal_count; i++) {
        printf("FOLLOW(%s) = { ", nonterminal_to_string(i));
        for (int j = 0; j < terminal_count; j++) {
            if (follow_sets[i][j] != NULL) {
                printf("%s", follow_sets[i][j]);
                int k = j + 1;
                while (k < terminal_count && follow_sets[i][k] == NULL) {
                    k++;
                }
                if (k < terminal_count && follow_sets[i][k] != NULL) {
                    printf(", ");
                }
            }
        }
        printf(" }\n");
    }
    printf("---------------------\n");
}

char* nonterminal_to_string(int nt) {  
    return nonterminal_symbols[nt];
}

void report_syntax_error(const char *message) { 
    fprintf(stderr, "Error: %s near token %s\n", message, yytext);
    release_memory();
    exit(1);
}

void release_memory() { 
    for (int i = 0; i < terminal_count; ++i) {
        if (terminal_symbols[i] != NULL) free(terminal_symbols[i]);
    }
    if (terminal_symbols != NULL) free(terminal_symbols);

    for (int i = 0; i < nonterminal_count; ++i) {
        if (nonterminal_symbols[i] != NULL) free(nonterminal_symbols[i]);
    }
    if (nonterminal_symbols != NULL) free(nonterminal_symbols);

    for (int i = 0; i < rule_count; ++i) {
        for (int j = 0; j < grammar_rules[i].body_length; ++j) {
            if (grammar_rules[i].body[j] != NULL) free(grammar_rules[i].body[j]);
        }
    }
    if (grammar_rules != NULL) free(grammar_rules);

    if (first_sets) {
        for (int i = 0; i < nonterminal_count; i++) {
            for (int j = 0; j < terminal_count; j++) {
                if (first_sets[i][j] != NULL) {
                    free(first_sets[i][j]);
                }
            }
            free(first_sets[i]);
        }
        free(first_sets);
    }

    if (follow_sets) {
        for (int i = 0; i < nonterminal_count; i++) {
            for (int j = 0; j < terminal_count; j++) {
                if (follow_sets[i][j] != NULL) {
                    free(follow_sets[i][j]);
                }
            }
            free(follow_sets[i]);
        }
        free(follow_sets);
    }

    for (int i = 0; i < nonterminal_count; ++i) {
        for (int j = 0; j < terminal_count; ++j) {
            if (predictive_parsing_table[i][j] != NULL) free(predictive_parsing_table[i][j]);
        }
    }

    free_stack();
}

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s near token %s\n", s, yytext);
    release_memory();
    exit(1);
}
