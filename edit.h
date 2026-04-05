#ifndef EDIT_H
#define EDIT_H
#include "types.h"

typedef struct Editinfo
{
  FILE *fptr_mp3_edit;
    char *mp3_edit;
    char *new_value;
    char *frame_id_to_edit;
    const char *tag;
}Editinfo;

Status read_validate_edit_args(char *argv[],Editinfo *editinfo);
Status edit_open_files(Editinfo *editinfo);
Status edit_tag(Editinfo *editinfo);
#endif