#ifndef VIEW_H
#define VIEW_H
#define MAX_TAG_VALUE 512
#include "types.h"

typedef struct Viewinfo
{
    FILE *fptr_mp3_view;
    char *mp3_view;
    char title[MAX_TAG_VALUE];
    char album[MAX_TAG_VALUE];
    char artist[MAX_TAG_VALUE];
    char year[MAX_TAG_VALUE];
    char comment[MAX_TAG_VALUE];
    char genre[512];
}Viewinfo;


Operationtype check_operation_type(char *argv[]);
Status view_open_files(Viewinfo *viewinfo);
Status read_validate_view_args(char *argv[],Viewinfo *viewinfo);
Status read_view_tag(Viewinfo *viewinfo);
#endif