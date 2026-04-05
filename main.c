/*****************************MP3 Tag Reader******************************************* */
/******Shriram Pai************************************************************************** */
/*************25005_168*********************************************************************************** */
#include<stdio.h>
#include<string.h>
#include "types.h"
#include "view.h"
#include "edit.h"
Operationtype check_operation_type(char *argv[])
{
    if(argv[1]!=NULL)
    {
        if(strcmp(argv[1],"-v")==0 && argv[2]!=NULL)
        {
            return v_view;
        }
        else if(strcmp(argv[1],"-e")==0 && argv[4]!=NULL)
        {
            return v_edit;
        }
        else if(strcmp(argv[1],"--help")==0)
        {
            return v_help;
        }
    }
    return v_invalid;
}
int main(int argc,char *argv[])
{
    
    switch(check_operation_type(argv))
    {
        case v_view:
        {
        Viewinfo viewinfo ;  // Zero initialize all fields

        if(read_validate_view_args(argv,&viewinfo)== v_failure)
        {
            return v_failure;
        }
        printf("first argument is %s\n",argv[1]);
        printf("Argument is %s\n",argv[2]);
        printf("Command line argument is %s\n",argv[3]);

        if(view_open_files(&viewinfo)==v_failure)
        {
            return v_failure;
        }
        if(read_view_tag(&viewinfo)==v_failure)
        {
            return v_failure;
        }
        return v_success;
        break;
        }

        case v_edit:
        {
          Editinfo editinfo;
          if(read_validate_edit_args(argv,&editinfo)==v_failure)
          {
            return v_failure;
          }
          if(edit_open_files(&editinfo)==v_failure)
          {
            return v_failure;
          }
          if(edit_tag(&editinfo)==v_failure)
          {
            return v_failure;
          }
          return v_success;
          break;
        }
    case v_help:
    {
    printf("$ mp3 tag  --help\n");
    printf("usage: mp3tag -[va]\n");
    printf("Modifies a Title tag\n");
    printf("Modifies a Track tag\n");
    printf("Modifies an Artist tag\n");
    printf("Modifies an Album tag\n");
    printf("Modifies an Year tag\n");
    printf("Modifies an comment tag\n");
    printf("Display this version\n");
    printf("Prints version info\n");
    break;
   }
   Default:
   printf("Unsupported arguments\n");
}
}