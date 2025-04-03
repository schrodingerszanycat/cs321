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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int line_num;
extern FILE *yyin;
extern int yylex();
void yyerror(const char *s);

// Symbol table structure
typedef struct {
    char *name;
    char *type;
    int scope;
} Symbol;

// Symbol table
Symbol symbol_table[1000];
int symbol_count = 0;

// Three-address code generation
int temp_var_count = 0;
int label_count = 0;
char *current_type;

// Stack for handling nested scopes
int scope_stack[100];
int scope_stack_top = 0;
int current_scope = 0;

// Control flow label stacks
typedef struct {
    int start_label;
    int end_label;
} ControlLabels;

ControlLabels control_stack[100];
int control_stack_top = 0;

// Function prototypes
void enter_scope();
void exit_scope();
int add_symbol(char *name, char *type);
int lookup_symbol(char *name);
char* new_temp();
int new_label();
void emit(char *format, ...);
void push_control(int start, int end);
void pop_control();
ControlLabels top_control();

#line 125 "y.tab.c"

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
    ID = 258,                      /* ID  */
    INT_CONST = 259,               /* INT_CONST  */
    FLOAT_CONST = 260,             /* FLOAT_CONST  */
    STRING = 261,                  /* STRING  */
    CHAR_CONST = 262,              /* CHAR_CONST  */
    INT = 263,                     /* INT  */
    FLOAT = 264,                   /* FLOAT  */
    CHAR = 265,                    /* CHAR  */
    VOID = 266,                    /* VOID  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    FOR = 270,                     /* FOR  */
    RETURN = 271,                  /* RETURN  */
    PLUS = 272,                    /* PLUS  */
    MINUS = 273,                   /* MINUS  */
    MULT = 274,                    /* MULT  */
    DIV = 275,                     /* DIV  */
    MOD = 276,                     /* MOD  */
    ASSIGN = 277,                  /* ASSIGN  */
    PLUS_ASSIGN = 278,             /* PLUS_ASSIGN  */
    MINUS_ASSIGN = 279,            /* MINUS_ASSIGN  */
    MULT_ASSIGN = 280,             /* MULT_ASSIGN  */
    DIV_ASSIGN = 281,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 282,              /* MOD_ASSIGN  */
    INC = 283,                     /* INC  */
    DEC = 284,                     /* DEC  */
    EQ = 285,                      /* EQ  */
    NEQ = 286,                     /* NEQ  */
    GT = 287,                      /* GT  */
    LT = 288,                      /* LT  */
    GTE = 289,                     /* GTE  */
    LTE = 290,                     /* LTE  */
    AND = 291,                     /* AND  */
    OR = 292,                      /* OR  */
    NOT = 293,                     /* NOT  */
    ADDR = 294,                    /* ADDR  */
    LPAREN = 295,                  /* LPAREN  */
    RPAREN = 296,                  /* RPAREN  */
    LBRACE = 297,                  /* LBRACE  */
    RBRACE = 298,                  /* RBRACE  */
    LSQUARE = 299,                 /* LSQUARE  */
    RSQUARE = 300,                 /* RSQUARE  */
    SEMI = 301,                    /* SEMI  */
    COMMA = 302,                   /* COMMA  */
    UMINUS = 303                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define INT_CONST 259
#define FLOAT_CONST 260
#define STRING 261
#define CHAR_CONST 262
#define INT 263
#define FLOAT 264
#define CHAR 265
#define VOID 266
#define IF 267
#define ELSE 268
#define WHILE 269
#define FOR 270
#define RETURN 271
#define PLUS 272
#define MINUS 273
#define MULT 274
#define DIV 275
#define MOD 276
#define ASSIGN 277
#define PLUS_ASSIGN 278
#define MINUS_ASSIGN 279
#define MULT_ASSIGN 280
#define DIV_ASSIGN 281
#define MOD_ASSIGN 282
#define INC 283
#define DEC 284
#define EQ 285
#define NEQ 286
#define GT 287
#define LT 288
#define GTE 289
#define LTE 290
#define AND 291
#define OR 292
#define NOT 293
#define ADDR 294
#define LPAREN 295
#define RPAREN 296
#define LBRACE 297
#define RBRACE 298
#define LSQUARE 299
#define RSQUARE 300
#define SEMI 301
#define COMMA 302
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 55 "parser.y"

    int ival;
    float fval;
    char *str;
    struct {
        char *place;     // Variable holding the value
        int true_label;  // Label for true branch (for boolean expressions)
        int false_label; // Label for false branch (for boolean expressions)
        char *code;      // Accumulated code
    } expr;

#line 286 "y.tab.c"

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
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT_CONST = 4,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 5,                /* FLOAT_CONST  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_CHAR_CONST = 7,                 /* CHAR_CONST  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_CHAR = 10,                      /* CHAR  */
  YYSYMBOL_VOID = 11,                      /* VOID  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_PLUS = 17,                      /* PLUS  */
  YYSYMBOL_MINUS = 18,                     /* MINUS  */
  YYSYMBOL_MULT = 19,                      /* MULT  */
  YYSYMBOL_DIV = 20,                       /* DIV  */
  YYSYMBOL_MOD = 21,                       /* MOD  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_PLUS_ASSIGN = 23,               /* PLUS_ASSIGN  */
  YYSYMBOL_MINUS_ASSIGN = 24,              /* MINUS_ASSIGN  */
  YYSYMBOL_MULT_ASSIGN = 25,               /* MULT_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 26,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 27,                /* MOD_ASSIGN  */
  YYSYMBOL_INC = 28,                       /* INC  */
  YYSYMBOL_DEC = 29,                       /* DEC  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NEQ = 31,                       /* NEQ  */
  YYSYMBOL_GT = 32,                        /* GT  */
  YYSYMBOL_LT = 33,                        /* LT  */
  YYSYMBOL_GTE = 34,                       /* GTE  */
  YYSYMBOL_LTE = 35,                       /* LTE  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_OR = 37,                        /* OR  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_ADDR = 39,                      /* ADDR  */
  YYSYMBOL_LPAREN = 40,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 41,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 42,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 43,                    /* RBRACE  */
  YYSYMBOL_LSQUARE = 44,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 45,                   /* RSQUARE  */
  YYSYMBOL_SEMI = 46,                      /* SEMI  */
  YYSYMBOL_COMMA = 47,                     /* COMMA  */
  YYSYMBOL_UMINUS = 48,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_external_declaration = 51,      /* external_declaration  */
  YYSYMBOL_function_definition = 52,       /* function_definition  */
  YYSYMBOL_53_1 = 53,                      /* $@1  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_parameter_list = 55,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 56,     /* parameter_declaration  */
  YYSYMBOL_declaration = 57,               /* declaration  */
  YYSYMBOL_58_3 = 58,                      /* $@3  */
  YYSYMBOL_declaration_list = 59,          /* declaration_list  */
  YYSYMBOL_declarator = 60,                /* declarator  */
  YYSYMBOL_type_specifier = 61,            /* type_specifier  */
  YYSYMBOL_compound_statement = 62,        /* compound_statement  */
  YYSYMBOL_63_4 = 63,                      /* $@4  */
  YYSYMBOL_statement_list = 64,            /* statement_list  */
  YYSYMBOL_statement = 65,                 /* statement  */
  YYSYMBOL_expr_statement = 66,            /* expr_statement  */
  YYSYMBOL_selection_statement = 67,       /* selection_statement  */
  YYSYMBOL_if_statement = 68,              /* if_statement  */
  YYSYMBOL_if_else_statement = 69,         /* if_else_statement  */
  YYSYMBOL_iteration_statement = 70,       /* iteration_statement  */
  YYSYMBOL_71_5 = 71,                      /* @5  */
  YYSYMBOL_72_6 = 72,                      /* @6  */
  YYSYMBOL_73_7 = 73,                      /* $@7  */
  YYSYMBOL_expr = 74,                      /* expr  */
  YYSYMBOL_assignment_expr = 75,           /* assignment_expr  */
  YYSYMBOL_logical_expr = 76,              /* logical_expr  */
  YYSYMBOL_relational_expr = 77,           /* relational_expr  */
  YYSYMBOL_additive_expr = 78,             /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 79,       /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 80,                /* unary_expr  */
  YYSYMBOL_postfix_expr = 81,              /* postfix_expr  */
  YYSYMBOL_primary_expr = 82,              /* primary_expr  */
  YYSYMBOL_argument_list = 83              /* argument_list  */
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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   216

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   100,   100,   101,   105,   106,   111,   110,   122,   121,
     135,   136,   140,   148,   147,   155,   156,   160,   164,   172,
     173,   174,   175,   179,   179,   183,   189,   190,   194,   197,
     200,   203,   206,   209,   213,   220,   223,   229,   232,   238,
     252,   270,   270,   289,   307,   289,   332,   339,   343,   348,
     355,   362,   369,   376,   386,   390,   395,   403,   407,   412,
     417,   422,   427,   432,   440,   444,   449,   457,   461,   466,
     471,   479,   483,   489,   495,   500,   508,   512,   518,   524,
     529,   537,   545,   551,   557,   561,   565,   572,   575
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT_CONST",
  "FLOAT_CONST", "STRING", "CHAR_CONST", "INT", "FLOAT", "CHAR", "VOID",
  "IF", "ELSE", "WHILE", "FOR", "RETURN", "PLUS", "MINUS", "MULT", "DIV",
  "MOD", "ASSIGN", "PLUS_ASSIGN", "MINUS_ASSIGN", "MULT_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "INC", "DEC", "EQ", "NEQ", "GT", "LT", "GTE",
  "LTE", "AND", "OR", "NOT", "ADDR", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LSQUARE", "RSQUARE", "SEMI", "COMMA", "UMINUS", "$accept",
  "program", "external_declaration", "function_definition", "$@1", "$@2",
  "parameter_list", "parameter_declaration", "declaration", "$@3",
  "declaration_list", "declarator", "type_specifier", "compound_statement",
  "$@4", "statement_list", "statement", "expr_statement",
  "selection_statement", "if_statement", "if_else_statement",
  "iteration_statement", "@5", "@6", "$@7", "expr", "assignment_expr",
  "logical_expr", "relational_expr", "additive_expr",
  "multiplicative_expr", "unary_expr", "postfix_expr", "primary_expr",
  "argument_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-23)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     205,   -23,   -23,   -23,   -23,   161,   -23,   -23,   -23,    -2,
     -23,   -23,   -20,    26,    14,    34,   -14,   -23,   -23,    -7,
     -23,    65,   145,   -23,    26,    30,   -23,   205,   -23,   -23,
     -23,   -23,   -23,   -23,   145,   145,   145,   145,   145,   -23,
     -23,     7,   146,    29,    61,   179,   -10,   -23,   -23,    49,
     -23,    30,   -23,   -23,   -23,   -23,   -23,    53,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   -23,   -23,   117,
     -23,    55,   -23,   -23,   146,   -23,   146,    29,    29,    29,
      29,    29,    29,    61,    61,   -23,   -23,   -23,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   -23,    38,    56,   -23,    58,
      71,   -23,   -23,   -23,   -23,    -1,   -23,   -23,   -23,   -23,
     -23,   -23,    64,   -23,   145,   145,    72,   101,   -23,    68,
     -23,   -23,   -23,   -23,    74,   145,   -23,   -23,    55,    75,
     145,   112,    55,    81,    55,   -23,   -23,   -23,   145,    87,
      55,   -23
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    19,    20,    21,    22,     0,     2,     4,     5,     0,
       1,     3,     0,     0,     0,    17,     0,    15,     8,     0,
      10,     0,     0,    14,     0,     0,     6,     0,    12,    81,
      82,    83,    84,    85,     0,     0,     0,     0,     0,    18,
      46,    47,    54,    57,    64,    67,    71,    76,    16,    23,
       9,     0,    11,    74,    72,    73,    75,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    78,     0,
      25,     0,     7,    86,    55,    67,    56,    58,    59,    60,
      61,    62,    63,    65,    66,    68,    69,    70,    48,    49,
      50,    51,    52,    53,    80,    87,     0,     0,    41,     0,
       0,    36,    32,    13,    28,     0,    26,    29,    30,    37,
      38,    31,     0,    79,     0,     0,     0,     0,    34,     0,
      24,    27,    35,    88,     0,     0,    43,    33,     0,     0,
       0,    39,     0,     0,     0,    42,    44,    40,     0,     0,
       0,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -23,   -23,   126,   -23,   -23,   -23,   -23,   105,    31,   -23,
     -23,   110,    21,   -13,   -23,   -23,    18,     9,   -23,   -23,
     -23,   -23,   -23,   -23,   -23,   -22,   -23,   -23,    28,   147,
      24,   130,   -23,   -23,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,    51,    25,    19,    20,   112,    13,
      16,    17,   113,   114,    81,   115,   116,   117,   118,   119,
     120,   121,   126,   140,   148,   122,    40,    41,    42,    43,
      44,    45,    46,    47,   106
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      39,    12,    29,    30,    31,    32,    33,     1,     2,     3,
       4,   107,    50,   108,   109,   110,    57,    34,    77,    78,
      14,     9,     1,     2,     3,     4,     9,    35,    36,    15,
      79,     8,    23,    24,    26,    21,     8,    37,    82,    38,
      27,    49,   130,    58,    59,   111,    66,    67,    21,    98,
      99,   100,   101,   102,   103,    18,    22,   105,    29,    30,
      31,    32,    33,     1,     2,     3,     4,   107,    28,   108,
     109,   110,    49,    34,    29,    30,    31,    32,    33,   123,
      68,    69,    70,    35,    36,   124,    84,    86,   129,    34,
      93,    94,    80,    37,    83,    38,   125,    49,   127,    35,
      36,   111,   133,   134,    29,    30,    31,    32,    33,    37,
     132,    38,   135,   139,   137,   138,   142,   128,   143,    34,
      29,    30,    31,    32,    33,   144,   149,   146,   150,    35,
      36,    11,    52,   131,    48,    34,   136,     0,     0,    37,
       0,    38,     0,     0,     0,    35,    36,   111,    29,    30,
      31,    32,    33,     0,     0,    37,   141,    38,   104,     0,
     145,    10,   147,    34,    53,    54,    55,    56,   151,     1,
       2,     3,     4,    35,    36,     0,    60,    61,    62,    63,
      64,    65,     0,    37,     0,    38,     0,     0,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    95,    96,
      97,    71,    72,    73,    74,    75,    76,    87,    88,    89,
      90,    91,    92,     1,     2,     3,     4
};

static const yytype_int16 yycheck[] =
{
      22,     3,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    25,    14,    15,    16,    38,    18,    28,    29,
      40,     0,     8,     9,    10,    11,     5,    28,    29,     3,
      40,     0,    46,    47,    41,    14,     5,    38,    51,    40,
      47,    42,    43,    36,    37,    46,    17,    18,    27,    71,
      72,    73,    74,    75,    76,    41,    22,    79,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,     3,    14,
      15,    16,    42,    18,     3,     4,     5,     6,     7,    41,
      19,    20,    21,    28,    29,    47,    58,    59,   110,    18,
      66,    67,    43,    38,    41,    40,    40,    42,    40,    28,
      29,    46,   124,   125,     3,     4,     5,     6,     7,    38,
      46,    40,    40,   135,    46,    41,    41,    46,   140,    18,
       3,     4,     5,     6,     7,    13,   148,    46,    41,    28,
      29,     5,    27,   115,    24,    18,   127,    -1,    -1,    38,
      -1,    40,    -1,    -1,    -1,    28,    29,    46,     3,     4,
       5,     6,     7,    -1,    -1,    38,   138,    40,    41,    -1,
     142,     0,   144,    18,    34,    35,    36,    37,   150,     8,
       9,    10,    11,    28,    29,    -1,    30,    31,    32,    33,
      34,    35,    -1,    38,    -1,    40,    -1,    -1,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    22,    23,    24,    25,    26,    27,    60,    61,    62,
      63,    64,    65,     8,     9,    10,    11
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,     9,    10,    11,    50,    51,    52,    57,    61,
       0,    51,     3,    58,    40,     3,    59,    60,    41,    55,
      56,    61,    22,    46,    47,    54,    41,    47,     3,     3,
       4,     5,     6,     7,    18,    28,    29,    38,    40,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    60,    42,
      62,    53,    56,    80,    80,    80,    80,    74,    36,    37,
      30,    31,    32,    33,    34,    35,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    40,
      43,    63,    62,    41,    77,    80,    77,    78,    78,    78,
      78,    78,    78,    79,    79,    80,    80,    80,    74,    74,
      74,    74,    74,    74,    41,    74,    83,    12,    14,    15,
      16,    46,    57,    61,    62,    64,    65,    66,    67,    68,
      69,    70,    74,    41,    47,    40,    71,    40,    46,    74,
      43,    65,    46,    74,    74,    40,    66,    46,    41,    74,
      72,    65,    41,    74,    13,    65,    46,    65,    73,    74,
      41,    65
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    53,    52,    54,    52,
      55,    55,    56,    58,    57,    59,    59,    60,    60,    61,
      61,    61,    61,    63,    62,    62,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    66,    66,    67,    67,    68,
      69,    71,    70,    72,    73,    70,    74,    75,    75,    75,
      75,    75,    75,    75,    76,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    78,    78,    78,    79,    79,    79,
      79,    80,    80,    80,    80,    80,    81,    81,    81,    81,
      81,    82,    82,    82,    82,    82,    82,    83,    83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     0,     7,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     1,     3,     1,
       1,     1,     1,     0,     4,     2,     1,     2,     1,     1,
       1,     1,     1,     3,     2,     2,     1,     1,     1,     5,
       7,     0,     6,     0,     0,    10,     1,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     2,     2,     2,     2,     1,     2,     2,     4,
       3,     1,     1,     1,     1,     1,     3,     1,     3
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
  case 6: /* $@1: %empty  */
#line 111 "parser.y"
      { 
        add_symbol((yyvsp[-3].str), (yyvsp[-4].str));
        emit("FUNCTION_BEGIN %s\n", (yyvsp[-3].str));
        enter_scope(); 
      }
#line 1474 "y.tab.c"
    break;

  case 7: /* function_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 117 "parser.y"
      { 
        emit("FUNCTION_END %s\n", (yyvsp[-5].str));
        exit_scope(); 
      }
#line 1483 "y.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 122 "parser.y"
      { 
        add_symbol((yyvsp[-2].str), (yyvsp[-3].str));
        emit("FUNCTION_BEGIN %s\n", (yyvsp[-2].str));
        enter_scope(); 
      }
#line 1493 "y.tab.c"
    break;

  case 9: /* function_definition: type_specifier ID LPAREN RPAREN $@2 compound_statement  */
#line 128 "parser.y"
      { 
        emit("FUNCTION_END %s\n", (yyvsp[-4].str));
        exit_scope(); 
      }
#line 1502 "y.tab.c"
    break;

  case 12: /* parameter_declaration: type_specifier ID  */
#line 140 "parser.y"
                        {
        add_symbol((yyvsp[0].str), (yyvsp[-1].str));
        emit("PARAM %s\n", (yyvsp[0].str));
    }
#line 1511 "y.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 148 "parser.y"
      { 
        current_type = (yyvsp[0].str); 
      }
#line 1519 "y.tab.c"
    break;

  case 17: /* declarator: ID  */
#line 160 "parser.y"
         {
        add_symbol((yyvsp[0].str), current_type);
        emit("DECLARE %s %s\n", current_type, (yyvsp[0].str));
    }
#line 1528 "y.tab.c"
    break;

  case 18: /* declarator: ID ASSIGN expr  */
#line 164 "parser.y"
                     {
        add_symbol((yyvsp[-2].str), current_type);
        emit("DECLARE %s %s\n", current_type, (yyvsp[-2].str));
        emit("%s = %s\n", (yyvsp[-2].str), (yyvsp[0].expr).place);
    }
#line 1538 "y.tab.c"
    break;

  case 19: /* type_specifier: INT  */
#line 172 "parser.y"
          { (yyval.str) = "int"; }
#line 1544 "y.tab.c"
    break;

  case 20: /* type_specifier: FLOAT  */
#line 173 "parser.y"
            { (yyval.str) = "float"; }
#line 1550 "y.tab.c"
    break;

  case 21: /* type_specifier: CHAR  */
#line 174 "parser.y"
           { (yyval.str) = "char"; }
#line 1556 "y.tab.c"
    break;

  case 22: /* type_specifier: VOID  */
#line 175 "parser.y"
           { (yyval.str) = "void"; }
#line 1562 "y.tab.c"
    break;

  case 23: /* $@4: %empty  */
#line 179 "parser.y"
             { enter_scope(); }
#line 1568 "y.tab.c"
    break;

  case 24: /* compound_statement: LBRACE $@4 statement_list RBRACE  */
#line 179 "parser.y"
                                                      {
        exit_scope();
        (yyval.expr).code = (yyvsp[-1].expr).code;
    }
#line 1577 "y.tab.c"
    break;

  case 25: /* compound_statement: LBRACE RBRACE  */
#line 183 "parser.y"
                    {
        (yyval.expr).code = strdup(""); /* Return a string value */
    }
#line 1585 "y.tab.c"
    break;

  case 28: /* statement: compound_statement  */
#line 194 "parser.y"
                         {
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1593 "y.tab.c"
    break;

  case 29: /* statement: expr_statement  */
#line 197 "parser.y"
                     {
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1601 "y.tab.c"
    break;

  case 30: /* statement: selection_statement  */
#line 200 "parser.y"
                          {
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1609 "y.tab.c"
    break;

  case 31: /* statement: iteration_statement  */
#line 203 "parser.y"
                          {
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1617 "y.tab.c"
    break;

  case 32: /* statement: declaration  */
#line 206 "parser.y"
                  {
        (yyval.expr).code = strdup("");
    }
#line 1625 "y.tab.c"
    break;

  case 33: /* statement: RETURN expr SEMI  */
#line 209 "parser.y"
                       {
        emit("RETURN %s\n", (yyvsp[-1].expr).place);
        (yyval.expr).code = strdup("");
    }
#line 1634 "y.tab.c"
    break;

  case 34: /* statement: RETURN SEMI  */
#line 213 "parser.y"
                  {
        emit("RETURN\n");
        (yyval.expr).code = strdup("");
    }
#line 1643 "y.tab.c"
    break;

  case 35: /* expr_statement: expr SEMI  */
#line 220 "parser.y"
                {
        (yyval.expr).code = (yyvsp[-1].expr).code;
    }
#line 1651 "y.tab.c"
    break;

  case 36: /* expr_statement: SEMI  */
#line 223 "parser.y"
           {
        (yyval.expr).code = strdup("");
    }
#line 1659 "y.tab.c"
    break;

  case 37: /* selection_statement: if_statement  */
#line 229 "parser.y"
                   {
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1667 "y.tab.c"
    break;

  case 38: /* selection_statement: if_else_statement  */
#line 232 "parser.y"
                        {
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1675 "y.tab.c"
    break;

  case 39: /* if_statement: IF LPAREN expr RPAREN statement  */
#line 238 "parser.y"
                                      {
        int true_label = new_label();
        int false_label = new_label();
        emit("%s", (yyvsp[-2].expr).code);  // Emit condition code
        emit("IF %s GOTO L%d\n", (yyvsp[-2].expr).place, true_label);
        emit("GOTO L%d\n", false_label);
        emit("LABEL L%d:\n", true_label);
        emit("%s", (yyvsp[0].expr).code);
        emit("LABEL L%d:\n", false_label);
        (yyval.expr).code = strdup("");
    }
#line 1691 "y.tab.c"
    break;

  case 40: /* if_else_statement: IF LPAREN expr RPAREN statement ELSE statement  */
#line 252 "parser.y"
                                                     {
        int true_label = new_label();
        int false_label = new_label();
        int end_label = new_label();
        emit("%s", (yyvsp[-4].expr).code);  // Emit condition code
        emit("IF %s GOTO L%d\n", (yyvsp[-4].expr).place, true_label);
        emit("GOTO L%d\n", false_label);
        emit("LABEL L%d:\n", true_label);
        emit("%s", (yyvsp[-2].expr).code);
        emit("GOTO L%d\n", end_label);
        emit("LABEL L%d:\n", false_label);
        emit("%s", (yyvsp[0].expr).code);
        emit("LABEL L%d:\n", end_label);
        (yyval.expr).code = strdup("");
    }
#line 1711 "y.tab.c"
    break;

  case 41: /* @5: %empty  */
#line 270 "parser.y"
            {
        int start_label = new_label(); 
        emit("LABEL L%d:\n", start_label);
        (yyval.ival) = start_label;
    }
#line 1721 "y.tab.c"
    break;

  case 42: /* iteration_statement: WHILE @5 LPAREN expr RPAREN statement  */
#line 274 "parser.y"
                                   {
        int true_label = new_label();
        int end_label = new_label();
        
        // Emit condition code
        emit("%s", (yyvsp[-2].expr).code);
        emit("IF %s GOTO L%d\n", (yyvsp[-2].expr).place, true_label);
        emit("GOTO L%d\n", end_label);
        
        emit("LABEL L%d:\n", true_label);
        emit("%s", (yyvsp[0].expr).code);
        emit("GOTO L%d\n", (yyvsp[-5].ival));
        emit("LABEL L%d:\n", end_label);
        (yyval.expr).code = strdup("");
    }
#line 1741 "y.tab.c"
    break;

  case 43: /* @6: %empty  */
#line 289 "parser.y"
                                {
        // Initialize labels
        int cond_label = new_label();
        int body_label = new_label();
        int update_label = new_label();
        int end_label = new_label();
        
        // Execute initialization
        emit("%s", (yyvsp[0].expr).code);
        
        // Jump to condition
        emit("LABEL L%d:\n", cond_label);
        
        // Save labels for later use
        (yyval.ival) = cond_label;
        (yyvsp[-2].ival) = body_label;
        (yyvsp[-1].ival) = update_label;
        (yyvsp[0].ival) = end_label;
    }
#line 1765 "y.tab.c"
    break;

  case 44: /* $@7: %empty  */
#line 307 "parser.y"
                {
        // If condition is true, go to body, else exit loop
        emit("IF %s GOTO L%d\n", (yyvsp[-1].expr).place, (yyvsp[-5].ival));
        emit("GOTO L%d\n", (yyvsp[-3].ival));
        
        // Body label
        emit("LABEL L%d:\n", (yyvsp[-5].ival));
    }
#line 1778 "y.tab.c"
    break;

  case 45: /* iteration_statement: FOR LPAREN expr_statement @6 expr SEMI $@7 expr RPAREN statement  */
#line 314 "parser.y"
                            {
        // After body, go to update
        emit("GOTO L%d:\n", (yyvsp[-8].ival));
        
        // Update label
        emit("LABEL L%d:\n", (yyvsp[-8].ival));
        emit("%s", (yyvsp[-2].expr).code);
        
        // Go back to condition
        emit("GOTO L%d\n", (yyvsp[-6].ival));
        
        // End label
        emit("LABEL L%d:\n", (yyvsp[-7].ival));
        (yyval.expr).code = strdup("");
    }
#line 1798 "y.tab.c"
    break;

  case 46: /* expr: assignment_expr  */
#line 332 "parser.y"
                      {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1807 "y.tab.c"
    break;

  case 47: /* assignment_expr: logical_expr  */
#line 339 "parser.y"
                   {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1816 "y.tab.c"
    break;

  case 48: /* assignment_expr: unary_expr ASSIGN expr  */
#line 343 "parser.y"
                             {
        (yyval.expr).place = (yyvsp[-2].expr).place;
        emit("%s = %s\n", (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1826 "y.tab.c"
    break;

  case 49: /* assignment_expr: unary_expr PLUS_ASSIGN expr  */
#line 348 "parser.y"
                                  {
        (yyval.expr).place = (yyvsp[-2].expr).place;
        char *temp = new_temp();
        emit("%s = %s + %s\n", temp, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        emit("%s = %s\n", (yyvsp[-2].expr).place, temp);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1838 "y.tab.c"
    break;

  case 50: /* assignment_expr: unary_expr MINUS_ASSIGN expr  */
#line 355 "parser.y"
                                   {
        (yyval.expr).place = (yyvsp[-2].expr).place;
        char *temp = new_temp();
        emit("%s = %s - %s\n", temp, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        emit("%s = %s\n", (yyvsp[-2].expr).place, temp);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1850 "y.tab.c"
    break;

  case 51: /* assignment_expr: unary_expr MULT_ASSIGN expr  */
#line 362 "parser.y"
                                  {
        (yyval.expr).place = (yyvsp[-2].expr).place;
        char *temp = new_temp();
        emit("%s = %s * %s\n", temp, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        emit("%s = %s\n", (yyvsp[-2].expr).place, temp);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1862 "y.tab.c"
    break;

  case 52: /* assignment_expr: unary_expr DIV_ASSIGN expr  */
#line 369 "parser.y"
                                 {
        (yyval.expr).place = (yyvsp[-2].expr).place;
        char *temp = new_temp();
        emit("%s = %s / %s\n", temp, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        emit("%s = %s\n", (yyvsp[-2].expr).place, temp);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1874 "y.tab.c"
    break;

  case 53: /* assignment_expr: unary_expr MOD_ASSIGN expr  */
#line 376 "parser.y"
                                 {
        (yyval.expr).place = (yyvsp[-2].expr).place;
        char *temp = new_temp();
        emit("%s = %s %% %s\n", temp, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        emit("%s = %s\n", (yyvsp[-2].expr).place, temp);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1886 "y.tab.c"
    break;

  case 54: /* logical_expr: relational_expr  */
#line 386 "parser.y"
                      {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1895 "y.tab.c"
    break;

  case 55: /* logical_expr: logical_expr AND relational_expr  */
#line 390 "parser.y"
                                       {
        (yyval.expr).place = new_temp();
        emit("%s = %s && %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1905 "y.tab.c"
    break;

  case 56: /* logical_expr: logical_expr OR relational_expr  */
#line 395 "parser.y"
                                      {
        (yyval.expr).place = new_temp();
        emit("%s = %s || %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1915 "y.tab.c"
    break;

  case 57: /* relational_expr: additive_expr  */
#line 403 "parser.y"
                    {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1924 "y.tab.c"
    break;

  case 58: /* relational_expr: relational_expr EQ additive_expr  */
#line 407 "parser.y"
                                       {
        (yyval.expr).place = new_temp();
        emit("%s = %s == %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1934 "y.tab.c"
    break;

  case 59: /* relational_expr: relational_expr NEQ additive_expr  */
#line 412 "parser.y"
                                        {
        (yyval.expr).place = new_temp();
        emit("%s = %s != %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1944 "y.tab.c"
    break;

  case 60: /* relational_expr: relational_expr GT additive_expr  */
#line 417 "parser.y"
                                       {
        (yyval.expr).place = new_temp();
        emit("%s = %s > %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1954 "y.tab.c"
    break;

  case 61: /* relational_expr: relational_expr LT additive_expr  */
#line 422 "parser.y"
                                       {
        (yyval.expr).place = new_temp();
        emit("%s = %s < %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1964 "y.tab.c"
    break;

  case 62: /* relational_expr: relational_expr GTE additive_expr  */
#line 427 "parser.y"
                                        {
        (yyval.expr).place = new_temp();
        emit("%s = %s >= %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1974 "y.tab.c"
    break;

  case 63: /* relational_expr: relational_expr LTE additive_expr  */
#line 432 "parser.y"
                                        {
        (yyval.expr).place = new_temp();
        emit("%s = %s <= %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 1984 "y.tab.c"
    break;

  case 64: /* additive_expr: multiplicative_expr  */
#line 440 "parser.y"
                          {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 1993 "y.tab.c"
    break;

  case 65: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 444 "parser.y"
                                             {
        (yyval.expr).place = new_temp();
        emit("%s = %s + %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 2003 "y.tab.c"
    break;

  case 66: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 449 "parser.y"
                                              {
        (yyval.expr).place = new_temp();
        emit("%s = %s - %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 2013 "y.tab.c"
    break;

  case 67: /* multiplicative_expr: unary_expr  */
#line 457 "parser.y"
                 {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 2022 "y.tab.c"
    break;

  case 68: /* multiplicative_expr: multiplicative_expr MULT unary_expr  */
#line 461 "parser.y"
                                          {
        (yyval.expr).place = new_temp();
        emit("%s = %s * %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 2032 "y.tab.c"
    break;

  case 69: /* multiplicative_expr: multiplicative_expr DIV unary_expr  */
#line 466 "parser.y"
                                         {
        (yyval.expr).place = new_temp();
        emit("%s = %s / %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 2042 "y.tab.c"
    break;

  case 70: /* multiplicative_expr: multiplicative_expr MOD unary_expr  */
#line 471 "parser.y"
                                         {
        (yyval.expr).place = new_temp();
        emit("%s = %s %% %s\n", (yyval.expr).place, (yyvsp[-2].expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 2052 "y.tab.c"
    break;

  case 71: /* unary_expr: postfix_expr  */
#line 479 "parser.y"
                   {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 2061 "y.tab.c"
    break;

  case 72: /* unary_expr: INC unary_expr  */
#line 483 "parser.y"
                     {
        (yyval.expr).place = new_temp();
        emit("%s = %s + 1\n", (yyval.expr).place, (yyvsp[0].expr).place);
        emit("%s = %s\n", (yyvsp[0].expr).place, (yyval.expr).place);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 2072 "y.tab.c"
    break;

  case 73: /* unary_expr: DEC unary_expr  */
#line 489 "parser.y"
                     {
        (yyval.expr).place = new_temp();
        emit("%s = %s - 1\n", (yyval.expr).place, (yyvsp[0].expr).place);
        emit("%s = %s\n", (yyvsp[0].expr).place, (yyval.expr).place);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 2083 "y.tab.c"
    break;

  case 74: /* unary_expr: MINUS unary_expr  */
#line 495 "parser.y"
                                    {
        (yyval.expr).place = new_temp();
        emit("%s = -%s\n", (yyval.expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 2093 "y.tab.c"
    break;

  case 75: /* unary_expr: NOT unary_expr  */
#line 500 "parser.y"
                     {
        (yyval.expr).place = new_temp();
        emit("%s = !%s\n", (yyval.expr).place, (yyvsp[0].expr).place);
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 2103 "y.tab.c"
    break;

  case 76: /* postfix_expr: primary_expr  */
#line 508 "parser.y"
                   {
        (yyval.expr).place = (yyvsp[0].expr).place;
        (yyval.expr).code = (yyvsp[0].expr).code;
    }
#line 2112 "y.tab.c"
    break;

  case 77: /* postfix_expr: postfix_expr INC  */
#line 512 "parser.y"
                       {
        (yyval.expr).place = new_temp();
        emit("%s = %s\n", (yyval.expr).place, (yyvsp[-1].expr).place);
        emit("%s = %s + 1\n", (yyvsp[-1].expr).place, (yyvsp[-1].expr).place);
        (yyval.expr).code = (yyvsp[-1].expr).code;
    }
#line 2123 "y.tab.c"
    break;

  case 78: /* postfix_expr: postfix_expr DEC  */
#line 518 "parser.y"
                       {
        (yyval.expr).place = new_temp();
        emit("%s = %s\n", (yyval.expr).place, (yyvsp[-1].expr).place);
        emit("%s = %s - 1\n", (yyvsp[-1].expr).place, (yyvsp[-1].expr).place);
        (yyval.expr).code = (yyvsp[-1].expr).code;
    }
#line 2134 "y.tab.c"
    break;

  case 79: /* postfix_expr: postfix_expr LPAREN argument_list RPAREN  */
#line 524 "parser.y"
                                               {
        (yyval.expr).place = new_temp();
        emit("%s = call %s\n", (yyval.expr).place, (yyvsp[-3].expr).place);
        (yyval.expr).code = (yyvsp[-3].expr).code;
    }
#line 2144 "y.tab.c"
    break;

  case 80: /* postfix_expr: postfix_expr LPAREN RPAREN  */
#line 529 "parser.y"
                                 {
        (yyval.expr).place = new_temp();
        emit("%s = call %s\n", (yyval.expr).place, (yyvsp[-2].expr).place);
        (yyval.expr).code = (yyvsp[-2].expr).code;
    }
#line 2154 "y.tab.c"
    break;

  case 81: /* primary_expr: ID  */
#line 537 "parser.y"
         {
        int idx = lookup_symbol((yyvsp[0].str));
        if (idx == -1) {
            yyerror("Undeclared variable");
        }
        (yyval.expr).place = (yyvsp[0].str);
        (yyval.expr).code = strdup("");
    }
#line 2167 "y.tab.c"
    break;

  case 82: /* primary_expr: INT_CONST  */
#line 545 "parser.y"
                {
        char temp[20];
        sprintf(temp, "%d", (yyvsp[0].ival));
        (yyval.expr).place = strdup(temp);
        (yyval.expr).code = strdup("");
    }
#line 2178 "y.tab.c"
    break;

  case 83: /* primary_expr: FLOAT_CONST  */
#line 551 "parser.y"
                  {
        char temp[20];
        sprintf(temp, "%f", (yyvsp[0].fval));
        (yyval.expr).place = strdup(temp);
        (yyval.expr).code = strdup("");
    }
#line 2189 "y.tab.c"
    break;

  case 84: /* primary_expr: STRING  */
#line 557 "parser.y"
             {
        (yyval.expr).place = (yyvsp[0].str);
        (yyval.expr).code = strdup("");
    }
#line 2198 "y.tab.c"
    break;

  case 85: /* primary_expr: CHAR_CONST  */
#line 561 "parser.y"
                 {
        (yyval.expr).place = (yyvsp[0].str);
        (yyval.expr).code = strdup("");
    }
#line 2207 "y.tab.c"
    break;

  case 86: /* primary_expr: LPAREN expr RPAREN  */
#line 565 "parser.y"
                         {
        (yyval.expr).place = (yyvsp[-1].expr).place;
        (yyval.expr).code = (yyvsp[-1].expr).code;
    }
#line 2216 "y.tab.c"
    break;

  case 87: /* argument_list: expr  */
#line 572 "parser.y"
           {
        emit("PARAM %s\n", (yyvsp[0].expr).place);
    }
#line 2224 "y.tab.c"
    break;

  case 88: /* argument_list: argument_list COMMA expr  */
#line 575 "parser.y"
                               {
        emit("PARAM %s\n", (yyvsp[0].expr).place);
    }
#line 2232 "y.tab.c"
    break;


#line 2236 "y.tab.c"

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

#line 580 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error on line %d: %s\n", line_num, s);
}

void enter_scope() {
    scope_stack[scope_stack_top++] = current_scope;
    current_scope++;
}

void exit_scope() {
    if (scope_stack_top > 0) {
        current_scope = scope_stack[--scope_stack_top];
    }
}

int add_symbol(char *name, char *type) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0 && symbol_table[i].scope == current_scope) {
            return i; // Symbol already exists in current scope
        }
    }
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].type = strdup(type);
    symbol_table[symbol_count].scope = current_scope;
    return symbol_count++;
}

int lookup_symbol(char *name) {
    for (int scope = current_scope; scope >= 0; scope--) {
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(symbol_table[i].name, name) == 0 && symbol_table[i].scope <= scope) {
                return i;
            }
        }
    }
    return -1; // Symbol not found
}

char* new_temp() {
    char *temp = (char *)malloc(10);
    sprintf(temp, "t%d", temp_var_count++);
    return temp;
}

int new_label() {
    return label_count++;
}

void emit(char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void push_control(int start, int end) {
    control_stack[control_stack_top].start_label = start;
    control_stack[control_stack_top].end_label = end;
    control_stack_top++;
}

void pop_control() {
    if (control_stack_top > 0) {
        control_stack_top--;
    }
}

ControlLabels top_control() {
    if (control_stack_top > 0) {
        return control_stack[control_stack_top - 1];
    }
    ControlLabels default_labels = {-1, -1};
    return default_labels;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    printf("Three Address Code:\n");
    printf("--------------------\n");
    yyparse();
    return 0;
}
