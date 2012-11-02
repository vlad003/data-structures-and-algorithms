/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE":
 * <Andrei Vacariu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

enum RET_STATUSES {
    ST_OK = 0,          // complete success!
    ST_FAIL,        // general failure
    ST_FAIL_EMPTY,
    ST_FAIL_NOT_EMPTY,
    ST_FAIL_MALLOC // memory allocation issues
};

typedef enum RET_STATUSES RET_STATUS;
