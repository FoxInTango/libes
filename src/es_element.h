#ifndef _es_element_h_
#define _es_element_h_
#include "es_prototype.h"
/**
 * 
 */
class es_context;
class es_document;
class es_element_implement;
class es_element{
protected:
    es_element_implement* implement;
public:
    es_element();
    ~es_element();
public:
public:
    unsigned int appendSubelement(es_element* element);
    unsigned int removeSubelement(es_element* element);
    unsigned int removeSubelement(const unsigned int& index);

    int attachContext();

    int load(const es_document* document,const unsigned int& index);
public:
    int run();
};

#endif
