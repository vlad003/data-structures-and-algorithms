enum RET_STATUSES {
    ST_OK,          // complete success!
    ST_FAIL,        // general failure
    ST_FAIL_EMPTY,
    ST_FAIL_NOT_EMPTY,
    ST_FAIL_MALLOC // memory allocation issues
};

typedef enum RET_STATUSES RET_STATUS;
