/**
 * replay file
 * compile with
 * cc -ggdb -O1 -o libfreetype-replay libfreetype-replay.c -I/usr/include/freetype2 -lfreetype
 */
#include <stdlib.h>
#include <stdio.h>
#include <ft2build.h>
#include FT_FREETYPE_H

int ReadFromFile(char* filename, unsigned char* ptr, size_t* sz)
{
        FILE *fp = fopen(filename, "r");
        if(!fp){
                printf("Failed to open %s\n", filename);
                return -1;
        }
        fseek(fp, 0L, SEEK_END);
        *sz = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        ptr = (unsigned char*) malloc(*sz);
        if(!ptr){
                printf("Failed to malloc(%d)\n", *sz);
                fclose(fp);
                return -1;
        }
        printf("Copying %d bytes from %s to %p\n", *sz, filename, ptr);
        fread(ptr, *sz, 1, fp);
        fclose(fp);
        return 0;
}
int main(int argc, char** argv, char** envp)
{
        int error;
        size_t size;
        unsigned char *data;

        if (argc!=2){
                printf("Missing replay file\n");
                exit(1);
        }
        if(ReadFromFile(argv[1], data, &size) < 0){
                exit(2);
        }

        FT_Library library;
        FT_Face face;
        error = FT_Init_FreeType( &library );
        if(error)
                return 0;

        error = FT_New_Memory_Face( library,
                                    data,    /* first byte in memory */
                                    size,    /* size in bytes        */
                                    0,       /* face_index           */
                                    &face );

        FT_Done_Face    ( face );
        FT_Done_FreeType( library );
        free(data);
        return 0;
}

