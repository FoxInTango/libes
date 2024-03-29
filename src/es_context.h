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
#ifndef _es_context_h_
#define _es_context_h_
#include <libast/libast.h>
#include <liburl/liburl.h>
#include <libcpp/libcpp.h>

EXTERN_C_BEGIN
namespaceBegin(foxintango)
/**
 * 判断文件类型,选择加载模块 
 */
class foxintangoAPI es_context :public ASTContext{
public:
    es_context();
   ~es_context();
public:
    ASTDocument* document_at(char* url);
public:
    int insert_global_element(ASTElement* e,const char* name=nullptr);
    int remove_global_element(ASTElement* e);
    int remove_global_element(const char* name=nullptr);
public:
    Error load_document(const URL& url);
public:
    Error load_language_module(const URL& url);
public:
    /**
     * script module & native module 
     */
    Error load_module(const URL& url);
};
namespaceEnd
EXTERN_C_END
#endif
