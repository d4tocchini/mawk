
/********************************************
scan.h
copyright 1991,2014-2016 Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 3, 2007.

If you import elements of this code into another product,
you agree to not name that product mawk.
********************************************/



/* scan.h  */

#ifndef  SCAN_H_INCLUDED
#define  SCAN_H_INCLUDED   1

#include <stdio.h>

#ifndef   MAKESCAN
#include  "table.h"
#include  "parse.h"
#endif

// extern  int     scan_code_cleaned;
#define SCAN_CODE_CLEAN        //scan_code_cleaned = 1
#define SCAN_CODE_DIRTY        //scan_code_cleaned = 0

extern  int        scan_code_NL_value;
#define SCAN_CODE_SET_NL(code) scan_code_NL_value = code

 int scan_code_get(const unsigned char c);

/*  the scan codes to compactify the main switch */
#define                         SC_SPACE               1
#define                         SC_NL                  2
#define                         SC_SEMI_COLON          3
#define                         SC_FAKE_SEMI_COLON     4
#define                         SC_LBRACE              5
#define                         SC_RBRACE              6
#define                         SC_QMARK               7
#define                         SC_COLON               8
#define                         SC_OR                  9
#define                         SC_AND                10
#define                         SC_PLUS               11
#define                         SC_MINUS              12
#define                         SC_MUL                13
#define                         SC_DIV                14
#define                         SC_MOD                15
#define                         SC_POW                16
#define                         SC_LPAREN             17
#define                         SC_RPAREN             18
#define                         SC_LBOX               19
#define                         SC_RBOX               20
#define                         SC_IDCHAR             21
#define                         SC_DIGIT              22
#define                         SC_DQUOTE             23
#define                         SC_ESCAPE             24
#define                         SC_COMMENT            25
#define                         SC_EQUAL              26
#define                         SC_NOT                27
#define                         SC_LT                 28
#define                         SC_GT                 29
#define                         SC_COMMA              30
#define                         SC_DOT                31
#define                         SC_MATCH              32
#define                         SC_DOLLAR             33
#define                         SC_UNEXPECTED         34

#ifndef  MAKESCAN

void                            parse(void);
int                             yyparse(void);
void                            scan_cleanup(void);
int                             yylex(
    YYSTYPE *                       yylval
                                );
void                            _mawk_yyerror(
                                    YYSTYPE *yylval,
                                    const char *
                                );
void                            _mawk_unexpected_char(
                                    YYSTYPE *yylval
                                );
void                            eat_nl(
                                    YYSTYPE *yylval
                                );
                                    /* eat all space including newlines */

#define                         yyerror(msg) \
                                    _mawk_yyerror(&yylval, msg)
#define                         UNEXPECTED_CHAR() \
                                    _mawk_unexpected_char(yylval)
#define                         EAT_NL \
                                    eat_nl(yylval)
#define                         EAT_NL_ \
                                    eat_nl(&yylval)
#define                         EAT_NL_NULL \
                                    eat_nl(NULL)
#define                         ct_ret(x) \
                                    return current_token = (x)
#define                         next() \
                                    (*buffp ? *buffp++ : slow_next())
#define                         un_next() \
                                    buffp--
#define                         test1_ret(c,x,d) \
                                    if ( next() == (c) ) ct_ret(x) ; \
                                    else { un_next() ; ct_ret(d) ; }
#define                         test2_ret(c1,x1,c2,x2,d) \
                                    switch( next() ) \
                                       { case c1: ct_ret(x1) ;\
                                         case c2: ct_ret(x2) ;\
                                         default: un_next() ;\
                                                  ct_ret(d) ; }
#endif  /* ! MAKESCAN  */
#endif
