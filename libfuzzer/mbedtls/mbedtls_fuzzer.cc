/**
 * This is a dummy test to check that libfuzzer works.
 *
 * Compile with:
 * $ ./make.sh test_fuzzer.cc -lmbed
 */

#include <stdint.h>
#include <stddef.h>

#include <mbedtls/ssl.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/certs.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
        mbedtls_x509_crt crt;
        mbedtls_x509_crl crl;

        int retcode;

        // retcode = mbedtls_x509_crt_parse(&crt, data, size);

        mbedtls_x509_crl_init(&crl);
        retcode = mbedtls_x509_crl_parse_der(&crl, data, size);
        mbedtls_x509_crl_free(&crl);

        return 0;
}
