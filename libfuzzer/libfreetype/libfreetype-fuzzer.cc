/** 
 * libfuzzer from freetype library 
 * compile with 
 * ./make.sh libfreetype-fuzzer.cc -I/usr/include/freetype2 -lfreetype 
 */ 
#include <stdio.h> 
#include <ft2build.h> 
#include FT_FREETYPE_H 
 
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size) 
{ 
        int error; 
        FT_Library library; 
        FT_Face face; 
        error = FT_Init_FreeType( &library ); 
        if(error) return 0; 
 
        error = FT_New_Memory_Face( library, 
                                    data,    /* first byte in memory */ 
                                    size,    /* size in bytes        */ 
                                    0,       /* face_index           */ 
                                    &face ); 
        if (!error)
           FT_Done_Face    ( face ); 
        FT_Done_FreeType( library ); 
        return 0; 
} 
