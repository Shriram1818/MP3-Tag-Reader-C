#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"edit.h"
#include"types.h"

Status read_validate_edit_args(char *argv[],Editinfo *editinfo)
{
    if(argv[4]==NULL)
    {
        printf("ERROR: Please select valid .mp3 file\n");
        return v_failure;
    }
    if(strstr(argv[4],".mp3"))
    {
        editinfo->mp3_edit=argv[4];
    }
    if(argv[2]==NULL)
    {
        printf("ERROR:Please select valid edit argument\n");
        return v_failure;
    }
    if (strcmp(argv[2], "-t") == 0 )
      editinfo->tag="TIT2";
     else if(strcmp(argv[2],"-a")==0)
      editinfo->tag="TPE1";
     else if(strcmp(argv[2],"-A")==0)
      editinfo->tag="TALB";
      else if(strcmp(argv[2],"-m")==0)
        editinfo->tag="COMM";
     else if(strcmp(argv[2],"-c")==0)
      editinfo->tag="TYER";
    else{
        printf("Invalid tag option %s\n",argv[2]);
        return v_failure;
    }
        editinfo->frame_id_to_edit = argv[2];           
         editinfo->new_value=argv[3];   
        return v_success;  
}
Status edit_open_files(Editinfo *editinfo)
{
    editinfo->fptr_mp3_edit=fopen(editinfo->mp3_edit,"r+");
    if(editinfo->fptr_mp3_edit==NULL)
   {
    perror("fopen");
    fprintf(stderr,"ERROR: File opened is not mp3 file\n");
    return v_failure;
   }
   
   return v_success;
}
Status edit_tag(Editinfo *editinfo)
{
    char header[10] = {0};
    fread(header, 1, 10, editinfo->fptr_mp3_edit);

    if(header[0] != 'I' || header[1] != 'D' || header[2] != '3')
    {
        printf("ERROR: Invalid tag found\n");
        return v_failure;
    }

    while(1)
    {
        char frame_id[5] = {0};
        if(fread(frame_id, 1, 4, editinfo->fptr_mp3_edit) != 4)
            break;

        unsigned char size_bytes[4];
        if(fread(size_bytes, 1, 4, editinfo->fptr_mp3_edit) != 4)
            break;

        int size = (size_bytes[0] << 24) | (size_bytes[1] << 16) | (size_bytes[2] << 8) | size_bytes[3];

        // Skip flags (2 bytes)
        fseek(editinfo->fptr_mp3_edit, 2, SEEK_CUR);

        if(strcmp(frame_id, editinfo->tag) == 0)
        {
            printf("Found %s tag, replacing it with '%s'\n", frame_id, editinfo->new_value);

            long current_pos = ftell(editinfo->fptr_mp3_edit);

            int new_value_len = strlen(editinfo->new_value);

            // Move pointer to start of text (after encoding byte)
            fseek(editinfo->fptr_mp3_edit, current_pos, SEEK_SET);

            // Write encoding byte (0x00 for ISO-8859-1)
            fputc(0x00, editinfo->fptr_mp3_edit);

            // Write new value
            fwrite(editinfo->new_value, 1, new_value_len, editinfo->fptr_mp3_edit);

            // Pad remaining bytes with zeros
            for(int i = new_value_len + 1; i < size; i++)
                fputc('\0', editinfo->fptr_mp3_edit);

            return v_success;
        }
        else
        {
            // Skip the rest of the frame
            fseek(editinfo->fptr_mp3_edit, size, SEEK_CUR);
        }
    }

    printf("Tag '%s' not found in the file.\n", editinfo->tag);
    return v_failure;
}
