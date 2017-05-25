/**
 * libass fuzzer
 *
 * Compile with:
 * $ ./make.sh libass_fuzzer.cc -I. -Llibass -lass
 */

#include <stdint.h>
#include <stddef.h>

#include <libass/ass.h>
#include <libass/ass.h>


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
        ASS_Library *ass_library;
        ASS_Renderer *ass_renderer;
        ASS_Track *ass_track;


        ass_library = ass_library_init();
        if (!ass_library)
                return 0;

        ass_renderer = ass_renderer_init(ass_library);
        if(!ass_renderer)
                goto end;

        ass_track = ass_read_memory(ass_library, (char*)data, size, NULL);
        if(ass_track){
                ass_alloc_style(ass_track);
                ass_alloc_event(ass_track);
                ass_free_track(ass_track);
        }

        ass_renderer_done(ass_renderer);

end:
        ass_library_done(ass_library);

        return 0;
}
