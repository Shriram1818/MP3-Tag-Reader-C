#ifndef TYPES_H
#define TYPES_H
#define MAX_TAG_VALUE 512


typedef enum
{
    v_view,
    v_edit,
    v_help,
    v_invalid,
}Operationtype;
typedef enum
{
     v_success,
     v_failure,
}Status;
#endif