#include "err.h"

/* define error info. */
err_t errinfo[19] = {
    { ENOERR, "No Errors: All operations completed successfully." },

    /* Configuration Errors. */
    { ELOADCFG, "Unable to load configuration file: %s." },
    { EEMPTYCFG, "Empty configuration file." },
    { EBADCFG, "Garbled configuration file." },

    /* Database Configuration Errors. */
    { EDBLOADCFG, "Unable to load database configuration file: %s." },
    { EDBEMPTYCFG, "Empty database configuration file." },
    { EDBBADCFG, "Garbled database configuration file." },

    /* Data Errors. */
    { ENOACT, "No action was specified." },
    { EBADCMD, "No such command: %s." },
    { EBADARGS, "Bad argument data: %s" },
    { EBADREQ, "Bad request. No path to route." },
    { ENODATA, "Empty data set." },

    /* Database Errors. */
    { EDBCONN, "Unable to connect to database: %s." },
    { EDBQUERY, "Error executing query: %s." },
    { EDBEXISTS, "ID already exists." },
    { EDBNEXISTS, "ID doesn't exist." },
    { EDBNODATA, "No data was returned from the query." },
};

void mkerr( int errno, ... ) {

    va_list ap;
    char *outstr = malloc( 1024 );

    if( outstr == NULL ) {
        fprintf( stderr, "Unable to allocate memory.\n" );
        return;
    }

    va_start( ap, errno );
    vsprintf( outstr, errinfo[ errno ].errstr, ap );

    printf( "{ error: \"%s\", code: %#05x }", outstr, errno );
    free( outstr );
}

