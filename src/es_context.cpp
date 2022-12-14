#include "es_context.h"
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <locale>
using namespace foxintango;
static std::map<foxintango::es_context*,std::map<std::string, foxintango::es_document*>*> context_document_map;

es_context::es_context(){
    if(!context_document_map.count(this)){
        context_document_map.insert(std::pair<es_context*, std::map<std::string, es_document*>*>(this,new std::map<std::string, es_document*>()));
    }
}

es_context::~es_context(){
    if(context_document_map.count(this)){
        delete context_document_map.at(this);
        context_document_map.erase(this);
    }
}

es_document* es_context::document_at(char* path){
    if(context_document_map.count(this)){
        std::map<std::string, es_document*>& document_map = *(context_document_map.at(this));

        if(document_map.count(path)) return document_map.at(path);
    }

    return nullptr;
}