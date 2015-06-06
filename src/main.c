#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *data;
    char *querystr = malloc( 200 );
    char *token;
    char **tokens;
    char tmp = 's';
    int err = 0;
    int i;
    int c = 0;

    printf( "Content-Type: text/html;charset=utf-8\n\n" );
    data = getenv("QUERY_STRING");

    if( data == NULL )
        printf( "<p>Error! QUERY_STRING is NULL.</p>\n" );
    else if( ( i = sscanf( data, "path=/%s", querystr ) ) != 1 )
        printf( "<p>Error! Invalid data. Code: %d</p>\n", i );
    else {

        if( strcmp( querystr, "/" ) == 0 )
            printf( "{\"error\":\"No action specified.\", \"code\":\"ENOACT\"}\n" );
        else {
            printf( "Page required: %s<br />\n", querystr );
            printf( "<ul>\n" );

            for( c = 0, i = 0; c < strlen( querystr ); c++ )
                if( querystr[c] == '/' ) i++;

            tokens = malloc( ( i + 1 ) * sizeof( char * ) );
            c = 0;

            while( ( token = strsep( &querystr, "/" ) ) != 0 ) {
                if( strcmp( token, "" ) != 0 ) {
                    printf( "<li>Token %d is: '%s'</li>\n", c+1, token );
                    tokens[c] = malloc( strlen( token ) + 1 );
                    strncpy( tokens[c], token, strlen( token ) );
                    c++;
                }
            }
            printf( "</ul><br />\n" );
            if( c == 1 ) {
                tmp = '\0';
            }
            printf( "Total of %d token%c.<br />\n", c, tmp );

            if( !c ) {
                printf( "{\"error\":\"No action specified.\", \"code\":\"ENOACT\"}\n" );
                return -1;
            }

            /* Read tokens and direct paths. */
            /* add, get, remove, search */

            if( strcmp( tokens[i], "add" ) == 0 ) {
                /* Add stuff. */
                printf( "Adding stuff<br />\n" );
                /* e.g. err = getstuff( tokens[i + 1] ); */
            }
            else if( strcmp( tokens[i], "get" ) == 0 ) {
                /* Get stuff. */
                printf( "Getting stuff<br />\n" );
            }
            else if( strcmp( tokens[i], "remove" ) == 0 ) {
                /* Remove stuff. */
                printf( "Removing stuff<br />\n" );
            }
            else if( strcmp( tokens[i], "search" ) == 0 ) {
                /* Search for stuff. */
                printf( "Searching for stuff<br />\n" );
            }
            else {
                printf( "{\"error\":\"Unknown command '%s'.\", \"code\":\"EBADCMD\"}\n",
                        tokens[i] );
                return -2;
            }

            if( err ) return -( err );
        }
    }

    return 0;        

}
