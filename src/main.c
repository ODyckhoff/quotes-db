#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "func/add.h"
#include "func/get.h"
#include "func/remove.h"
#include "func/search.h"
#include "err.h"

int main( void ) {
    char *data;
    char *query;
    char *querytmp;
    char *token;
    char **tokens;
    int err = 0;
    int i;
    int c = 0;
    int len;

    printf( "Content-Type: text/html;charset=utf-8\n\n" );
    data = getenv("QUERY_STRING");
    printf( "%s\n", data );
    query = malloc( 200 );
    memset( query, 0, 200 );

    if( data == NULL )
        mkerr( ENODATA );
    else if( ( i = sscanf( data, "path=/%[^\t\n]", query ) ) != 1 )
        mkerr( EBADREQ );
    else {
        if( strcmp( query, "/" ) == 0 )
            mkerr( ENOACT );
        else {
            printf( "Page required: %s<br />\n", query );
            printf( "<ul>\n" );

            for( c = 0, i = 0; c < strlen( query ); c++ )
                if( query[c] == '/' ) i++;

            tokens = malloc( ( i + 1 ) * sizeof( char * ) );
            memset( tokens, 0, ( i + 1 ) );
            c = 0;
            querytmp = query;

            while( ( token = strsep( &query, "/" ) ) != 0 ) {
                if( strcmp( token, "" ) != 0 ) {
                    printf( "<li>Token %d is: '%s'</li>\n", c+1, token );
                    len = strlen( token ) + 1;
                    tokens[c] = malloc( len );
                    memset( tokens[c], 0, len );
                    strncpy( tokens[c], token, strlen( token ) );
                    c++;
                }
            }
            free( token );
            free( querytmp );
            printf( "</ul><br />\n" );
            printf( "Total of %d token%s.<br />\n", 
                        c, ( c == 1 ? "" : "s" )
            );

            if( !c ) {
                mkerr( ENOACT );
                cleanup( tokens, c );
                return -1;
            }

            /* Read tokens and direct paths. */
            /* add, get, remove, search */

            if( strcmp( tokens[0], "add" ) == 0 ) {
                /* Add stuff. */
                err = addhndlr( tokens, c );
            }
            else if( strcmp( tokens[0], "get" ) == 0 ) {
                /* Get stuff. */
                err = gethndlr( tokens, c );
            }
            else if( strcmp( tokens[0], "remove" ) == 0 ) {
                /* Remove stuff. */
                err = removehndlr( tokens, c );
            }
            else if( strcmp( tokens[0], "search" ) == 0 ) {
                /* Search for stuff. */
                err = searchhndlr( tokens, c );
            }
            else {
                
                mkerr( EBADCMD, tokens[0] );
            }
        }
    }

    cleanup( tokens, c );
    return 0;

}

void cleanup( char **tokens, int c ) {
    int i;
    for( i = 0; i < c; i++ ) {
        free( tokens[i] );
    }
    free( tokens );
}
