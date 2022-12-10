/*
 * libes
 *
 * Copyright (C) 2022 FoxInTango <foxintango@yeah.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "es_document.h"
#include "es_token.h"
#include <vector>
#include <map>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <locale>

#define ES_file_line_length_max 2048

typedef std::vector<es_token> es_token_array;

static std::map<es_document*,es_token_array*> document_token_array_map;

unsigned int u16len(char16_t* u) {
    if(!u) return -1;

    unsigned int len = 0;

    while(u[len] != 0){
        len ++;
    }

    return len;
}

int u16cpy(char16_t* d,char16_t* s,unsigned int l) {
    if(!d || !s || !l) return 0;

    for(unsigned int i = 0;i < l; i ++) {
        d[i] = s[i];
    }
}

es_document::es_document() {
    if(!document_token_array_map.count(this)) {
        es_token_array* array = new es_token_array();
        document_token_array_map.insert(std::pair<es_document*,es_token_array*>(this,array));
    }
}

es_document::~es_document() {
    if(document_token_array_map.count(this)) {
        delete document_token_array_map.at(this);
        document_token_array_map.erase(this);
    }
}

int es_document::load(char* path) {
    std::ifstream stream(path);
    if(!stream) return -1;
    std::cout << "document : " << path << " loaded." << std::endl;
    es_token_array& tokens = (*document_token_array_map.at(this));

    /**
     * https://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16
     * char  utf8[ES_file_line_length_max];
     * short utf16[ES_file_line_length_max];
     * stream.getline(utf8,ES_file_line_length_max);
     */
    unsigned int line_index = 0;
    bool meet_syntax_error  = false;
    
    for(std::string line; std::getline(stream,line);) {
        if(meet_syntax_error) break;
        // std::string line; std::getline(stream,line);
        unsigned int index = 0;
        //std::wstring wline = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.from_bytes(line);
        std::wstring wline = std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(line);
        //std::wcout << "Line " << line_index << "  Content : " << wline << std::endl;
        bool in_quote   = false;
        int  quote_type = 0;
        while(index < line.length()){
            // std::cout << "deal with - line : " << line_index << " char " << index << "    " << line[index] << std::endl;
            switch(line[index]) {
                case es_token_mark_bracket_l:{
                    es_token token;
                    token.type = es_token_bracket_l;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_bracket_l;
                    tokens.push_back(token);
                }break;
                case es_token_mark_bracket_r:{
                    es_token token;
                    token.type = es_token_bracket_r;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_bracket_r;
                    tokens.push_back(token);
                }break;
                case es_token_mark_angle_l:{
                    es_token token;
                    token.type = es_token_angle_l;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_angle_l;
                    tokens.push_back(token);
                }break;
                case es_token_mark_angle_r:{
                    es_token token;
                    token.type = es_token_angle_r;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_angle_r;
                    tokens.push_back(token);
                }break;
                case es_token_mark_square_l:{
                    es_token token;
                    token.type = es_token_square_l;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_square_l;
                    tokens.push_back(token);
                }break;
                case es_token_mark_square_r:{
                    es_token token;
                    token.type = es_token_square_r;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_square_r;
                    tokens.push_back(token);
                }break;
                case es_token_mark_brace_l:{
                    es_token token;
                    token.type = es_token_brace_l;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_brace_l;
                    tokens.push_back(token);
                }break;
                case es_token_mark_brace_r:{
                    es_token token;
                    token.type = es_token_brace_r;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_brace_r;
                    tokens.push_back(token);
                }break;
                case es_token_mark_dot:{
                    es_token token;
                    token.type = es_token_dot;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_dot;
                    tokens.push_back(token);
                }break;
                case es_token_mark_space:{
                    es_token token;
                    token.type = es_token_space;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_space;
                    tokens.push_back(token);
                }break;
                case es_token_mark_quote_s:{
                    /** 提取字符串 */
                    std::wstring string;
                    index += 1;
                    while(wline[index] != es_token_mark_quote_s && index < line.length()){
                        string.push_back(wline[index]);
                        index ++;
                    }
                    if(wline[index] != es_token_mark_quote_s) {
                        std::cout << "Syntax Error >> " << "File : " << path << " Line : " << line_index << " | unclosed string" << std::endl;
                        meet_syntax_error = true;
                        continue;
                    }
                    es_token token;
                    token.type = es_token_quote_s;
                    token.value = new wchar_t[string.length() + 1];
                    memset(token.value,0,string.length() + 1);
                    memcpy(token.value,string.c_str(),sizeof(wchar_t) * string.length());
                    token.value[0] = es_token_mark_quote_s;
                    tokens.push_back(token);
                    std::cout << "deal with string : "  << std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(string) << std::endl;
                }break;
                case es_token_mark_quote_d:{
                    /** 提取字符串 */
                    std::u16string string;
                    index += 1;
                    while(wline[index] != es_token_mark_quote_d && index < line.length()){
                        string.push_back(line[index]);
                        index ++;
                    }
                    if(wline[index] != es_token_mark_quote_d) {
                        std::cout << "Syntax Error >> " << "File : " << path << " Line : " << line_index << " | unclosed string" << std::endl;
                        meet_syntax_error = true;
                        continue;
                    }
                    es_token token;
                    token.type = es_token_quote_d;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_quote_d;
                    tokens.push_back(token);
                    std::cout << "deal with string : "  << std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(string) << std::endl;
                }break;
                case es_token_mark_colon:{
                    es_token token;
                    token.type = es_token_colon;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_colon;
                    tokens.push_back(token);
                }break;
                case es_token_mark_semi:{
                    es_token token;
                    token.type = es_token_semi;
                    token.value = new wchar_t[2];
                    memset(token.value,0,2);
                    token.value[0] = es_token_mark_semi;
                    tokens.push_back(token);
                }break;
                /**
                 * deal with keywords 
                 */
                default:{
                    /** const */
                    if(0 == wcsncmp(&wline[index],es_token_keyword_const,wcslen(es_token_keyword_const))){
                        if(wline[index + wcslen(es_token_keyword_const)] == L' ' && index + wcslen(es_token_keyword_const) <= wline.length()) {
                            es_token token;
                            token.type = es_token_const;
                            token.value = new wchar_t[wcslen(es_token_keyword_const) + 1];
                            token.value[wcslen(es_token_keyword_const)] = 0;
                            wcscpy(token.value,es_token_keyword_const);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_const);
                        }
                        
                    }
                    /** let */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_let,wcslen(es_token_keyword_let))){
                        if(wline[index + wcslen(es_token_keyword_let)] == L' ' && index + wcslen(es_token_keyword_let) <= wline.length()) {
                            es_token token;
                            token.type = es_token_let;
                            token.value = new wchar_t[wcslen(es_token_keyword_let) + 1];
                            token.value[wcslen(es_token_keyword_let)] = 0;
                            wcscpy(token.value,es_token_keyword_let);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_let);
                        }
                    }
                    /** var */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_var,wcslen(es_token_keyword_var))){
                        if(wline[index + wcslen(es_token_keyword_var)] == L' ' && index + wcslen(es_token_keyword_var) <= wline.length()) {
                            es_token token;
                            token.type = es_token_var;
                            token.value = new wchar_t[wcslen(es_token_keyword_var) + 1];
                            token.value[wcslen(es_token_keyword_var)] = 0;
                            wcscpy(token.value,es_token_keyword_var);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_var);
                        }
                    }
                    /** function */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_function,wcslen(es_token_keyword_function))){
                        if(wline[index + wcslen(es_token_keyword_function)] == L' ' && index + wcslen(es_token_keyword_function) <= wline.length()) {
                            es_token token;
                            token.type = es_token_function;
                            token.value = new wchar_t[wcslen(es_token_keyword_function) + 1];
                            token.value[wcslen(es_token_keyword_function)] = 0;
                            wcscpy(token.value,es_token_keyword_function);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_function);
                        }
                    }
                    /** class */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_class,wcslen(es_token_keyword_class))){
                        if(wline[index + wcslen(es_token_keyword_class)] == L' ' && index + wcslen(es_token_keyword_class) <= wline.length()) {
                            es_token token;
                            token.type = es_token_class;
                            token.value = new wchar_t[wcslen(es_token_keyword_class) + 1];
                            token.value[wcslen(es_token_keyword_class)] = 0;
                            wcscpy(token.value,es_token_keyword_class);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_class);
                        }
                    }
                    /** export */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_export,wcslen(es_token_keyword_export))){
                        if(wline[index + wcslen(es_token_keyword_export)] == L' ' && index + wcslen(es_token_keyword_export) <= wline.length()) {
                            es_token token;
                            token.type = es_token_export;
                            token.value = new wchar_t[wcslen(es_token_keyword_export) + 1];
                            token.value[wcslen(es_token_keyword_export)] = 0;
                            wcscpy(token.value,es_token_keyword_export);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_export);
                        }
                    }
                    /** import */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_import,wcslen(es_token_keyword_import))){
                        if(wline[index + wcslen(es_token_keyword_import)] == L' ' && index + wcslen(es_token_keyword_import) <= wline.length()) {
                            es_token token;
                            token.type = es_token_import;
                            token.value = new wchar_t[wcslen(es_token_keyword_import) + 1];
                            token.value[wcslen(es_token_keyword_import)] = 0;
                            wcscpy(token.value,es_token_keyword_import);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_import);
                        }
                    }
                    /** throw */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_throw,wcslen(es_token_keyword_throw))){
                        if(wline[index + wcslen(es_token_keyword_throw)] == L' ' && index + wcslen(es_token_keyword_throw) <= wline.length()) {
                            es_token token;
                            token.type = es_token_throw;
                            token.value = new wchar_t[wcslen(es_token_keyword_throw) + 1];
                            token.value[wcslen(es_token_keyword_throw)] = 0;
                            wcscpy(token.value,es_token_keyword_throw);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_throw);
                        }
                    }
                    /** new */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_new,wcslen(es_token_keyword_new))){
                        if(wline[index + wcslen(es_token_keyword_new)] == L' ' && index + wcslen(es_token_keyword_new) <= wline.length()) {
                            es_token token;
                            token.type = es_token_new;
                            token.value = new wchar_t[wcslen(es_token_keyword_new) + 1];
                            token.value[wcslen(es_token_keyword_new)] = 0;
                            wcscpy(token.value,es_token_keyword_new);
                            tokens.push_back(token);
                            std::wcout << " ** deal with keyword : " << token.value << "  line index: " << line_index << "  char index: " << index << std::endl;
                            index += wcslen(es_token_keyword_new);
                        }
                    }
                    /** unsure */
                    else {
                        
                    }
                }break;
            }
            index++;
        }
        line_index ++;
    }
    return 0;
}
