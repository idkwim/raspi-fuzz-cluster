/**
 * ClamaAV fuzzer
 *
 * https://github.com/vrtadmin/clamav-devel/blob/master/libclamav/scanners.c#L3596
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <clamav.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) 
{
        cl_init(CL_INIT_DEFAULT);
        struct cl_engine *engine = cl_engine_new();
        cl_engine_compile(engine);
        const char *virusName = NULL;
        long unsigned int scanned = 0;

        cl_fmap_t* map = cl_fmap_open_memory(data, size);
        cl_scanmap_callback(map, &virusName, &scanned, engine, CL_SCAN_STDOPT, NULL);
        cl_fmap_close(map);

        cl_engine_free(engine);
        return 0;
}
