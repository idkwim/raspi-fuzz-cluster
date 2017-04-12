/**
 * This is a dummy test to check that libfuzzer works.
 *
 * Compile with:
 * $ ./make.sh test_fuzzer.cc
 */

#include <stdint.h>
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        return \
                size >= 3 &&
                data[0] == 'F' &&
                data[1] == 'U' &&
                data[2] == 'Z' &&
                data[3] == 'Z';
}
