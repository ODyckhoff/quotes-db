#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *data;
    char *querystr;
    int i;

    printf("Content-Type: text/html;charset=utf-8\n\n");
    data = getenv("QUERY_STRING");
    if( data == NULL )
        printf("<p>Error! QUERY_STRING is NULL.</p>\n");
    else if(i = sscanf(data,"path=%s", querystr)!=1)
        printf("<p>Error! Invalid data. Code: %d</p>\n", i);
    else {

        if(strcmp(querystr, "/") == 0)
            printf("{\"error\":\"No action specified.\", \"code\":\"ENOACT\"}\n");
        else {
            printf("Page required: %s", querystr);
        }
    }

    return 0;
        
}
