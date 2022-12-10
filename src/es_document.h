#ifndef _es_document_h_
#define _es_document_h_
#include "es_element.h"
class es_document{
public:
    es_document();
   ~es_document();
public:
    int load(char* path);
public:
    es_element* build();
};
#endif
