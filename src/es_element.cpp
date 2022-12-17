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
#include "es_element.h"
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
/**
 * objects:
 *     var obj = {} | "" | 2000 | ["","",{}];
 *     let obj = same as var;
 * expressions:
 *     obj.member1,member2,member3
 *     obj = a + b * (c + d);
 * switch:
 *     
 *     
 */
typedef std::vector<foxintango::es_element*> ES_element_array;
typedef std::map<std::wstring, es_element*> ES_element_name_map;

namespaceBegin(foxintango)
class es_element_implement{
public:
    es_element*         owner;
    es_context*         context;
    ES_element_array    subelements;
public:
    es_element_implement(){

    }

    ~es_element_implement(){
    
    }
};

class es_element_string      :public es_element_implement{};
class es_element_number      :public es_element_implement{};
class es_element_array       :public es_element_implement{};
class es_element_object      :public es_element_implement{};

class es_element_return      :public es_element_implement{};/** jump to higher level*/
class es_element_break       :public es_element_implement{};
class es_element_continue    :public es_element_implement{};

class es_element_scope       :public es_element_implement{
public:
    ES_element_name_map elementMap;
};/** () | {} */
class es_element_expression  :public es_element_scope{};
class es_element_function    :public es_element_scope{};
class es_element_switch      :public es_element_scope{};/** if | switch */
class es_element_for         :public es_element_scope{};
class es_element_while       :public es_element_scope{};
class es_element_do          :public es_element_scope{};
class es_element_in          :public es_element_scope{};
class es_element_try         :public es_element_scope {};
namespaceEnd
