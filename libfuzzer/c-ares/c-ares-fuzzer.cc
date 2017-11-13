/**
 * C-Ares fuzzer
 *
 * Compile library with ASAN:
 * $ curl -fSsL https://c-ares.haxx.se/download/c-ares-1.13.0.tar.gz  | tar xfz -
 * $ ./configure CC="clang-4.0 -O2 -fno-omit-frame-pointer -g -fsanitize=address -fsanitize-coverage=trace-pc-guard,trace-cmp,trace-gep,trace-div"
 *
 * Compile fuzzer with:
 * $ ./make.sh c-ares-fuzzer.cc -lcares
 *
 * Run fuzzer with:
 * $ ./c-ares-fuzzer -workers=4 -jobs=4 -timeout=3000 -rss_limit_mb=256
 */


#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <arpa/nameser.h>
#include <ares.h>

extern "C" int LLVMFuzzerTestOneInput(const char *Data, size_t Size)
{
        unsigned char *buf;
        int buflen;
        std::string s(reinterpret_cast<const char *>(Data), Size);
        ares_create_query(s.c_str(), ns_c_in, ns_t_a, 0x1234, 0, &buf, &buflen, 0);
        ares_free_string(buf);
        return 0;
}
