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
#line 1 "for3Add1.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char *);
int yylex(void);
extern int yylineno;
extern char *yytext;

struct symbol {
    char *name;
    char *type;
    int scope;
};
struct symbol symbol_table[100];
int symbol_count = 0;

int lookup_symbol(char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_symbol(char *name, char *type) {
    if (symbol_count >= 100) {
        fprintf(stderr, "Error: Symbol table overflow\n");
        exit(1);
    }
    symbol_table[symbol_count].name = strdup(name);
    if (!symbol_table[symbol_count].name) { yyerror("strdup failed for symbol name"); exit(1); }
    symbol_table[symbol_count].type = strdup(type);
    if (!symbol_table[symbol_count].type) { yyerror("strdup failed for symbol type"); exit(1); }
    symbol_count++;
}

typedef struct {
    char *op;
    char *arg1;
    char *arg2;
    char *result;
} quad;
quad code[1000];
int next_quad = 0;
int temp_count = 0;
int case_label_count = 0;

struct list {
    int quad_index;
    struct list *next;
};

typedef struct attr {
    char *place;
    struct list *true_list;
    struct list *false_list;
    struct list *next_list;
    struct list *break_list;
    struct list *case_list;
    struct list *continue_list;
    int case_val;
    int quad;
} attr;

void emit(char *op, char *arg1, char *arg2, char *result);
char* new_temp(void);
char* int_to_string(int);
struct list* make_list(int);
struct list* merge(struct list*, struct list*);
void backpatch(struct list*, int);
void print_three_address_code();
void ensure_boolean_lists(attr* expr_attr);

attr* create_attr() {
    attr* new_attr = (attr*)malloc(sizeof(attr));
    if (!new_attr) { yyerror("Memory allocation failed for attribute"); exit(1); }
    new_attr->place = NULL;
    new_attr->true_list = NULL;
    new_attr->false_list = NULL;
    new_attr->next_list = NULL;
    new_attr->break_list = NULL;
    new_attr->case_list = NULL;
    new_attr->continue_list = NULL;
    new_attr->case_val = 0;
    new_attr->quad = next_quad;
    return new_attr;
}


#line 164 "for3Add1.tab.c"

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

#include "for3Add1.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_SWITCH = 7,                     /* SWITCH  */
  YYSYMBOL_CASE = 8,                       /* CASE  */
  YYSYMBOL_DEFAULT = 9,                    /* DEFAULT  */
  YYSYMBOL_BREAK = 10,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 11,                  /* CONTINUE  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_FLOAT = 13,                     /* FLOAT  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_EQ = 16,                        /* EQ  */
  YYSYMBOL_NE = 17,                        /* NE  */
  YYSYMBOL_LE = 18,                        /* LE  */
  YYSYMBOL_GE = 19,                        /* GE  */
  YYSYMBOL_LT = 20,                        /* LT  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_NUMBER = 24,                    /* NUMBER  */
  YYSYMBOL_FLOAT_NUM = 25,                 /* FLOAT_NUM  */
  YYSYMBOL_ID = 26,                        /* ID  */
  YYSYMBOL_27_ = 27,                       /* ';'  */
  YYSYMBOL_28_ = 28,                       /* '('  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_30_ = 30,                       /* ','  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* ':'  */
  YYSYMBOL_34_ = 34,                       /* '='  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_39_ = 39,                       /* '%'  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_program = 41,                   /* program  */
  YYSYMBOL_declaration_list = 42,          /* declaration_list  */
  YYSYMBOL_declaration = 43,               /* declaration  */
  YYSYMBOL_var_decl = 44,                  /* var_decl  */
  YYSYMBOL_type_specifier = 45,            /* type_specifier  */
  YYSYMBOL_func_decl = 46,                 /* func_decl  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_params = 48,                    /* params  */
  YYSYMBOL_param_list = 49,                /* param_list  */
  YYSYMBOL_param = 50,                     /* param  */
  YYSYMBOL_compound_stmt = 51,             /* compound_stmt  */
  YYSYMBOL_local_declarations = 52,        /* local_declarations  */
  YYSYMBOL_local_declaration = 53,         /* local_declaration  */
  YYSYMBOL_stmt_list = 54,                 /* stmt_list  */
  YYSYMBOL_M = 55,                         /* M  */
  YYSYMBOL_N = 56,                         /* N  */
  YYSYMBOL_stmt = 57,                      /* stmt  */
  YYSYMBOL_expr_stmt = 58,                 /* expr_stmt  */
  YYSYMBOL_if_stmt = 59,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 60,                /* while_stmt  */
  YYSYMBOL_for_stmt = 61,                  /* for_stmt  */
  YYSYMBOL_switch_stmt = 62,               /* switch_stmt  */
  YYSYMBOL_case_list = 63,                 /* case_list  */
  YYSYMBOL_case_stmt = 64,                 /* case_stmt  */
  YYSYMBOL_default_stmt = 65,              /* default_stmt  */
  YYSYMBOL_break_stmt = 66,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 67,             /* continue_stmt  */
  YYSYMBOL_return_stmt = 68,               /* return_stmt  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_assign_expr = 70,               /* assign_expr  */
  YYSYMBOL_log_or_expr = 71,               /* log_or_expr  */
  YYSYMBOL_log_and_expr = 72,              /* log_and_expr  */
  YYSYMBOL_rel_expr = 73,                  /* rel_expr  */
  YYSYMBOL_add_expr = 74,                  /* add_expr  */
  YYSYMBOL_mult_expr = 75,                 /* mult_expr  */
  YYSYMBOL_factor = 76,                    /* factor  */
  YYSYMBOL_primary = 77,                   /* primary  */
  YYSYMBOL_var = 78,                       /* var  */
  YYSYMBOL_call = 79,                      /* call  */
  YYSYMBOL_args = 80,                      /* args  */
  YYSYMBOL_arg_list = 81                   /* arg_list  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


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
       2,     2,     2,     2,     2,     2,     2,    39,     2,     2,
      28,    29,    37,    35,    30,    36,     2,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    27,
       2,    34,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   119,   119,   123,   124,   127,   127,   129,   137,   138,
     139,   143,   142,   161,   162,   163,   166,   167,   170,   177,
     183,   184,   187,   189,   201,   206,   209,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   228,   232,   235,
     250,   264,   285,   310,   332,   342,   353,   358,   379,   389,
     397,   405,   411,   418,   420,   427,   430,   441,   444,   455,
     458,   470,   482,   494,   506,   518,   530,   542,   550,   558,
     561,   569,   577,   585,   588,   590,   591,   592,   593,   594,
     604,   613,   624,   625,   628,   633
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "FOR", "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE", "INT", "FLOAT",
  "VOID", "RETURN", "EQ", "NE", "LE", "GE", "LT", "GT", "AND", "OR",
  "NUMBER", "FLOAT_NUM", "ID", "';'", "'('", "')'", "','", "'{'", "'}'",
  "':'", "'='", "'+'", "'-'", "'*'", "'/'", "'%'", "$accept", "program",
  "declaration_list", "declaration", "var_decl", "type_specifier",
  "func_decl", "$@1", "params", "param_list", "param", "compound_stmt",
  "local_declarations", "local_declaration", "stmt_list", "M", "N", "stmt",
  "expr_stmt", "if_stmt", "while_stmt", "for_stmt", "switch_stmt",
  "case_list", "case_stmt", "default_stmt", "break_stmt", "continue_stmt",
  "return_stmt", "expr", "assign_expr", "log_or_expr", "log_and_expr",
  "rel_expr", "add_expr", "mult_expr", "factor", "primary", "var", "call",
  "args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-49)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -111,     6,    75,  -111,  -111,  -111,  -111,  -111,  -111,   -12,
    -111,     0,  -111,    87,    -9,     5,    12,     7,  -111,  -111,
    -111,    75,    15,  -111,  -111,  -111,    75,  -111,    17,  -111,
      51,    63,  -111,    -2,    64,  -111,    68,    79,    90,   102,
      85,  -111,  -111,   103,  -111,    33,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,   105,  -111,   107,
     111,  -111,    59,    67,  -111,  -111,   100,  -111,    33,   108,
      95,    33,  -111,  -111,  -111,   110,    33,   106,  -111,  -111,
    -111,    33,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,   109,    33,  -111,   112,  -111,  -111,   113,
     114,  -111,    33,    33,    -1,  -111,    -1,    -1,    -1,    -1,
      -1,    67,    67,  -111,  -111,  -111,  -111,  -111,   116,    33,
     115,  -111,    33,   111,  -111,    -2,  -111,   120,  -111,  -111,
     135,    -2,  -111,  -111,   136,  -111,    33,   117,  -111,   119,
    -111,    54,    -2,  -111,   126,   118,  -111,  -111,  -111,    -2,
     121,  -111,  -111,  -111,  -111,  -111,     8,    10
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     8,     9,    10,     3,     5,     0,
       6,     0,     7,    15,    10,     0,     0,    13,    17,    18,
      11,     0,     0,    16,    21,    12,    24,    22,     0,    20,
      25,     0,    19,     0,     0,    25,     0,     0,     0,     0,
       0,    78,    79,    80,    38,     0,    28,    36,    23,    27,
      29,    30,    31,    32,    33,    34,    35,     0,    53,    55,
      57,    59,    66,    69,    73,    74,    76,    77,     0,     0,
       0,     0,    49,    50,    52,     0,    83,     0,    37,    25,
      25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    25,     0,    51,    85,     0,
      82,    75,     0,     0,    60,    76,    61,    64,    65,    62,
      63,    67,    68,    70,    71,    72,    54,    25,     0,     0,
       0,    81,     0,    56,    58,     0,    25,     0,    25,    84,
      40,     0,    25,    46,     0,    41,     0,    25,    25,     0,
      43,     0,     0,    25,     0,     0,    44,    45,    39,     0,
       0,    25,    42,    25,    24,    24,    25,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,  -111,   141,    34,  -111,  -111,  -111,  -111,
     131,   133,  -111,   127,   -40,   -35,  -111,  -110,    86,  -111,
    -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,  -111,   -38,
    -111,  -111,    55,    56,   -33,    40,    35,  -111,   -17,  -111,
    -111,  -111
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,    27,    28,    10,    22,    16,    17,
      18,    46,    26,    47,    30,    33,   134,    48,    49,    50,
      51,    52,    53,   137,   146,   147,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      99,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    34,    75,    35,    36,    37,     3,    77,    38,    39,
       4,     5,     6,    40,    11,   130,   -48,   -48,   -47,   -47,
     -14,   135,    41,    42,    43,    44,    45,    12,    13,    24,
      93,    19,   148,    96,    87,    88,     9,    21,    98,   152,
     -48,    20,   -47,    31,   102,   103,    24,    15,   104,   106,
     107,   108,   109,   110,   116,    15,   118,    41,    42,    43,
     119,    45,   144,   145,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,    81,    82,    83,    84,    85,
      86,   127,   125,    32,   129,   105,   105,     4,     5,     6,
      12,   131,    68,   133,    87,    88,    70,   136,   139,     4,
       5,    14,   141,   142,    89,    90,    91,    71,   149,    41,
      42,    43,    74,    45,   156,   157,   154,    72,   155,    41,
      42,    43,    44,    45,   113,   114,   115,   111,   112,    73,
      79,    76,    78,    80,    92,   101,    94,    97,   117,   -26,
     138,   120,   121,     8,   122,   126,   128,   132,   143,   140,
     150,   151,    23,    29,   153,    25,    95,   123,     0,   124
};

static const yytype_int16 yycheck[] =
{
      35,     3,    40,     5,     6,     7,     0,    45,    10,    11,
      12,    13,    14,    15,    26,   125,     8,     9,     8,     9,
      29,   131,    24,    25,    26,    27,    28,    27,    28,    31,
      68,    26,   142,    71,    35,    36,     2,    30,    76,   149,
      32,    29,    32,    26,    79,    80,    31,    13,    81,    82,
      83,    84,    85,    86,    92,    21,    94,    24,    25,    26,
      95,    28,     8,     9,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    16,    17,    18,    19,    20,
      21,   119,   117,    32,   122,   102,   103,    12,    13,    14,
      27,   126,    28,   128,    35,    36,    28,   132,   136,    12,
      13,    14,   137,   138,    37,    38,    39,    28,   143,    24,
      25,    26,    27,    28,   154,   155,   151,    27,   153,    24,
      25,    26,    27,    28,    89,    90,    91,    87,    88,    27,
      23,    28,    27,    22,    34,    29,    28,    27,    29,     4,
       4,    29,    29,     2,    30,    29,    31,    27,    29,    32,
      24,    33,    21,    26,    33,    22,    70,   102,    -1,   103
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    41,    42,     0,    12,    13,    14,    43,    44,    45,
      46,    26,    27,    28,    14,    45,    48,    49,    50,    26,
      29,    30,    47,    50,    31,    51,    52,    44,    45,    53,
      54,    26,    32,    55,     3,     5,     6,     7,    10,    11,
      15,    24,    25,    26,    27,    28,    51,    53,    57,    58,
      59,    60,    61,    62,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    28,    55,
      28,    28,    27,    27,    27,    69,    28,    69,    27,    23,
      22,    16,    17,    18,    19,    20,    21,    35,    36,    37,
      38,    39,    34,    69,    28,    58,    69,    27,    69,    80,
      81,    29,    55,    55,    74,    78,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    76,    69,    29,    69,    55,
      29,    29,    30,    72,    73,    55,    29,    69,    31,    69,
      57,    55,    27,    55,    56,    57,    55,    63,     4,    69,
      32,    55,    55,    29,     8,     9,    64,    65,    57,    55,
      24,    33,    57,    33,    55,    55,    54,    54
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    45,    45,
      45,    47,    46,    48,    48,    48,    49,    49,    50,    51,
      52,    52,    53,    54,    54,    55,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    58,    58,    59,
      59,    60,    61,    62,    63,    63,    63,    64,    65,    66,
      67,    68,    68,    69,    70,    70,    71,    71,    72,    72,
      73,    73,    73,    73,    73,    73,    73,    74,    74,    74,
      75,    75,    75,    75,    76,    77,    77,    77,    77,    77,
      78,    79,    80,    80,    81,    81
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     3,     1,     1,
       1,     0,     7,     1,     1,     0,     3,     1,     2,     4,
       2,     0,     1,     3,     0,     0,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,    10,
       6,     7,    11,     8,     3,     3,     0,     5,     4,     2,
       2,     3,     2,     1,     3,     1,     4,     1,     4,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     1,     3,     1,     1,     1,     1,
       1,     4,     1,     0,     3,     1
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
  case 2: /* program: declaration_list  */
#line 120 "for3Add1.y"
    { }
#line 1339 "for3Add1.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 123 "for3Add1.y"
                                                { }
#line 1345 "for3Add1.tab.c"
    break;

  case 7: /* var_decl: type_specifier ID ';'  */
#line 130 "for3Add1.y"
    {
        add_symbol((yyvsp[-1].id), "var");
        free((yyvsp[-1].id));
        (yyval.attr) = NULL;
    }
#line 1355 "for3Add1.tab.c"
    break;

  case 8: /* type_specifier: INT  */
#line 137 "for3Add1.y"
                       { }
#line 1361 "for3Add1.tab.c"
    break;

  case 9: /* type_specifier: FLOAT  */
#line 138 "for3Add1.y"
                       { }
#line 1367 "for3Add1.tab.c"
    break;

  case 10: /* type_specifier: VOID  */
#line 139 "for3Add1.y"
                       { }
#line 1373 "for3Add1.tab.c"
    break;

  case 11: /* $@1: %empty  */
#line 143 "for3Add1.y"
    {
        if (!(yyvsp[-3].id)) { yyerror("Internal error: NULL ID in func_decl"); exit(1); }
        add_symbol((yyvsp[-3].id), "func");
        emit("func_begin", (yyvsp[-3].id), NULL, NULL);
    }
#line 1383 "for3Add1.tab.c"
    break;

  case 12: /* func_decl: type_specifier ID '(' params ')' $@1 compound_stmt  */
#line 149 "for3Add1.y"
    {
        if (!(yyvsp[-5].id) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in func_decl"); exit(1); }
        if ((yyvsp[0].attr) && (yyvsp[0].attr)->next_list) {
            backpatch((yyvsp[0].attr)->next_list, next_quad);
        }
        emit("func_end", (yyvsp[-5].id), NULL, NULL);
        free((yyvsp[-5].id));
        if ((yyvsp[0].attr)) free((yyvsp[0].attr));
        (yyval.attr) = NULL;
    }
#line 1398 "for3Add1.tab.c"
    break;

  case 13: /* params: param_list  */
#line 161 "for3Add1.y"
                    { }
#line 1404 "for3Add1.tab.c"
    break;

  case 14: /* params: VOID  */
#line 162 "for3Add1.y"
                    { }
#line 1410 "for3Add1.tab.c"
    break;

  case 15: /* params: %empty  */
#line 163 "for3Add1.y"
         { }
#line 1416 "for3Add1.tab.c"
    break;

  case 16: /* param_list: param_list ',' param  */
#line 166 "for3Add1.y"
                                  { }
#line 1422 "for3Add1.tab.c"
    break;

  case 18: /* param: type_specifier ID  */
#line 171 "for3Add1.y"
    {
        add_symbol((yyvsp[0].id), "param");
        free((yyvsp[0].id));
    }
#line 1431 "for3Add1.tab.c"
    break;

  case 19: /* compound_stmt: '{' local_declarations stmt_list '}'  */
#line 178 "for3Add1.y"
    {
        (yyval.attr) = (yyvsp[-1].attr);
    }
#line 1439 "for3Add1.tab.c"
    break;

  case 20: /* local_declarations: local_declarations local_declaration  */
#line 183 "for3Add1.y"
                                                          { }
#line 1445 "for3Add1.tab.c"
    break;

  case 22: /* local_declaration: var_decl  */
#line 187 "for3Add1.y"
                             { }
#line 1451 "for3Add1.tab.c"
    break;

  case 23: /* stmt_list: stmt_list M stmt  */
#line 190 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in stmt_list"); exit(1); }
        backpatch((yyvsp[-2].attr)->next_list, (yyvsp[-1].attr)->quad);
        (yyval.attr) = create_attr();
        (yyval.attr)->next_list = (yyvsp[0].attr)->next_list;
        (yyval.attr)->break_list = merge((yyvsp[-2].attr)->break_list, (yyvsp[0].attr)->break_list);
        (yyval.attr)->continue_list = merge((yyvsp[-2].attr)->continue_list, (yyvsp[0].attr)->continue_list);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
        free((yyvsp[-1].attr));
    }
#line 1466 "for3Add1.tab.c"
    break;

  case 24: /* stmt_list: %empty  */
#line 201 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
    }
#line 1474 "for3Add1.tab.c"
    break;

  case 25: /* M: %empty  */
#line 206 "for3Add1.y"
    { (yyval.attr) = create_attr(); (yyval.attr)->quad = next_quad; }
#line 1480 "for3Add1.tab.c"
    break;

  case 26: /* N: %empty  */
#line 209 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->next_list = make_list(next_quad - 1);
    }
#line 1490 "for3Add1.tab.c"
    break;

  case 27: /* stmt: expr_stmt  */
#line 216 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1496 "for3Add1.tab.c"
    break;

  case 28: /* stmt: compound_stmt  */
#line 217 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1502 "for3Add1.tab.c"
    break;

  case 29: /* stmt: if_stmt  */
#line 218 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1508 "for3Add1.tab.c"
    break;

  case 30: /* stmt: while_stmt  */
#line 219 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1514 "for3Add1.tab.c"
    break;

  case 31: /* stmt: for_stmt  */
#line 220 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1520 "for3Add1.tab.c"
    break;

  case 32: /* stmt: switch_stmt  */
#line 221 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1526 "for3Add1.tab.c"
    break;

  case 33: /* stmt: break_stmt  */
#line 222 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1532 "for3Add1.tab.c"
    break;

  case 34: /* stmt: continue_stmt  */
#line 223 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1538 "for3Add1.tab.c"
    break;

  case 35: /* stmt: return_stmt  */
#line 224 "for3Add1.y"
                      { (yyval.attr) = (yyvsp[0].attr); }
#line 1544 "for3Add1.tab.c"
    break;

  case 36: /* stmt: local_declaration  */
#line 225 "for3Add1.y"
                         { (yyval.attr) = create_attr(); }
#line 1550 "for3Add1.tab.c"
    break;

  case 37: /* expr_stmt: expr ';'  */
#line 229 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
    }
#line 1558 "for3Add1.tab.c"
    break;

  case 38: /* expr_stmt: ';'  */
#line 232 "for3Add1.y"
          { (yyval.attr) = create_attr(); }
#line 1564 "for3Add1.tab.c"
    break;

  case 39: /* if_stmt: IF '(' expr ')' M stmt N ELSE M stmt  */
#line 236 "for3Add1.y"
    {
        if (!(yyvsp[-7].attr) || !(yyvsp[-5].attr) || !(yyvsp[-4].attr) || !(yyvsp[-3].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in if-else"); exit(1); }
        ensure_boolean_lists((yyvsp[-7].attr));
        backpatch((yyvsp[-7].attr)->true_list, (yyvsp[-5].attr)->quad);
        backpatch((yyvsp[-7].attr)->false_list, (yyvsp[-1].attr)->quad);
        (yyval.attr) = create_attr();
        struct list *if_exits = ((yyvsp[-4].attr) && (yyvsp[-4].attr)->next_list) ? (yyvsp[-4].attr)->next_list : NULL;
        struct list *else_exits = ((yyvsp[0].attr) && (yyvsp[0].attr)->next_list) ? (yyvsp[0].attr)->next_list : NULL;
        (yyval.attr)->next_list = merge(if_exits, (yyvsp[-3].attr)->next_list);
        (yyval.attr)->next_list = merge((yyval.attr)->next_list, else_exits);
        (yyval.attr)->break_list = merge((yyvsp[-4].attr)->break_list, (yyvsp[0].attr)->break_list);
        (yyval.attr)->continue_list = merge((yyvsp[-4].attr)->continue_list, (yyvsp[0].attr)->continue_list);
        (yyval.attr)->quad = (yyvsp[-7].attr)->quad;
    }
#line 1583 "for3Add1.tab.c"
    break;

  case 40: /* if_stmt: IF '(' expr ')' M stmt  */
#line 251 "for3Add1.y"
    {
        if (!(yyvsp[-3].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in if"); exit(1); }
        ensure_boolean_lists((yyvsp[-3].attr));
        backpatch((yyvsp[-3].attr)->true_list, (yyvsp[-1].attr)->quad);
        (yyval.attr) = create_attr();
        struct list *if_exits = ((yyvsp[0].attr) && (yyvsp[0].attr)->next_list) ? (yyvsp[0].attr)->next_list : NULL;
        (yyval.attr)->next_list = merge((yyvsp[-3].attr)->false_list, if_exits);
        (yyval.attr)->break_list = (yyvsp[0].attr)->break_list;
        (yyval.attr)->continue_list = (yyvsp[0].attr)->continue_list;
        (yyval.attr)->quad = (yyvsp[-3].attr)->quad;
    }
#line 1599 "for3Add1.tab.c"
    break;

  case 41: /* while_stmt: WHILE M '(' expr ')' M stmt  */
#line 265 "for3Add1.y"
    {
        if (!(yyvsp[-5].attr) || !(yyvsp[-3].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in while"); exit(1); }
        ensure_boolean_lists((yyvsp[-3].attr));
        backpatch((yyvsp[-3].attr)->true_list, (yyvsp[-1].attr)->quad);
        if ((yyvsp[0].attr) && (yyvsp[0].attr)->next_list) {
            backpatch((yyvsp[0].attr)->next_list, (yyvsp[-5].attr)->quad);
        }
        if ((yyvsp[0].attr) && (yyvsp[0].attr)->continue_list) {
            backpatch((yyvsp[0].attr)->continue_list, (yyvsp[-5].attr)->quad);
        }
        char *loop_start_target = int_to_string((yyvsp[-5].attr)->quad);
        emit("goto", NULL, NULL, loop_start_target);
        free(loop_start_target);
        (yyval.attr) = create_attr();
        (yyval.attr)->next_list = (yyvsp[-3].attr)->false_list;
        (yyval.attr)->break_list = (yyvsp[0].attr)->break_list;
        (yyval.attr)->quad = (yyvsp[-5].attr)->quad;
    }
#line 1622 "for3Add1.tab.c"
    break;

  case 42: /* for_stmt: FOR '(' expr_stmt M expr ';' M expr ')' M stmt  */
#line 286 "for3Add1.y"
    {
        if (!(yyvsp[-8].attr) || !(yyvsp[-6].attr) || !(yyvsp[-4].attr) || !(yyvsp[-3].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr)) {
            yyerror("Internal error: NULL attr in for_stmt");
            exit(1);
        }
        ensure_boolean_lists((yyvsp[-6].attr));
        backpatch((yyvsp[-6].attr)->true_list, (yyvsp[-1].attr)->quad);
        if ((yyvsp[0].attr)->next_list) {
            backpatch((yyvsp[0].attr)->next_list, (yyvsp[-4].attr)->quad);
        }
        if ((yyvsp[0].attr)->continue_list) {
            backpatch((yyvsp[0].attr)->continue_list, (yyvsp[-4].attr)->quad);
        }
        emit("goto", NULL, NULL, int_to_string((yyvsp[-4].attr)->quad));
        char *to_condition = int_to_string((yyvsp[-7].attr)->quad);
        emit("goto", NULL, NULL, to_condition);
        free(to_condition);
        (yyval.attr) = create_attr();
        (yyval.attr)->next_list = (yyvsp[-6].attr)->false_list;
        (yyval.attr)->break_list = (yyvsp[0].attr)->break_list;
        (yyval.attr)->quad = (yyvsp[-7].attr)->quad;
    }
#line 1649 "for3Add1.tab.c"
    break;

  case 43: /* switch_stmt: SWITCH '(' expr ')' '{' M case_list '}'  */
#line 311 "for3Add1.y"
    {
        if (!(yyvsp[-5].attr) || !(yyvsp[-2].attr) || !(yyvsp[-1].attr)) {
            yyerror("Internal error: NULL attr in switch");
            exit(1);
        }
        (yyval.attr) = create_attr();
        (yyval.attr)->place = (yyvsp[-5].attr)->place; // Preserve the switch expression
        (yyval.attr)->quad = (yyvsp[-5].attr)->quad;
        (yyval.attr)->next_list = (yyvsp[-1].attr)->next_list;
        (yyval.attr)->break_list = (yyvsp[-1].attr)->break_list;

        // Backpatch breaks and fall-throughs to the end of switch
        if ((yyvsp[-1].attr)->break_list) {
            backpatch((yyvsp[-1].attr)->break_list, next_quad);
        }
        if ((yyvsp[-1].attr)->next_list) {
            backpatch((yyvsp[-1].attr)->next_list, next_quad);
        }
    }
#line 1673 "for3Add1.tab.c"
    break;

  case 44: /* case_list: case_list M case_stmt  */
#line 333 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in case_list"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->next_list = merge((yyvsp[-2].attr)->next_list, (yyvsp[0].attr)->next_list);
        (yyval.attr)->break_list = merge((yyvsp[-2].attr)->break_list, (yyvsp[0].attr)->break_list);
        (yyval.attr)->case_list = merge((yyvsp[-2].attr)->case_list, (yyvsp[0].attr)->case_list);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
        backpatch((yyvsp[-2].attr)->next_list, (yyvsp[-1].attr)->quad);
    }
#line 1687 "for3Add1.tab.c"
    break;

  case 45: /* case_list: case_list M default_stmt  */
#line 343 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in case_list"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->next_list = merge((yyvsp[-2].attr)->next_list, (yyvsp[0].attr)->next_list);
        (yyval.attr)->break_list = merge((yyvsp[-2].attr)->break_list, (yyvsp[0].attr)->break_list);
        (yyval.attr)->case_list = (yyvsp[-2].attr)->case_list;
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
        backpatch((yyvsp[-2].attr)->next_list, (yyvsp[-1].attr)->quad);
    }
#line 1701 "for3Add1.tab.c"
    break;

  case 46: /* case_list: %empty  */
#line 353 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
    }
#line 1709 "for3Add1.tab.c"
    break;

  case 47: /* case_stmt: CASE NUMBER ':' M stmt_list  */
#line 359 "for3Add1.y"
    {
        if (!(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in case_stmt"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->case_val = (yyvsp[-3].num);
        (yyval.attr)->quad = (yyvsp[-1].attr)->quad;
        (yyval.attr)->break_list = (yyvsp[0].attr)->break_list;
        (yyval.attr)->next_list = (yyvsp[0].attr)->next_list;

        // Emit comparison with switch expression (to be inherited from switch_stmt)
        char *case_value = int_to_string((yyvsp[-3].num));
        char *temp = new_temp();
        emit("==", "switch_expr", case_value, temp); // Placeholder for switch expression
        emit("if==", "switch_expr", case_value, int_to_string((yyvsp[-1].attr)->quad));
        (yyval.attr)->next_list = merge((yyval.attr)->next_list, make_list(next_quad));
        emit("goto", NULL, NULL, "0"); // Jump to next case or end
        free(case_value);
        free(temp);
    }
#line 1732 "for3Add1.tab.c"
    break;

  case 48: /* default_stmt: DEFAULT ':' M stmt_list  */
#line 380 "for3Add1.y"
    {
        if (!(yyvsp[-1].attr) || !(yyvsp[0].attr)) { yyerror("Internal error: NULL attr in default_stmt"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->quad = (yyvsp[-1].attr)->quad;
        (yyval.attr)->break_list = (yyvsp[0].attr)->break_list;
        (yyval.attr)->next_list = (yyvsp[0].attr)->next_list;
    }
#line 1744 "for3Add1.tab.c"
    break;

  case 49: /* break_stmt: BREAK ';'  */
#line 390 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->break_list = make_list(next_quad - 1);
    }
#line 1754 "for3Add1.tab.c"
    break;

  case 50: /* continue_stmt: CONTINUE ';'  */
#line 398 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->continue_list = make_list(next_quad - 1);
    }
#line 1764 "for3Add1.tab.c"
    break;

  case 51: /* return_stmt: RETURN expr ';'  */
#line 406 "for3Add1.y"
    {
        if (!(yyvsp[-1].attr) || !(yyvsp[-1].attr)->place) { yyerror("Internal error: NULL attr/place in return expr"); exit(1); }
        emit("return", (yyvsp[-1].attr)->place, NULL, NULL);
        (yyval.attr) = create_attr();
    }
#line 1774 "for3Add1.tab.c"
    break;

  case 52: /* return_stmt: RETURN ';'  */
#line 412 "for3Add1.y"
    {
        emit("return", NULL, NULL, NULL);
        (yyval.attr) = create_attr();
    }
#line 1783 "for3Add1.tab.c"
    break;

  case 53: /* expr: assign_expr  */
#line 418 "for3Add1.y"
                   { (yyval.attr) = (yyvsp[0].attr); }
#line 1789 "for3Add1.tab.c"
    break;

  case 54: /* assign_expr: var '=' expr  */
#line 421 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[0].attr) || !(yyvsp[-2].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in assign"); exit(1); }
        emit("=", (yyvsp[0].attr)->place, NULL, (yyvsp[-2].attr)->place);
        (yyval.attr) = (yyvsp[-2].attr);
        (yyval.attr)->true_list = (yyval.attr)->false_list = (yyval.attr)->next_list = NULL;
    }
#line 1800 "for3Add1.tab.c"
    break;

  case 55: /* assign_expr: log_or_expr  */
#line 427 "for3Add1.y"
                  { (yyval.attr) = (yyvsp[0].attr); }
#line 1806 "for3Add1.tab.c"
    break;

  case 56: /* log_or_expr: log_or_expr OR M log_and_expr  */
#line 431 "for3Add1.y"
    {
        if (!(yyvsp[-3].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr) || !(yyvsp[-3].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in OR"); exit(1); }
        backpatch((yyvsp[-3].attr)->false_list, (yyvsp[-1].attr)->quad);
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("||", (yyvsp[-3].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        (yyval.attr)->true_list = merge((yyvsp[-3].attr)->true_list, (yyvsp[0].attr)->true_list);
        (yyval.attr)->false_list = (yyvsp[0].attr)->false_list;
        (yyval.attr)->quad = (yyvsp[-3].attr)->quad;
    }
#line 1821 "for3Add1.tab.c"
    break;

  case 57: /* log_or_expr: log_and_expr  */
#line 441 "for3Add1.y"
                   { (yyval.attr) = (yyvsp[0].attr); }
#line 1827 "for3Add1.tab.c"
    break;

  case 58: /* log_and_expr: log_and_expr AND M rel_expr  */
#line 445 "for3Add1.y"
    {
        if (!(yyvsp[-3].attr) || !(yyvsp[-1].attr) || !(yyvsp[0].attr) || !(yyvsp[-3].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in AND"); exit(1); }
        backpatch((yyvsp[-3].attr)->true_list, (yyvsp[-1].attr)->quad);
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("&&", (yyvsp[-3].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        (yyval.attr)->true_list = (yyvsp[0].attr)->true_list;
        (yyval.attr)->false_list = merge((yyvsp[-3].attr)->false_list, (yyvsp[0].attr)->false_list);
        (yyval.attr)->quad = (yyvsp[-3].attr)->quad;
    }
#line 1842 "for3Add1.tab.c"
    break;

  case 59: /* log_and_expr: rel_expr  */
#line 455 "for3Add1.y"
               { (yyval.attr) = (yyvsp[0].attr); }
#line 1848 "for3Add1.tab.c"
    break;

  case 60: /* rel_expr: add_expr EQ add_expr  */
#line 459 "for3Add1.y"
    {
        if(!(yyvsp[-2].attr)||!(yyvsp[0].attr)||!(yyvsp[-2].attr)->place||!(yyvsp[0].attr)->place){yyerror("Null attr/place"); exit(1);}
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("==", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        emit("if==", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, "0");
        (yyval.attr)->true_list = make_list(next_quad-1);
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->false_list = make_list(next_quad-1);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1864 "for3Add1.tab.c"
    break;

  case 61: /* rel_expr: add_expr NE add_expr  */
#line 471 "for3Add1.y"
    {
        if(!(yyvsp[-2].attr)||!(yyvsp[0].attr)||!(yyvsp[-2].attr)->place||!(yyvsp[0].attr)->place){yyerror("Null attr/place"); exit(1);}
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("!=", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        emit("if!=", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, "0");
        (yyval.attr)->true_list = make_list(next_quad-1);
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->false_list = make_list(next_quad-1);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1880 "for3Add1.tab.c"
    break;

  case 62: /* rel_expr: add_expr LT add_expr  */
#line 483 "for3Add1.y"
    {
        if(!(yyvsp[-2].attr)||!(yyvsp[0].attr)||!(yyvsp[-2].attr)->place||!(yyvsp[0].attr)->place){yyerror("Null attr/place"); exit(1);}
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("<", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        emit("if<", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, "0");
        (yyval.attr)->true_list = make_list(next_quad-1);
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->false_list = make_list(next_quad-1);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1896 "for3Add1.tab.c"
    break;

  case 63: /* rel_expr: add_expr GT add_expr  */
#line 495 "for3Add1.y"
    {
        if(!(yyvsp[-2].attr)||!(yyvsp[0].attr)||!(yyvsp[-2].attr)->place||!(yyvsp[0].attr)->place){yyerror("Null attr/place"); exit(1);}
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit(">", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        emit("if>", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, "0");
        (yyval.attr)->true_list = make_list(next_quad-1);
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->false_list = make_list(next_quad-1);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1912 "for3Add1.tab.c"
    break;

  case 64: /* rel_expr: add_expr LE add_expr  */
#line 507 "for3Add1.y"
    {
        if(!(yyvsp[-2].attr)||!(yyvsp[0].attr)||!(yyvsp[-2].attr)->place||!(yyvsp[0].attr)->place){yyerror("Null attr/place"); exit(1);}
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("<=", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        emit("if<=", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, "0");
        (yyval.attr)->true_list = make_list(next_quad-1);
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->false_list = make_list(next_quad-1);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1928 "for3Add1.tab.c"
    break;

  case 65: /* rel_expr: add_expr GE add_expr  */
#line 519 "for3Add1.y"
    {
        if(!(yyvsp[-2].attr)||!(yyvsp[0].attr)||!(yyvsp[-2].attr)->place||!(yyvsp[0].attr)->place){yyerror("Null attr/place"); exit(1);}
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit(">=", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        emit("if>=", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, "0");
        (yyval.attr)->true_list = make_list(next_quad-1);
        emit("goto", NULL, NULL, "0");
        (yyval.attr)->false_list = make_list(next_quad-1);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1944 "for3Add1.tab.c"
    break;

  case 66: /* rel_expr: add_expr  */
#line 531 "for3Add1.y"
    {
        (yyval.attr) = (yyvsp[0].attr);
        if ((yyval.attr)) {
            (yyval.attr)->true_list = NULL;
            (yyval.attr)->false_list = NULL;
        } else {
            (yyval.attr) = create_attr();
        }
    }
#line 1958 "for3Add1.tab.c"
    break;

  case 67: /* add_expr: add_expr '+' mult_expr  */
#line 543 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[0].attr) || !(yyvsp[-2].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in '+'"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("+", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1970 "for3Add1.tab.c"
    break;

  case 68: /* add_expr: add_expr '-' mult_expr  */
#line 551 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[0].attr) || !(yyvsp[-2].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in '-'"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("-", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 1982 "for3Add1.tab.c"
    break;

  case 69: /* add_expr: mult_expr  */
#line 558 "for3Add1.y"
                { (yyval.attr) = (yyvsp[0].attr); }
#line 1988 "for3Add1.tab.c"
    break;

  case 70: /* mult_expr: mult_expr '*' factor  */
#line 562 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[0].attr) || !(yyvsp[-2].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in '*'"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("*", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 2000 "for3Add1.tab.c"
    break;

  case 71: /* mult_expr: mult_expr '/' factor  */
#line 570 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[0].attr) || !(yyvsp[-2].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in '/'"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("/", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 2012 "for3Add1.tab.c"
    break;

  case 72: /* mult_expr: mult_expr '%' factor  */
#line 578 "for3Add1.y"
    {
        if (!(yyvsp[-2].attr) || !(yyvsp[0].attr) || !(yyvsp[-2].attr)->place || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in '%'"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("%", (yyvsp[-2].attr)->place, (yyvsp[0].attr)->place, (yyval.attr)->place);
        (yyval.attr)->quad = (yyvsp[-2].attr)->quad;
    }
#line 2024 "for3Add1.tab.c"
    break;

  case 73: /* mult_expr: factor  */
#line 585 "for3Add1.y"
             { (yyval.attr) = (yyvsp[0].attr); }
#line 2030 "for3Add1.tab.c"
    break;

  case 74: /* factor: primary  */
#line 588 "for3Add1.y"
                 { (yyval.attr) = (yyvsp[0].attr); }
#line 2036 "for3Add1.tab.c"
    break;

  case 75: /* primary: '(' expr ')'  */
#line 590 "for3Add1.y"
                       { (yyval.attr) = (yyvsp[-1].attr); }
#line 2042 "for3Add1.tab.c"
    break;

  case 76: /* primary: var  */
#line 591 "for3Add1.y"
          { (yyval.attr) = (yyvsp[0].attr); }
#line 2048 "for3Add1.tab.c"
    break;

  case 77: /* primary: call  */
#line 592 "for3Add1.y"
           { (yyval.attr) = (yyvsp[0].attr); }
#line 2054 "for3Add1.tab.c"
    break;

  case 78: /* primary: NUMBER  */
#line 593 "for3Add1.y"
             { (yyval.attr) = create_attr(); (yyval.attr)->place =int_to_string((yyvsp[0].num)); }
#line 2060 "for3Add1.tab.c"
    break;

  case 79: /* primary: FLOAT_NUM  */
#line 595 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
        char fnum_str[50];
        sprintf(fnum_str, "%f", (yyvsp[0].fnum));
        (yyval.attr)->place = strdup(fnum_str);
        if (!(yyval.attr)->place) { yyerror("strdup failed for float"); exit(1); }
    }
#line 2072 "for3Add1.tab.c"
    break;

  case 80: /* var: ID  */
#line 605 "for3Add1.y"
    {
        (yyval.attr) = create_attr();
        (yyval.attr)->place = strdup((yyvsp[0].id));
        if (!(yyval.attr)->place) { yyerror("strdup failed for var ID"); exit(1); }
        free((yyvsp[0].id));
    }
#line 2083 "for3Add1.tab.c"
    break;

  case 81: /* call: ID '(' args ')'  */
#line 614 "for3Add1.y"
    {
        if (!(yyvsp[-3].id)) { yyerror("Internal error: NULL function ID"); exit(1); }
        (yyval.attr) = create_attr();
        (yyval.attr)->place = new_temp();
        emit("call", (yyvsp[-3].id), NULL, (yyval.attr)->place);
        (yyval.attr)->quad = next_quad - 1;
        free((yyvsp[-3].id));
    }
#line 2096 "for3Add1.tab.c"
    break;

  case 82: /* args: arg_list  */
#line 624 "for3Add1.y"
                { }
#line 2102 "for3Add1.tab.c"
    break;

  case 83: /* args: %empty  */
#line 625 "for3Add1.y"
        { }
#line 2108 "for3Add1.tab.c"
    break;

  case 84: /* arg_list: arg_list ',' expr  */
#line 629 "for3Add1.y"
    {
        if (!(yyvsp[0].attr) || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in arg list"); exit(1); }
        emit("param", (yyvsp[0].attr)->place, NULL, NULL);
    }
#line 2117 "for3Add1.tab.c"
    break;

  case 85: /* arg_list: expr  */
#line 634 "for3Add1.y"
    {
        if (!(yyvsp[0].attr) || !(yyvsp[0].attr)->place) { yyerror("Internal error: NULL attr/place in arg list base"); exit(1); }
        emit("param", (yyvsp[0].attr)->place, NULL, NULL);
    }
#line 2126 "for3Add1.tab.c"
    break;


#line 2130 "for3Add1.tab.c"

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

#line 640 "for3Add1.y"


void emit(char *op, char *arg1, char *arg2, char *result) {
    if (next_quad >= 1000) { fprintf(stderr, "Error: Code array overflow\n"); exit(1); }
    char* op_copy = op ? strdup(op) : NULL;
    char* arg1_copy = arg1 ? strdup(arg1) : NULL;
    char* arg2_copy = arg2 ? strdup(arg2) : NULL;
    char* result_copy = result ? strdup(result) : NULL;
    if ((op && !op_copy) || (arg1 && !arg1_copy) || (arg2 && !arg2_copy) || (result && !result_copy)) {
        yyerror("strdup failed in emit"); free(op_copy); free(arg1_copy); free(arg2_copy); free(result_copy); exit(1);
    }
    code[next_quad].op = op_copy; code[next_quad].arg1 = arg1_copy; code[next_quad].arg2 = arg2_copy; code[next_quad].result = result_copy;
    next_quad++;
}

char* new_temp(void) {
    char temp[20]; sprintf(temp, "t%d", temp_count++); char* temp_copy = strdup(temp);
    if (!temp_copy) { yyerror("strdup failed for new_temp"); exit(1); } return temp_copy;
}

char* int_to_string(int value) {
    char temp[20]; sprintf(temp, "%d", value); char* value_copy = strdup(temp);
    if (!value_copy) { yyerror("strdup failed for int_to_string"); exit(1); } return value_copy;
}

struct list* make_list(int quad_index) {
    struct list *l = (struct list*)malloc(sizeof(struct list)); if (!l) { yyerror("malloc failed in make_list"); exit(1); }
    l->quad_index = quad_index; l->next = NULL; return l;
}

struct list* merge(struct list *l1, struct list *l2) {
    if (!l1) return l2; if (!l2) return l1; struct list *temp = l1; while (temp->next) temp = temp->next;
    temp->next = l2; return l1;
}

void ensure_boolean_lists(attr* expr_attr) {
    if (!expr_attr) { yyerror("Internal error: NULL expression attribute"); exit(1); }
    if (expr_attr->true_list == NULL && expr_attr->false_list == NULL) {
        if (!expr_attr->place) {
            yyerror("Internal error: Expression used as condition has no 'place'");
            expr_attr->place = strdup("error_placeholder");
            if (!expr_attr->place) exit(1);
        }
        char *zero_str = strdup("0");
        if (!zero_str) { yyerror("strdup failed for '0'"); exit(1); }
        expr_attr->true_list = make_list(next_quad);
        emit("if!=", expr_attr->place, zero_str, "0");
        expr_attr->false_list = make_list(next_quad);
        emit("goto", NULL, NULL, "0");
        free(zero_str);
    } else if (expr_attr->true_list == NULL || expr_attr->false_list == NULL) {
        yyerror("Internal error: Inconsistent boolean lists in expression"); exit(1);
    }
}

void backpatch(struct list *l, int target_quad) {
    if (!l) return;
    char *target_str = int_to_string(target_quad);
    struct list *current = l;
    struct list *next_node = NULL;
    while (current) {
        int quad_idx = current->quad_index;
        if (quad_idx >= 0 && quad_idx < next_quad) {
            char* old_result = code[quad_idx].result;
            code[quad_idx].result = strdup(target_str);
            if (!code[quad_idx].result) { yyerror("strdup failed in backpatch"); exit(1); }
            if (old_result) { free(old_result); }
        } else { fprintf(stderr, "Warning: Invalid quad index %d encountered during backpatching.\n", quad_idx); }
        next_node = current->next;
        free(current);
        current = next_node;
    }
    free(target_str);
}

void yyerror(char *s) {
    fprintf(stderr, "\nSyntax error: %s at line %d near '%s'\n", s, yylineno, yytext); exit(1);
}

void print_three_address_code() {
    printf("\n----- THREE ADDRESS CODE -----\n");
    for (int i = 0; i < next_quad; i++) {
        printf("L%d:\t", i);
        if (!code[i].op) { printf("(empty)\n"); continue; }
        if (strcmp(code[i].op, "=") == 0) {
            printf("%s = %s\n", code[i].result ? code[i].result : "?", code[i].arg1 ? code[i].arg1 : "?");
        } else if (strncmp(code[i].op, "if", 2) == 0) {
            printf("if %s %s %s goto L%s\n",
                  code[i].arg1 ? code[i].arg1 : "?",
                  &code[i].op[2],
                  code[i].arg2 ? code[i].arg2 : "?",
                  code[i].result ? code[i].result : "?");
        } else if (strcmp(code[i].op, "goto") == 0) {
            printf("goto L%s\n", code[i].result ? code[i].result : "?");
        } else if (strcmp(code[i].op, "param") == 0) {
            printf("param %s\n", code[i].arg1 ? code[i].arg1 : "?");
        } else if (strcmp(code[i].op, "call") == 0) {
            printf("%s = call %s\n", code[i].result ? code[i].result : "?", code[i].arg1 ? code[i].arg1 : "?");
        } else if (strcmp(code[i].op, "return") == 0) {
            if (code[i].arg1)
                printf("return %s\n", code[i].arg1);
            else
                printf("return\n");
        } else if (strcmp(code[i].op, "func_begin") == 0 || strcmp(code[i].op, "func_end") == 0) {
            printf("%s %s\n", code[i].op, code[i].arg1 ? code[i].arg1 : "?");
        } else if (strcmp(code[i].op, "case") == 0) {
            printf("case %s:\n", code[i].arg1 ? code[i].arg1 : "?");
        } else if (strcmp(code[i].op, "default") == 0) {
            printf("default:\n");
        } else if (code[i].arg2) {
            printf("%s = %s %s %s\n",
                   code[i].result ? code[i].result : "?",
                   code[i].arg1 ? code[i].arg1 : "?",
                   code[i].op,
                   code[i].arg2 ? code[i].arg2 : "?");
        } else if (code[i].arg1) {
            printf("%s = %s %s\n",
                   code[i].result ? code[i].result : "?",
                   code[i].op,
                   code[i].arg1 ? code[i].arg1 : "?");
        } else {
            printf("%s\n", code[i].op);
        }
    }
    printf("---------------------------\n");
}

int main() {
    if (yyparse() == 0) {
        print_three_address_code();
    } else {
        printf("Parsing failed.\n");
    }
    for(int i=0; i< symbol_count; ++i) {
        if (symbol_table[i].name) free(symbol_table[i].name);
        if (symbol_table[i].type) free(symbol_table[i].type);
        symbol_table[i].name = NULL;
        symbol_table[i].type = NULL;
    }
    for (int i = 0; i < next_quad; i++) {
        if(code[i].op) free(code[i].op);
        if(code[i].arg1) free(code[i].arg1);
        if(code[i].arg2) free(code[i].arg2);
        if(code[i].result) free(code[i].result);
        code[i].op = code[i].arg1 = code[i].arg2 = code[i].result = NULL;
    }
    return 0;
}
