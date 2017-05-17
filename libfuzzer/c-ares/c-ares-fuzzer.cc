/**
 * C-Ares fuzzer
 *
 * Compile with:
 * $ ./make.sh c-ares-fuzzer.cc -lares
 */


#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <arpa/nameser.h>

#include <ares.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
        unsigned char *buf;
        int buflen;
        std::string s(reinterpret_cast<const char *>(Data), Size);
        ares_create_query(s.c_str(), ns_c_in, ns_t_a, 0x1234, 0, &buf, &buflen, 0);
        free(buf);
        return 0;
}
