/**
 * This is a dummy test to check that libfuzzer works.
 *
 * Compile with:
 * $ ./make.sh test_fuzzer.cc
 */

#include <stdint.h>
#include <stddef.h>

/**
 * For custom mutators, check out
 * https://github.com/llvm-mirror/llvm/blob/master/lib/Fuzzer/FuzzerInterface.h
 */

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
        return \
                size >= 3 &&
                data[0] == 'F' &&
                data[1] == 'U' &&
                data[2] == 'Z' &&
                data[3] == 'Z';
}
