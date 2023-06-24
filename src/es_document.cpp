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
#include <set>
#include <fstream>
#include <codecvt>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include <locale>
using namespace foxintango;

#define DEBUG
#define ES_file_line_length_max 2048

static std::map<es_document*, es_token_array*> document_token_array_map;
using namespace foxintango;
es_document::es_document() {
    if(!document_token_array_map.count(this)) {
        document_token_array_map.insert(std::pair<es_document*, es_token_array*>(this, new es_token_array()));
    }
}

es_document::~es_document() {
    if(document_token_array_map.count(this)) {
        delete document_token_array_map.at(this);
        document_token_array_map.erase(this);
    }
}

/*
Error es_document::load(const char* path) {
    std::ifstream stream(path);
    if(!stream || !document_token_array_map.at(this)) return -1;
#ifdef DEBUG
    std::cout << "document : " << path << " loaded." << std::endl;
#endif // DEBUG

    std::wstring documentURL = std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(path);
    
     * https://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16
     * char  utf8[ES_file_line_length_max];
     * short utf16[ES_file_line_length_max];
     * stream.getline(utf8,ES_file_line_length_max);
     
    unsigned int line_index = 0;
    unsigned int char_index = 0;
    bool meet_syntax_error  = false;
    编码测试 
    //std::ofstream ostream("./libes/test/unicode.txt");
    for(std::string line; std::getline(stream,line);) {
        if(meet_syntax_error) break;
        // std::string line; std::getline(stream,line);
        char_index = 0;
        std::wstring wline = std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(line);
        编码测试
        //ostream.write(std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(wline).c_str(), std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(wline).length() * sizeof(wchar_t));
        /** 行尾测试
        
        es_token_array tokens;
        while(char_index < wline.length() && !(wline[char_index] == L'\n' || wline[char_index] == L'\t' || wline[char_index] == L'\r')){
            // std::cout << "deal with - line : " << line_index << " char " << index << "    " << line[index] << std::endl;
            es_token token;
            token.documentURL = new wchar_t[documentURL.length()];
            wmemset(token.documentURL, 0, documentURL.length());
            wmemcpy(token.documentURL, documentURL.c_str(), documentURL.length());
            token.lineIndex = line_index;
            token.charIndex = char_index;
            std::wstring unsure;
            while (char_index < wline.length() && wline[char_index] != L'\n' && wline[char_index] != L'\t' && wline[char_index] != L'\r') {
                unsure += wline[char_index];
                int step = 0;
                bool asked = false;
                while(step = es_token_what_is(unsure.c_str(), asked,token, tokens) != 0){
                    if (step > 0) {
                        for (int i = 0; i < step; i++) {
                            unsure += wline[char_index + i + 1];
                        }
                    } else {
                        asked = true;
                    }
                }
                tokens.append(token);
                char_index += (step + 1);
            }
        }
        es_token_array& document_tokens = *(document_token_array_map.at(this));
        document_tokens.append(tokens);
        line_index ++;
    }
    编码测试
    // ostream.close();
#ifdef DEBUG
    std::cout << "tokens : " << std::endl;
    es_token_array& document_tokens = *(document_token_array_map.at(this));
    for(int i = 0; i < document_tokens.count();i ++){
        std::cout << " token: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(document_tokens[i].value) << "  LINE INDEX : "<< (int)(document_tokens[i].lineIndex) << "  CHAR INDEX : " << (int)(document_tokens[i].charIndex) << std::endl;
#endif
    }

    return 0;
}
*/

Error es_document::load(const char* path){
    String token;
    String content;
    Index  index = 0;

    while(index < content.length()){
        load_token(token,content,index);
        if(token == es_token_keyword_break){
            ASTBreak* e = new ASTBreak();
        }
    }

    return 0;
}
Error es_document::load_token(String& token, String& content, Index& index){
    return 0;
}

ASTScope* es_document::load_scope(){ return 0; }
ASTClass* es_document::load_class() { return 0; }
ASTFunction* es_document::load_function() { return 0; }
ASTExpression* es_document::load_expression() { return 0; }
