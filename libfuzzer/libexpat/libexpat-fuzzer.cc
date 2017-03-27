/**
 * libexpat fuzzer
 * compile with
 * $ ./make.sh libexpat-fuzzer.cc -lexpat
 */
#include <stdio.h>
#include <expat.h> 
 
static void XMLCALL start(void *data, const char *el, const char **attr)
{
	return;
}
 
static void XMLCALL end(void *data, const char *el)
{
  	return;
}
 
extern "C" int LLVMFuzzerTestOneInput(const unsigned char *data, unsigned long size)
{
        int error, done;
	XML_Parser p = XML_ParserCreate(NULL);
        if(!p) return 0;
	XML_SetElementHandler(p, start, end);
	done = 1;
	XML_Parse(p, (const char*)data, size, done);
	XML_ParserFree(p);
        return 0;
}
