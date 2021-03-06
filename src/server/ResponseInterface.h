#ifndef RESPONSEINTERFACE_H
#define RESPONSEINTERFACE_H

enum ResponseCode {
    DATA_SUCCESS = 1,
    DATA_ERROR = 10,
    DATA_ERROR_OPEN_DB,
    DATA_ERROR_CLOSE_DB,
    DATA_ERROR_CREATE_TB,
    DATA_ERROR_INSERT_TB,
    DATA_ERROR_SELECT_DB = 15,
    DATA_ERROR_UPDATE_DB,
    DATA_ERROR_DELETE_DB,
    DATA_SELECT_EMPTY,
    DATA_ERROR_START_TRANSACTION,
    DATA_ERROR_END_TRANSACTION = 20,
    DATA_IS_EXISTED,
    PERMISSION_DENY = 30
};

enum ResultCode {
    DONE = 1,
    URL_INVALID,
    ERROR,
    UNKNOWN,
    NOT_SUPPORT,
    FIRST_LOGIN,
    NOT_FIRST_LOGIN
};

#endif
