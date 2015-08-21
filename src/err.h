#ifndef __ERR_H
#define __ERR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void mkerr( int errno, ... );

typedef struct err_t {
    int err;
    const char *errstr;
} err_t;

extern struct err_t errinfo[19];

enum errtype {
    OUT_JSONP,
    OUT_JSON,
    OUT_RAW
};

enum errors {
    ENOERR = 0,

    /* Configuration Errors. */
    ELOADCFG,
    EEMPTYCFG,
    EBADCFG,

    /* Database Configuration Errors. */
    EDBLOADCFG,
    EDBEMPTYCFG,
    EDBBADCFG,

    /* API Errors. */
    ENOACT,
    EBADCMD,
    EBADARGS,
    EBADREQ,
    ENODATA,

    /* Database Errors. */
    EDBCONN,
    EDBQUERY,
    EDBEXISTS,
    EDBNEXISTS,
    EDBNODATA
};

#endif /* __ERR_H */
