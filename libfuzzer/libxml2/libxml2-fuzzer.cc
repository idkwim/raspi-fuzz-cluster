/**
 * libxml2 fuzzer
 *
 * Compile with:
 * $ ./make.sh libxml2-fuzzer.cc -I/usr/include/libxml2 -lxml2
 */

#include <string>
#include <vector>

#include <libxml/xmlversion.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>
#include <libxml/tree.h>

void ignore (void * ctx, const char * msg, ...) {}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        xmlSetGenericErrorFunc(NULL, &ignore);
        if (auto doc = xmlReadMemory(reinterpret_cast<const char *>(data),
                                     size,
                                     "noname.xml",
                                     NULL,
                                     0)){
                xmlFreeDoc(doc);
        }
        return 0;
}
