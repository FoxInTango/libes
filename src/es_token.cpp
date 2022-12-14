#include "es_token.h"
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
#define DEBUG

std::map<std::wstring,es_token> ES_token_map = {
    { es_token_operator_assign,{ es_token_assign,es_token_operator_assign,0,0}}
};

typedef std::vector<es_token> ES_token_array;
std::map<es_token_array*, ES_token_array*> ES_token_array_map;

es_token_array::es_token_array(){
    ES_token_array_map.insert(std::pair<es_token_array*, ES_token_array*>(this, new ES_token_array()));
}

es_token_array::~es_token_array(){
    if(ES_token_array_map.count(this)){
        delete ES_token_array_map.at(this);
        ES_token_array_map.erase(this);
    }
}

const es_token& es_token_array::at(const unsigned int& index){
    return ES_token_array_map.count(this) ? ES_token_array_map.at(this)->at(index) : es_token();
}

unsigned int es_token_array::count() {
    return ES_token_array_map.count(this) ? ES_token_array_map.at(this)->size() : 0;
}
unsigned int es_token_array::count(const wchar_t* text){
    unsigned int count = 0;

    if(ES_token_array_map.count(this)) {
        for(ES_token_array::iterator iter = ES_token_array_map.at(this)->begin(); iter != ES_token_array_map.at(this)->end();iter++){
            if (0 == wcsncmp(text, (*iter).value, wcslen((*iter).value))) {
                count ++;
            }
        }
    }

    return count;
}
unsigned int es_token_array::count(const es_token_type& type){
    unsigned int count = 0;

    if (ES_token_array_map.count(this)) {
        for (ES_token_array::iterator iter = ES_token_array_map.at(this)->begin(); iter != ES_token_array_map.at(this)->end(); iter++) {
            if ((*iter).type == type) {
                count++;
            }
        }
    }
    return count;
}

unsigned int es_token_array::append(const es_token& token){
    if(ES_token_array_map.count(this)){
        ES_token_array_map.at(this)->push_back(token);
    }
}

unsigned int es_token_array::append(es_token_array& array){
    if (ES_token_array_map.count(this)) {
        ES_token_array* v = ES_token_array_map.at(&array);
        ES_token_array_map.at(this)->insert(ES_token_array_map.at(this)->begin(),v->begin(),v->end());
    }
}

unsigned int es_token_array::remove(const unsigned int& index){
    if (ES_token_array_map.count(this)) {
        ES_token_array_map.at(this)->erase(ES_token_array_map.at(this)->begin()+ index);
    }
}

unsigned int es_token_array::insert(const es_token& token, const unsigned int& index){
    if (ES_token_array_map.count(this)) {
        ES_token_array_map.at(this)->insert(ES_token_array_map.at(this)->begin() + index,token);
    }
}

const es_token& es_token_array::operator [] (const unsigned int& index){
    return at(index);
}

void es_token_init() {
    int index = 0;
}

int es_token_what_is(const wchar_t* const wline, const bool& asked, es_token& token, const es_token_array& array) {
    /** constructor */
    if (0 == wcsncmp(wline, es_token_keyword_consfun, wcslen(es_token_keyword_consfun))) {
        es_token token;
        token.type = es_token_consfun;
        token.value = new wchar_t[wcslen(es_token_keyword_consfun) + 1];
        token.value[wcslen(es_token_keyword_consfun)] = 0;
        wcscpy(token.value, es_token_keyword_consfun);
    }
    /** const */
    else if (0 == wcsncmp(wline, es_token_keyword_const, wcslen(es_token_keyword_const))) {
        token.type = es_token_const;
        token.value = new wchar_t[wcslen(es_token_keyword_const) + 1];
        token.value[wcslen(es_token_keyword_const)] = 0;
        wcscpy(token.value, es_token_keyword_const);
    }
    /** let */
    else if (0 == wcsncmp(wline, es_token_keyword_let, wcslen(es_token_keyword_let))) {
        token.type = es_token_let;
        token.value = new wchar_t[wcslen(es_token_keyword_let) + 1];
        token.value[wcslen(es_token_keyword_let)] = 0;
        wcscpy(token.value, es_token_keyword_let);
    }
    /** var */ //***************
    else if (0 == wcsncmp(wline, es_token_keyword_var, wcslen(es_token_keyword_var))) {
            token.type = es_token_var;
            token.value = new wchar_t[wcslen(es_token_keyword_var) + 1];
            token.value[wcslen(es_token_keyword_var)] = 0;
            wcscpy(token.value, es_token_keyword_var);
    }
    /** function */
    else if (0 == wcsncmp(wline, es_token_keyword_function, wcslen(es_token_keyword_function))) {
        token.type = es_token_function;
        token.value = new wchar_t[wcslen(es_token_keyword_function) + 1];
        token.value[wcslen(es_token_keyword_function)] = 0;
        wcscpy(token.value, es_token_keyword_function);
    }
    /** class */
    else if (0 == wcsncmp(wline, es_token_keyword_class, wcslen(es_token_keyword_class))) {
        token.type = es_token_class;
        token.value = new wchar_t[wcslen(es_token_keyword_class) + 1];
        token.value[wcslen(es_token_keyword_class)] = 0;
        wcscpy(token.value, es_token_keyword_class);
    }
    /** export */
    else if (0 == wcsncmp(wline, es_token_keyword_export, wcslen(es_token_keyword_export))) {
        token.type = es_token_export;
        token.value = new wchar_t[wcslen(es_token_keyword_export) + 1];
        token.value[wcslen(es_token_keyword_export)] = 0;
        wcscpy(token.value, es_token_keyword_export);
    }
    /** import */
    else if (0 == wcsncmp(wline, es_token_keyword_import, wcslen(es_token_keyword_import))) {
        token.type = es_token_import;
        token.value = new wchar_t[wcslen(es_token_keyword_import) + 1];
        token.value[wcslen(es_token_keyword_import)] = 0;
        wcscpy(token.value, es_token_keyword_import);
    }
    /** throw */
    else if (0 == wcsncmp(wline, es_token_keyword_throw, wcslen(es_token_keyword_throw))) {
        token.type = es_token_throw;
        token.value = new wchar_t[wcslen(es_token_keyword_throw) + 1];
        token.value[wcslen(es_token_keyword_throw)] = 0;
        wcscpy(token.value, es_token_keyword_throw);
    }
    /** new */
    else if (0 == wcsncmp(wline, es_token_keyword_new, wcslen(es_token_keyword_new))) {
        token.type = es_token_new;
        token.value = new wchar_t[wcslen(es_token_keyword_new) + 1];
        token.value[wcslen(es_token_keyword_new)] = 0;
        wcscpy(token.value, es_token_keyword_new);
    }
    /** unsure */
    else {
        token.type = es_token_unsure;
        token.value = new wchar_t[wcslen(wline) + 1];
        memset(token.value, 0, sizeof(wchar_t) * (wcslen(wline) + 1));
        memcpy(token.value, wline, sizeof(wchar_t) * wcslen(wline));
    }

    return 0;
}