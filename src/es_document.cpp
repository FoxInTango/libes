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

#define DEBUG
#define ES_file_line_length_max 2048

typedef std::vector<es_token> ES_token_array;

static std::map<es_document*, ES_token_array*> document_token_array_map;

void handle_text();
void handle_number();
void handle_comment();

es_document::es_document() {
    if(!document_token_array_map.count(this)) {
        ES_token_array* array = new ES_token_array();
        document_token_array_map.insert(std::pair<es_document*, ES_token_array*>(this,array));
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
#ifdef DEBUG
    std::cout << "document : " << path << " loaded." << std::endl;
#endif // DEBUG

    
    ES_token_array& tokens = (*document_token_array_map.at(this));
    /**
     * https://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16
     * char  utf8[ES_file_line_length_max];
     * short utf16[ES_file_line_length_max];
     * stream.getline(utf8,ES_file_line_length_max);
     */
    unsigned int line_index = 0;
    bool meet_syntax_error  = false;
    /** 编码测试 */
    //std::ofstream ostream("./libes/test/unicode.txt");
    for(std::string line; std::getline(stream,line);) {
        if(meet_syntax_error) break;
        // std::string line; std::getline(stream,line);
        unsigned int index = 0;
        std::wstring wline = std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(line);
        /** 编码测试 */
        //ostream.write(std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(wline).c_str(), std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(wline).length() * sizeof(wchar_t));
        /** 行尾测试
         */
        while(index < wline.length() && !(wline[index] == L'\n' || wline[index] == L'\t' || wline[index] == L'\r')){
            // std::cout << "deal with - line : " << line_index << " char " << index << "    " << line[index] << std::endl;
            switch(wline[index]) {
                /** ( */
                case es_token_mark_bracket_l:{
                    es_token token;
                    token.type = es_token_bracket_l;
                    token.value = new wchar_t[2];
                    memset(token.value,0,sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_bracket_l;
                    tokens.push_back(token);
                    index++;
                }break;
                /** ) */
                case es_token_mark_bracket_r:{
                    es_token token;
                    token.type = es_token_bracket_r;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_bracket_r;
                    tokens.push_back(token);
                    index++;
                }break;
                /** < */
                case es_token_mark_angle_l:{
                    es_token token;
                    /**
                     * <=
                     * <<
                     */
                    if(index + 1 < wline.length()) {
                        switch(wline[index + 1]){
                            case es_token_mark_angle_l:{
                                token.type = es_token_shift_l;
                                token.value = new wchar_t[3];
                                memset(token.value, 0, sizeof(wchar_t) * 3);
                                token.value[0] = es_token_operator_shift_l[0];
                                token.value[1] = es_token_operator_shift_l[1];
                                tokens.push_back(token);
                                index += 2;
                            }break;
                            case es_token_mark_dhbar:{
                                token.type = es_token_cle;
                                token.value = new wchar_t[3];
                                memset(token.value, 0, sizeof(wchar_t) * 3);
                                token.value[0] = es_token_operator_cle[0];
                                token.value[1] = es_token_operator_cle[1];
                                tokens.push_back(token);
                                index += 2;
                            }break;
                            default: {
                                token.type = es_token_cl;
                                token.value = new wchar_t[2];
                                memset(token.value, 0, sizeof(wchar_t) * 2);
                                token.value[0] = es_token_mark_angle_l;
                                tokens.push_back(token);
                                index++;
                            }break;
                        }
                    } else {
                        token.type = es_token_cl;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_mark_angle_l;
                        tokens.push_back(token);
                        index++;
                    }
                }break;
                /** > */
                case es_token_mark_angle_r:{
                    es_token token;
                    /**
                      * >=
                      * >>
                      */
                    if (index + 1 < wline.length()) {
                        switch (wline[index + 1]) {
                        case es_token_mark_angle_r: {
                            token.type = es_token_shift_r;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_shift_r[0];
                            token.value[1] = es_token_operator_shift_r[1];
                            tokens.push_back(token);
                            index += 2;
                        }break;
                        case es_token_mark_dhbar: {
                            token.type = es_token_cge;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_cge[0];
                            token.value[1] = es_token_operator_cge[1];
                            tokens.push_back(token);
                            index += 2;
                        }break;
                        default: {
                            token.type = es_token_cg;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_cg;
                            tokens.push_back(token);
                            index++;
                        }break;
                        }
                    }
                    else {
                        token.type = es_token_cg;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_cg;
                        tokens.push_back(token);
                        index++;
                    }
                }break;
                /** [ */
                case es_token_mark_square_l:{
                    es_token token;
                    token.type = es_token_square_l;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_square_l;
                    tokens.push_back(token);
                    index++;
                }break;
                /** ] */
                case es_token_mark_square_r:{
                    es_token token;
                    token.type = es_token_square_r;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_square_r;
                    tokens.push_back(token);
                    index++;
                }break;
                /** { */
                case es_token_mark_brace_l:{
                    es_token token;
                    token.type = es_token_brace_l;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t)* 2);
                    token.value[0] = es_token_mark_brace_l;
                    tokens.push_back(token);
                    index++;
                }break;
                /** } */
                case es_token_mark_brace_r:{
                    es_token token;
                    token.type = es_token_brace_r;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_brace_r;
                    tokens.push_back(token);
                    index++;
                }break;
                /** . */
                case es_token_mark_dot:{
                    es_token token;
                    token.type = es_token_dot;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_dot;
                    tokens.push_back(token);
                    index++;
                }break;
                /**  */
                case es_token_mark_space:{
                    /** pass */
                    /*
                    while(wline[index] == es_token_mark_space){
                        index ++;
                    }*/
                    index++;
                }break;
                /** ' */
                case es_token_mark_quote_s:{
                    /** 提取字符串 */
                    std::wstring string;
                    index += 1;
                    while(wline[index] != es_token_mark_quote_s && index < line.length()){
                        string += wline[index];
                        index ++;
                    }
                    if(wline[index] != es_token_mark_quote_s) {
#ifdef DEBUG
                        std::cout << "Syntax Error | Unclosed String : { " << "File : " << path/*std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(path)*/ << " Line : " << line_index << " }" << std::endl;
#endif // DEBUG          
                        meet_syntax_error = true;
                        continue;
                    } else { /** 字符串作为 token*/
                        es_token token;
                        token.type = es_token_quote_s;
                        token.value = new wchar_t[string.length() + 1];
                        memset(token.value, 0, (sizeof(wchar_t)* string.length() + 1));
                        memcpy(token.value, string.c_str(), sizeof(wchar_t)* string.length());
                        tokens.push_back(token); 
                        index++;
                    }            
#ifdef DEBUG
                    std::cout << "deal with string : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(string) << std::endl;
#endif // DEBUG  
                }break;
                /** " */
                case es_token_mark_quote_d:{
                    /** 提取字符串 */
                    std::wstring string;
                    index += 1;
                    while(wline[index] != es_token_mark_quote_d && index < line.length()){
                        string += wline[index];
                        index ++;
                    }
                    if(wline[index] != es_token_mark_quote_d) {
#ifdef DEBUG
                        std::cout << "Syntax Error | Unclosed String : { " << "File : " << path/*std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.from_bytes(path)*/ << " Line : " << line_index << " }" << std::endl;
#endif
                        meet_syntax_error = true;
                        continue;
                    } else { /** 字符串作为 token，其后引号作为token*/
                        es_token token;
                        token.type = es_token_quote_d;
                        token.value = new wchar_t[string.length() + 1];
                        memset(token.value, 0, sizeof(wchar_t) * (string.length() + 1));
                        memcpy(token.value, string.c_str(), sizeof(wchar_t)* string.length());
                        tokens.push_back(token);
                        index++;
                    }
#ifdef DEBUG
                    std::cout << "deal with string : "  << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(string) << std::endl;
#endif
                }break;
                /** : */
                case es_token_mark_colon:{
                    es_token token;
                    token.type = es_token_colon;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_colon;
                    tokens.push_back(token);
                    index++;
                }break;
                /** ; */
                case es_token_mark_semi:{
                    es_token token;
                    token.type = es_token_semi;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_semi;
                    tokens.push_back(token);
                    index++;
                }break;
                    /** / */
                case es_token_mark_slash: {
                    es_token token;
                    /**
                     * // 
                     * /*
                     * /=
                     */
                    if (index + 1 < wline.length()) {
                        switch (wline[index + 1]) {
                            es_token token;
                        case es_token_mark_slash: {
                            token.type = es_token_comment_s;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_comment_short[0];
                            token.value[1] = es_token_comment_short[1];
                            tokens.push_back(token);
                            index+=2;
                        }break;
                        case es_token_mark_star: {
                            token.type = es_token_comment_l;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_comment_long_l[0];
                            token.value[1] = es_token_comment_long_l[1];
                            tokens.push_back(token);
                            index+=2;
                        }break;
                        default: {
                            token.type  = es_token_slash;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_mark_slash;
                            tokens.push_back(token);
                            index++;
                        }break;
                        }
                    }
                    else {
                        token.type = es_token_slash;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_mark_slash;
                        tokens.push_back(token);
                        index++;
                    }
                }break;
                /** \ */
                case es_token_mark_bslash: {
                    es_token token;
                    token.type = es_token_bslash;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_bslash;
                    tokens.push_back(token);
                    index++;
                }break;
                /** | */
                case es_token_mark_vbar: {
                    es_token token;
                    /**
                     * |=
                     * ||
                     */
                    if (index + 1 < wline.length()) {
                        switch (wline[index + 1]) {
                        case es_token_mark_dhbar: {
                            token.type = es_token_assign_bw_or;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_bw_or[0];
                            token.value[1] = es_token_operator_assign_bw_or[1];
                            tokens.push_back(token);
                            index+=2;
                        }break;
                        case es_token_mark_vbar: {
                            token.type = es_token_lg_or;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_lg_or[0];
                            token.value[1] = es_token_operator_lg_or[1];
                            tokens.push_back(token);
                            index+=2;
                        }break;
                        default: {
                            token.type = es_token_bw_or;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_bw_or;
                            tokens.push_back(token);
                            index++;
                        }break;
                        }
                    }
                    else {
                        token.type = es_token_bw_or;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_bw_or;
                        tokens.push_back(token);
                        index++;
                    }
                }break;
                /** ~ */
                case es_token_mark_wave: {
                    /**
                     * ~=
                     */
                    es_token token;
                    if (index + 1 < wline.length()) {
                        switch (wline[index + 1]) {
                        case es_token_mark_dhbar: {
                            token.type = es_token_assign_bw_not;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_bw_not[0];
                            token.value[1] = es_token_operator_assign_bw_not[1];
                            tokens.push_back(token);
                            index+=2;
                        }break;
                        default: {
                            token.type = es_token_bw_not;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_bw_not;
                            tokens.push_back(token);
                            index++;
                        }break;
                        }
                    }
                    else {
                        token.type = es_token_bw_not;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_bw_not;
                        tokens.push_back(token);
                        index++;
                    }
                }break;
                /** ! */
                case es_token_mark_woo: {
                    /**
                     * !=
                     * !==
                     */
                    if (index + 1 < wline.length()) {
                        switch (wline[index + 1])
                        {
                        case es_token_mark_dhbar:{
                            if(wline[index + 2] == es_token_mark_dhbar) {
                                es_token token;
                                token.type = es_token_nef;
                                token.value = new wchar_t[4];
                                memset(token.value, 0, sizeof(wchar_t) * 4);
                                token.value[0] = es_token_operator_nef[0];
                                token.value[1] = es_token_operator_nef[1];
                                token.value[2] = es_token_operator_nef[2];
                                tokens.push_back(token);
                                index +=3;
                            } else {
                                es_token token;
                                token.type = es_token_ne;
                                token.value = new wchar_t[3];
                                memset(token.value, 0, sizeof(wchar_t) * 3);
                                token.value[0] = es_token_operator_ne[0];
                                token.value[1] = es_token_operator_ne[1];
                                tokens.push_back(token);
                                index+=2;
                            }
                        }break;
                        default:{
                            es_token token;
                            token.type = es_token_lg_not;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_lg_not;
                            tokens.push_back(token);
                            index++;
                            }break;
                        }
                    } else {
                        es_token token;
                        token.type = es_token_operator_lg_not;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_lg_not;
                        tokens.push_back(token);
                        index++;
                    }
                }break;
                /** @ */
                case es_token_mark_at: {
                    es_token token;
                    token.type = es_token_at;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_at;
                    tokens.push_back(token);
                    index ++;
                }break;
                /** # */
                case es_token_mark_sharp: {
                    es_token token;
                    token.type = es_token_sharp;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_sharp;
                    tokens.push_back(token);
                    index++;
                }break;
                /** $ */
                case es_token_mark_usd: {
                    es_token token;
                    token.type = es_token_usd;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_mark_usd;
                    tokens.push_back(token);
                    index++;
                }break;
                /** % */
                case es_token_mark_percent: {
                    /**
                     * %=
                     */
                     if(index + 1 < wline.length()){
                         if(wline[index + 1] == es_token_mark_dhbar){
                             es_token token;
                             token.type = es_token_assign_mod;
                             token.value = new wchar_t[3];
                             memset(token.value, 0, sizeof(wchar_t) * 3);
                             token.value[0] = es_token_operator_assign_mod[0];
                             token.value[1] = es_token_operator_assign_mod[1];
                             tokens.push_back(token);
                             index ++ ;
                         } else {
                             es_token token;
                             token.type = es_token_mod;
                             token.value = new wchar_t[3];
                             memset(token.value, 0, sizeof(wchar_t) * 3);
                             token.value[0] = es_token_operator_mod;
                             tokens.push_back(token);
                         }
                     } else {
                         es_token token;
                         token.type = es_token_mod;
                         token.value = new wchar_t[3];
                         memset(token.value, 0, sizeof(wchar_t) * 3);
                         token.value[0] = es_token_operator_mod;
                         tokens.push_back(token);
                     }
                    index++;
                }break;
                /** ^ */
                case es_token_mark_arrow_up: {
                    /**
                     * ^=
                     */
                    if (index + 1 < wline.length()) {
                        if (wline[index + 1] == es_token_mark_dhbar) {
                            es_token token;
                            token.type = es_token_assign_exp;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_exp[0];
                            token.value[1] = es_token_operator_assign_exp[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else {
                            es_token token;
                            token.type = es_token_exp;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_exp;
                            tokens.push_back(token);
                        }
                    }
                    else {
                        es_token token;
                        token.type = es_token_exp;
                        token.value = new wchar_t[3];
                        memset(token.value, 0, sizeof(wchar_t) * 3);
                        token.value[0] = es_token_operator_exp;
                        tokens.push_back(token);
                    }
                    index++;
                }break;
                /** & */
                case es_token_mark_and: {
                    /**
                     * &=
                     * &&
                     */
                    if (index + 1 < wline.length()) {
                        if (wline[index + 1] == es_token_mark_dhbar) {
                            es_token token;
                            token.type = es_token_assign_bw_and;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_bw_and[0];
                            token.value[1] = es_token_operator_assign_bw_and[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else if(wline[index + 1] == es_token_mark_and){
                            es_token token;
                            token.type = es_token_lg_and;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_lg_and[0];
                            token.value[1] = es_token_operator_lg_and[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else {
                            es_token token;
                            token.type = es_token_and;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_bw_and;
                            tokens.push_back(token);
                        }
                    }
                    else {
                        es_token token;
                        token.type = es_token_and;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_bw_and;
                        tokens.push_back(token);
                    }
                    index++;
                }break;
                    /** ? */
                case es_token_mark_what: {
                    es_token token;
                    token.type = es_token_what;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_operator_what;
                    tokens.push_back(token);
                    index++;
                }break;
                    /** , */
                case es_token_mark_comma: {
                    es_token token;
                    token.type = es_token_comma;
                    token.value = new wchar_t[2];
                    memset(token.value, 0, sizeof(wchar_t) * 2);
                    token.value[0] = es_token_operator_comma;
                    tokens.push_back(token);
                    index++;
                }break;
                    /** + */
                case es_token_mark_cross: {
                    /**
                     * +=
                     * ++
                     */
                    if (index + 1 < wline.length()) {
                        if (wline[index + 1] == es_token_mark_dhbar) {
                            es_token token;
                            token.type = es_token_assign_add;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_add[0];
                            token.value[1] = es_token_operator_assign_add[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else if (wline[index + 1] == es_token_operator_add) {
                            es_token token;
                            token.type = es_token_assign_add_s;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_add_s[0];
                            token.value[1] = es_token_operator_assign_add_s[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else {
                            es_token token;
                            token.type = es_token_add;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_add;
                            tokens.push_back(token);
                        }
                    }
                    else {
                        es_token token;
                        token.type = es_token_add;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_add;
                        tokens.push_back(token);
                    }
                    index++;
                }break;
                    /** - */
                case es_token_mark_hyphen: {
                    /**
                     * -=
                     * --
                     */
                    if (index + 1 < wline.length()) {
                        if (wline[index + 1] == es_token_operator_assign) {
                            es_token token;
                            token.type = es_token_assign_sub;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_sub[0];
                            token.value[1] = es_token_operator_assign_sub[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else if (wline[index + 1] == es_token_operator_sub) {
                            es_token token;
                            token.type = es_token_assign_sub_s;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_sub_s[0];
                            token.value[1] = es_token_operator_assign_sub_s[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else {
                            es_token token;
                            token.type = es_token_sub;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_sub;
                            tokens.push_back(token);
                        }
                    }
                    else {
                        es_token token;
                        token.type = es_token_sub;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_sub;
                        tokens.push_back(token);
                    }
                    index++;
                }break;
                    /** * */
                case es_token_mark_star: {
                    /**
                     * *=
                     *
                     */
                    if (index + 1 < wline.length()) {
                        if (wline[index + 1] == es_token_operator_mul) {
                            es_token token;
                            token.type = es_token_assign_mul;
                            token.value = new wchar_t[3];
                            memset(token.value, 0, sizeof(wchar_t) * 3);
                            token.value[0] = es_token_operator_assign_mul[0];
                            token.value[1] = es_token_operator_assign_mul[1];
                            tokens.push_back(token);
                            index++;
                        }
                        else {
                            es_token token;
                            token.type = es_token_mul;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_mul;
                            tokens.push_back(token);
                        }
                    }
                    else {
                        es_token token;
                        token.type = es_token_mul;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_mul;
                        tokens.push_back(token);
                    }
                    index++;
                }break;
                    /** = */
                case es_token_mark_dhbar: {
                    /**
                     * ==
                     * ===
                     */
                    if (index + 1 < wline.length()) {
                        switch (wline[index + 1])
                        {
                        case es_token_mark_dhbar: {
                            if (wline[index + 2] == es_token_mark_dhbar) {
                                es_token token;
                                token.type = es_token_cef;
                                token.value = new wchar_t[4];
                                memset(token.value, 0, sizeof(wchar_t) * 4);
                                token.value[0] = es_token_operator_cef[0];
                                token.value[1] = es_token_operator_cef[1];
                                token.value[2] = es_token_operator_cef[2];
                                tokens.push_back(token);
                                index += 3;
                            }
                            else {
                                es_token token;
                                token.type = es_token_cef;
                                token.value = new wchar_t[3];
                                memset(token.value, 0, sizeof(wchar_t) * 3);
                                token.value[0] = es_token_operator_ce[0];
                                token.value[1] = es_token_operator_ce[1];
                                tokens.push_back(token);
                                index += 2;
                            }
                        }break;
                        default: {
                            es_token token;
                            token.type = es_token_assign;
                            token.value = new wchar_t[2];
                            memset(token.value, 0, sizeof(wchar_t) * 2);
                            token.value[0] = es_token_operator_assign;
                            tokens.push_back(token);
                            index++;
                        }break;
                        }
                    }
                    else {
                        es_token token;
                        token.type = es_token_assign;
                        token.value = new wchar_t[2];
                        memset(token.value, 0, sizeof(wchar_t) * 2);
                        token.value[0] = es_token_operator_assign;
                        tokens.push_back(token);
                        index++;
                    }
                    index ++;
                }break;
                case es_number_0: {
                    
                    index++;
                }break;
                case es_number_1: {

                    index++;
                }break;
                case es_number_2: {

                    index++;
                }break;
                case es_number_3: {

                    index++;
                }break;
                case es_number_4: {

                    index++;
                }break;
                case es_number_5: {

                    index++;
                }break;
                case es_number_6: {

                    index++;
                }break;
                case es_number_7: {

                    index++;
                }break;
                case es_number_8: {

                    index++;
                }break;
                case es_number_9: {

                    index++;
                }break;
                /**
                 * deal with keywords 
                 */
                default:{
                    /** constructor */
                    if (0 == wcsncmp(&wline[index], es_token_keyword_consfun, wcslen(es_token_keyword_consfun))) {
                        if (index + wcslen(es_token_keyword_consfun) < wline.length() && (wline[index + wcslen(es_token_keyword_consfun)] == L' ' || wline[index + wcslen(es_token_keyword_consfun)] == L'\n' || wline[index + wcslen(es_token_keyword_consfun)] == L'\t' || wline[index + wcslen(es_token_keyword_consfun)] == L'\r' || wline[index + wcslen(es_token_keyword_consfun)] == es_token_mark_bracket_l)) {
                            es_token token;
                            token.type = es_token_consfun;
                            token.value = new wchar_t[wcslen(es_token_keyword_consfun) + 1];
                            token.value[wcslen(es_token_keyword_consfun)] = 0;
                            wcscpy(token.value, es_token_keyword_consfun);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_consfun);
                        }

                    }
                    /** const */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_const,wcslen(es_token_keyword_const))){
                        if(index + wcslen(es_token_keyword_const) < wline.length() && (wline[index + wcslen(es_token_keyword_const)] == L' ' || wline[index + wcslen(es_token_keyword_const)] == L'\n' || wline[index + wcslen(es_token_keyword_const)] == L'\t' || wline[index + wcslen(es_token_keyword_const)] == L'\r')) {
                            es_token token;
                            token.type = es_token_const;
                            token.value = new wchar_t[wcslen(es_token_keyword_const) + 1];
                            token.value[wcslen(es_token_keyword_const)] = 0;
                            wcscpy(token.value,es_token_keyword_const);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_const);
                        }else {

                        
                        }
                        
                    }
                    /** let */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_let,wcslen(es_token_keyword_let))){
                        if(index + wcslen(es_token_keyword_let) < wline.length() && (wline[index + wcslen(es_token_keyword_let)] == L' ' || wline[index + wcslen(es_token_keyword_let)] == L'\n' || wline[index + wcslen(es_token_keyword_let)] == L'\t' || wline[index + wcslen(es_token_keyword_let)] == L'\r')) {
                            es_token token;
                            token.type = es_token_let;
                            token.value = new wchar_t[wcslen(es_token_keyword_let) + 1];
                            token.value[wcslen(es_token_keyword_let)] = 0;
                            wcscpy(token.value,es_token_keyword_let);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_let);
                        }
                    }
                    /** var */ //***************
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_var,wcslen(es_token_keyword_var))){
                        if(index + wcslen(es_token_keyword_var) < wline.length() && (wline[index + wcslen(es_token_keyword_var)] == L' ' || wline[index + wcslen(es_token_keyword_var)] == L'\n' || wline[index + wcslen(es_token_keyword_var)] == L'\t' || wline[index + wcslen(es_token_keyword_var)] == L'\r')) {
                            es_token token;
                            token.type = es_token_var;
                            token.value = new wchar_t[wcslen(es_token_keyword_var) + 1];
                            token.value[wcslen(es_token_keyword_var)] = 0;
                            wcscpy(token.value,es_token_keyword_var);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_var);
                        }
                    }
                    /** function */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_function,wcslen(es_token_keyword_function))){
                        if(index + wcslen(es_token_keyword_function) < wline.length() && (wline[index + wcslen(es_token_keyword_function)] == L' ' || wline[index + wcslen(es_token_keyword_function)] == L'\n' || wline[index + wcslen(es_token_keyword_function)] == L'\t' || wline[index + wcslen(es_token_keyword_function)] == L'\r')) {
                            es_token token;
                            token.type = es_token_function;
                            token.value = new wchar_t[wcslen(es_token_keyword_function) + 1];
                            token.value[wcslen(es_token_keyword_function)] = 0;
                            wcscpy(token.value,es_token_keyword_function);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_function);
                        }
                    }
                    /** class */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_class,wcslen(es_token_keyword_class))){
                        if(index + wcslen(es_token_keyword_class) < wline.length() && (wline[index + wcslen(es_token_keyword_class)] == L' ' || wline[index + wcslen(es_token_keyword_class)] == L'\n' || wline[index + wcslen(es_token_keyword_class)] == L'\t' || wline[index + wcslen(es_token_keyword_class)] == L'\r')) {
                            es_token token;
                            token.type = es_token_class;
                            token.value = new wchar_t[wcslen(es_token_keyword_class) + 1];
                            token.value[wcslen(es_token_keyword_class)] = 0;
                            wcscpy(token.value,es_token_keyword_class);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_class);
                        }
                    }
                    /** export */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_export,wcslen(es_token_keyword_export))){
                        if(index + wcslen(es_token_keyword_export) < wline.length() && (wline[index + wcslen(es_token_keyword_export)] == L' ' || wline[index + wcslen(es_token_keyword_export)] == L'\n' || wline[index + wcslen(es_token_keyword_export)] == L'\t' || wline[index + wcslen(es_token_keyword_export)] == L'\r')) {
                            es_token token;
                            token.type = es_token_export;
                            token.value = new wchar_t[wcslen(es_token_keyword_export) + 1];
                            token.value[wcslen(es_token_keyword_export)] = 0;
                            wcscpy(token.value,es_token_keyword_export);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_export);
                        }
                    }
                    /** import */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_import,wcslen(es_token_keyword_import))){
                        if(index + wcslen(es_token_keyword_import) < wline.length() && (wline[index + wcslen(es_token_keyword_import)] == L' ' || wline[index + wcslen(es_token_keyword_import)] == L'\n' || wline[index + wcslen(es_token_keyword_import)] == L'\t' || wline[index + wcslen(es_token_keyword_import)] == L'\r')) {
                            es_token token;
                            token.type = es_token_import;
                            token.value = new wchar_t[wcslen(es_token_keyword_import) + 1];
                            token.value[wcslen(es_token_keyword_import)] = 0;
                            wcscpy(token.value,es_token_keyword_import);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_import);
                        }
                    }
                    /** throw */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_throw,wcslen(es_token_keyword_throw))){
                        if(index + wcslen(es_token_keyword_throw) < wline.length() && (wline[index + wcslen(es_token_keyword_throw)] == L' ' || wline[index + wcslen(es_token_keyword_throw)] == L'\n' || wline[index + wcslen(es_token_keyword_throw)] == L'\t' || wline[index + wcslen(es_token_keyword_throw)] == L'\r')) {
                            es_token token;
                            token.type = es_token_throw;
                            token.value = new wchar_t[wcslen(es_token_keyword_throw) + 1];
                            token.value[wcslen(es_token_keyword_throw)] = 0;
                            wcscpy(token.value,es_token_keyword_throw);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_throw);
                        }
                    }
                    /** new */
                    else if(0 == wcsncmp(&wline[index],es_token_keyword_new,wcslen(es_token_keyword_new))){
                        if(index + wcslen(es_token_keyword_new) < wline.length() && (wline[index + wcslen(es_token_keyword_new)] == L' ' || wline[index + wcslen(es_token_keyword_new)] == L'\n' || wline[index + wcslen(es_token_keyword_new)] == L'\t' || wline[index + wcslen(es_token_keyword_new)] == L'\r')) {
                            es_token token;
                            token.type = es_token_new;
                            token.value = new wchar_t[wcslen(es_token_keyword_new) + 1];
                            token.value[wcslen(es_token_keyword_new)] = 0;
                            wcscpy(token.value,es_token_keyword_new);
                            tokens.push_back(token);
#ifdef DEBUG
                            std::cout << " ** deal with keyword : " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(token.value) << "  line index: " << line_index << "  char index: " << index << std::endl;
#endif
                            index += wcslen(es_token_keyword_new);
                        }
                    }
                    /** unsure */
                    else {
                        std::wstring unsure;
                        // && !mask()
                        // std::cout << "unsure begin :" << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes(wline[index]) << std::endl;
                        while(index < wline.length() && !es_token_is_mask(wline[index]) && wline[index] != L'\n' && wline[index] != L'\t' && wline[index] != L'\r'){
                            unsure += wline[index];
                            index ++;
                        }
                        es_token token;
                        token.type = es_token_unsure;
                        token.value = new wchar_t[unsure.length() + 1];
                        memset(token.value, 0, sizeof(wchar_t) * (unsure.length() + 1));
                        memcpy(token.value, unsure.c_str(), sizeof(wchar_t) * unsure.length());
                        tokens.push_back(token);
                    }
                }break;
            }
            //index++;
        }
        line_index ++;
    }
    /** 编码测试 */
    // ostream.close();
#ifdef DEBUG
    std::cout << "tokens : " << std::endl;
    for(ES_token_array::iterator iter = tokens.begin(); iter!= tokens.end();iter ++){
        std::cout << " token: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>{}.to_bytes((*iter).value) << std::endl;
#endif
    }

    return 0;
}
