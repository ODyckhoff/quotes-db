#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *data;
    char *querystr = malloc( 200 );
    char *token;
    char tmp = 's';
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

            while( ( token = strsep( &querystr, "/" ) ) != 0 ) {
                if( strcmp( token, "" ) != 0 ) {
                    printf( "<li>Token %d is: '%s'</li>\n", c+1, token );
                    c++;
                }
            }
            printf( "</ul><br />\n" );
            if( c == 1 ) {
                tmp = '\0';
            }
            printf( "Total of %d token%c.<br />\n", c, tmp );
        }
    }

    return 0;        
}
