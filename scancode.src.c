
/********************************************
scancode.src.c
copyright 1991,2014-2016 Michael D. Brennan

This is a source file for mawk, an implementation of
the AWK programming language.

Mawk is distributed without warranty under the terms of
the GNU General Public License, version 3, 2007.

If you import elements of this code into another product,
you agree to not name that product mawk.
********************************************/

/* source for scancode.src.exe which builds the scancode[]
   via:	  scancode.src.exe > scancode.c
*/

#include <string.h>

#define MAKESCAN

#include "scan.h"

int scan_code[256];

void
scan_init( void )
{
    int * p;

    for ( p = scan_code + 1; p < scan_code + 256; p++ ) {
        *p = SC_UNEXPECTED;
    }
    for ( p = scan_code + '0'; p <= scan_code + '9'; p++ )
        *p = SC_DIGIT;

    scan_code[' '] = scan_code['\t'] = scan_code['\f'] = SC_SPACE;
    scan_code['\r'] = scan_code['\013'] = SC_SPACE;

    scan_code[';']  = SC_SEMI_COLON;
    scan_code['\n'] = SC_NL;
    scan_code['{']  = SC_LBRACE;
    scan_code['}']  = SC_RBRACE;
    scan_code['+']  = SC_PLUS;
    scan_code['-']  = SC_MINUS;
    scan_code['*']  = SC_MUL;
    scan_code['/']  = SC_DIV;
    scan_code['%']  = SC_MOD;
    scan_code['^']  = SC_POW;
    scan_code['(']  = SC_LPAREN;
    scan_code[')']  = SC_RPAREN;
    scan_code['_']  = SC_IDCHAR;
    scan_code['=']  = SC_EQUAL;
    scan_code['#']  = SC_COMMENT;
    scan_code['\"'] = SC_DQUOTE;
    scan_code[',']  = SC_COMMA;
    scan_code['!']  = SC_NOT;
    scan_code['<']  = SC_LT;
    scan_code['>']  = SC_GT;
    scan_code['|']  = SC_OR;
    scan_code['&']  = SC_AND;
    scan_code['?']  = SC_QMARK;
    scan_code[':']  = SC_COLON;
    scan_code['[']  = SC_LBOX;
    scan_code[']']  = SC_RBOX;
    scan_code['\\'] = SC_ESCAPE;
    scan_code['.']  = SC_DOT;
    scan_code['~']  = SC_MATCH;
    scan_code['$']  = SC_DOLLAR;

    for ( p = scan_code + 'A'; p <= scan_code + 'Z'; p++ )
        *p = *( p + 'a' - 'A' ) = SC_IDCHAR;
}

void
scan_print( const char * date )
{
    register int * p = scan_code;
    register int   c; /* column */
    register int   r; /* row */

    printf( "\n\n/* scancode.c */\n" );
    printf( "/* generated from scancode.src.c */\n" );
    printf( "/* %s */\n\n\n", date );

    printf( "#include \"scan.h\" \n" );

    printf( "const int scan_code[256] = {\n" );
    for ( r = 1; r <= 16; r++ ) {
        for ( c = 1; c <= 16; c++ ) {
            printf( "%2d", *p++ );
            if ( r != 16 || c != 16 )
                putchar( ',' );
        }
        putchar( '\n' );
    }
    printf( "};\n" );

    // printf( "    int     scan_code_cleaned = 0;  \n");
    printf( "    int        scan_code_NL_value = SC_NL;  \n");

    // printf( "   #define SCAN_CODE_CLEAN        scan_code_cleaned = 1  \n");
    // printf( "   #define SCAN_CODE_DIRTY        scan_code_cleaned = 0  \n");
    // printf( "   #define SCAN_CODE_SET_NL(code) scan_code_NL_value = code  \n");

    // printf( "   int _scan_code_get_clean_space(const unsigned char c) {  \n");
    // printf( "       switch (c) {                                         \n");
    // printf( "           case '\\f'   :                                    \n");
    // printf( "           case '\\013' :                                    \n");
    // printf( "           case '\\r'   :                                    \n");
    // printf( "               return SC_UNEXPECTED;                        \n");
    // printf( "       }                                                    \n");
    // printf( "       return 1;                                            \n");
    // printf( "   }                                                        \n");

    printf( "    int scan_code_get(const unsigned char c) {               \n");
    // printf( "       if (c == '\\n') return scan_code_NL_value;            \n");
    printf( "       const  int code = scan_code[c];                       \n");
    //const  int i = code * scan_code_cleaned;
     //printf(\"\\n %u %u %u \\n\", code, scan_code_cleaned, i);
    printf( "       const  int i = code ^ SC_NL;                          \n");
    printf( "       switch (i) {                  \n");
    printf( "           case 0 :                                         \n");
    printf( "               return scan_code_NL_value;            \n");
    // printf( "               return _scan_code_get_clean_space(c);        \n");
    // printf( "           case SC_SPACE : // SC_SPACE = 1                  \n");
    // printf( "               return code;                                 \n");
    printf( "       }                                                    \n");
    printf( "       return code;                                         \n");
    printf( "   }                                                        \n");
}

char dbuff[128];
const char *
get_date( void )
{
    FILE * fp = popen( "/bin/date", "r" );
    if ( fp ) {
        char * p;
        fgets( dbuff, 128, fp );
        if ( p = strchr( dbuff, '\n' ) )
            *p = 0;
        pclose( fp );
    }
    return dbuff;
}

int
main( void )
{
    scan_init();
    scan_print( get_date() );
    return 0;
}
