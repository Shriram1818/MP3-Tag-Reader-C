#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"view.h"
#include"types.h"

Status read_validate_view_args(char *argv[],Viewinfo *viewinfo)
{
    if (argv[2] == NULL)
    {
        printf("Usage: please .mp3 file\n");
        return v_failure;
    }

   if(strstr(argv[2],".mp3")) 
   {
    viewinfo->mp3_view=argv[2];
   }
   else
   {
      printf("File is not mp3 file\n");
      return v_failure;
   }
    return v_success;                            
}
Status view_open_files(Viewinfo *viewinfo)
{
 //  printf("Trying to open:%s\n",viewinfo->mp3_view);
   viewinfo->fptr_mp3_view=fopen(viewinfo->mp3_view,"rb");
   if(viewinfo->fptr_mp3_view==NULL)
   {
    perror("fopen");
    fprintf(stderr,"ERROR: File opened is not mp3 file\n");
    return v_failure;
   }
   return v_success;

}
Status read_view_tag(Viewinfo *viewinfo)
{
    char header[10];
    if (fread(header, 1, 10, viewinfo->fptr_mp3_view) != 10)
    {
        printf("Failed to read ID3 header\n");
        return v_failure;
    }
    while (1)
    {
        //printf("While reading frames at %d bytes\n",bytes_read);
        char frame_id[4] = {0};
        if (fread(frame_id, 1, 4, viewinfo->fptr_mp3_view) != 4)
            break;

        if (frame_id[0] < 'A' || frame_id[0] > 'Z')
            break;

        unsigned char size_bytes[4];
        if (fread(size_bytes, 1, 4, viewinfo->fptr_mp3_view) != 4)
            break;

        int size = (size_bytes[0] << 24) | (size_bytes[1] << 16) |
                   (size_bytes[2] << 8) | size_bytes[3];
                   printf("Frame ID: %s | Size: %u\n", frame_id, size);

        fseek(viewinfo->fptr_mp3_view, 2, SEEK_CUR);
        if (strcmp(frame_id, "APIC") == 0) {
        printf("Skipping APIC frame (image data)\n");
        fseek(viewinfo->fptr_mp3_view, size, SEEK_CUR);
        continue;
    }

        if (size < 2)
            continue;

        unsigned char *data = malloc(size);
        if (!data)
        {
            printf("Memory allocation failed\n");
            return v_failure;
        }

        if (fread(data, 1, size, viewinfo->fptr_mp3_view) != size)
        {
            free(data);
            printf("Failed to read frame data\n");
            return v_failure;
        }

        char temp[512];
        memcpy(temp, &data[1], size - 1);  // Skip encoding byte
        temp[size - 1] = '\0';

        if (strcmp(frame_id, "TIT2") == 0)
            strcpy(viewinfo->title, temp);

        else if (strcmp(frame_id, "TPE1") == 0)
            strcpy(viewinfo->artist, temp);
        else if (strcmp(frame_id, "TALB") == 0)
            strcpy(viewinfo->album, temp);
        else if (strcmp(frame_id, "TYER") == 0)
            strcpy(viewinfo->year, temp);
        else if (strcmp(frame_id, "TCON") == 0)
        strcpy(viewinfo->comment, temp);
        free(data);
     
    }
        printf("MP3 Tag Reader and Editor for ID3v2\n");
        printf("------------------------------------\n");
        printf("TITLE :%s\n",viewinfo->title);
        printf("ARTIST:%s\n",viewinfo->artist);
        printf("ALBUM :%s\n",viewinfo->album);
        printf("YEAR:%s\n",viewinfo->year);
        printf("COMMENT :%s\n",viewinfo->comment);
        printf("ARTIST:%s\n",viewinfo->artist);
        printf("------------------------------------\n");

       

    return v_success;
}

