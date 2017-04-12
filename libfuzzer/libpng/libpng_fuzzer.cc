/**
 * libpng fuzzer.
 *
 * Compile with:
 * $ ./make.sh libpng_fuzzer.cc -lpng
 */

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define PNG_DEBUG 3
#define PNG_BYTES_TO_CHECK 4

#include <png.h>


struct fake_file
{
                unsigned char *buf;
                unsigned int size;
                unsigned int cur;
};


void user_read_fn(png_structp pngPtr, png_bytep data, png_size_t length)
{
        struct fake_file *fp = (struct fake_file *)pngPtr;
        fp->cur += length;
}


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
        int x, y;
        int width, height;
        png_byte color_type;
        png_byte bit_depth;
        png_structp png_ptr;
        png_infop info_ptr;
        int number_of_passes;
        png_bytep* row_pointers;

        struct fake_file fd = {
                .buf = (unsigned char*)data,
                .size = size,
                .cur = 0
        };

        if (png_sig_cmp((unsigned char*)data, (png_size_t)0, PNG_BYTES_TO_CHECK))
                return 0;

        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!png_ptr)
                return 0;

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr){
                png_destroy_read_struct(&png_ptr, NULL, NULL);
                return 0;
        }

        if (setjmp(png_jmpbuf(png_ptr)))
                goto finish;

        png_set_read_fn(png_ptr,(png_voidp)&fd, user_read_fn);
        png_set_sig_bytes(png_ptr, 8);
        png_read_info(png_ptr, info_ptr);
        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);

        if (setjmp(png_jmpbuf(png_ptr)))
                goto finish;

        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);

        for (y=0; y<height; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

        for (y=0; y<height; y++)
                free(row_pointers[y]);

        free(row_pointers);

finish:
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return 0;
}
