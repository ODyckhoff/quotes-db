#include "add.h"

int addhndlr( char **tokens, int toknum ) {

    char *category;
    char *quote;

    if( toknum != 3 ) {
        mkerr( EBADARGS, "Incorrect number of arguments to add." );
        return EBADARGS;
    }

    category = strdup( tokens[1] );
    quote = strdup( tokens[2] );

    printf( "Adding stuff.<br />\nCategory: %s<br />Quote: %s<br />\n", category, quote );

    return 0;
}
