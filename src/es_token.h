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
#ifndef _es_token_h_
#define _es_token_h_

#define es_number_0  L'0'
#define es_number_1  L'1'
#define es_number_2  L'2'
#define es_number_3  L'3'
#define es_number_4  L'4'
#define es_number_5  L'5'
#define es_number_6  L'6'
#define es_number_7  L'7'
#define es_number_8  L'8'
#define es_number_9  L'9'
#define es_number_0b L"0b"  // 二进制
#define es_number_0B L"0B"  // 二进制
#define es_number_0x L"0x"  // 十六进制
#define es_number_0X L"0X"  // 十六进制
#define es_number_0o L"0o"  // 八进制
#define es_number_0O L"0O"  // 八进制
#define es_number_e  L'e'   // 科学计数法
#define es_number_E  L'E'   // 科学计数法

/**
 * bracket  ()
 * angle    <>
 * square   []
 * braces   {}
 */
#define es_token_mark_bracket_l            L'('
#define es_token_mark_bracket_r            L')'
#define es_token_mark_angle_l              L'<' // 1 < | 2 << | 3 <=
#define es_token_mark_angle_r              L'>' // 1 > | 2 >> | 3 >=
#define es_token_mark_square_l             L'[' 
#define es_token_mark_square_r             L']'
#define es_token_mark_brace_l              L'{'
#define es_token_mark_brace_r              L'}'
#define es_token_mark_dot                  L'.'
#define es_token_mark_space                L' '
#define es_token_mark_quote_s              L'\''
#define es_token_mark_quote_d              L'"'
#define es_token_mark_colon                L':'
#define es_token_mark_semi                 L';'
#define es_token_mark_slash                L'/' // 1 / | 2 // | 3 /* | 4 */
#define es_token_mark_bslash               L'\\'
#define es_token_mark_vbar                 L'|' // 1 | | 2 || | 3 |=
#define es_token_mark_wave                 L'~' // 1 ~ | 2 ~= 
#define es_token_mark_woo                  L'!' // 1 ! | 2 != | 3 !==
#define es_token_mark_at                   L'@' // PASS
#define es_token_mark_sharp                L'#' // PASS
#define es_token_mark_usd                  L'$' // PASS
#define es_token_mark_percent              L'%' // 1 % | 2 %=
#define es_token_mark_arrow_up             L'^' // 1 ^ | 2 ^=
#define es_token_mark_and                  L'&' // 1 & | 2 && | 3 &=
#define es_token_mark_what                 L'?'
#define es_token_mark_comma                L','
#define es_token_mark_cross                L'+' // 1 + | 2 += | 3 ++
#define es_token_mark_hyphen               L'-' // 1 - | 2 -= | 3 --
#define es_token_mark_star                 L'*' // 1 * | 2 *= | 3 */
#define es_token_mark_dhbar                L'=' // 1 = | 2 == | 3 ===

#define es_token_operator_assign           L'='
#define es_token_operator_assign_add       L"+="
#define es_token_operator_assign_add_s     L"++"
#define es_token_operator_assign_sub       L"-="
#define es_token_operator_assign_sub_s     L"--"

#define es_token_operator_assign_mul       L"*="
#define es_token_operator_assign_exc       L"/="
#define es_token_operator_assign_mod       L"%="
#define es_token_operator_assign_exp       L"^="
#define es_token_operator_assign_bw_and    L"&="
#define es_token_operator_assign_bw_or     L"|="
#define es_token_operator_assign_bw_not    L"~="

#define es_token_operator_add              L'+'
#define es_token_operator_sub              L'-'
#define es_token_operator_mul              L'*'
#define es_token_operator_exc              L'/'
#define es_token_operator_mod              L'%'
#define es_token_operator_exp              L'^'

#define es_token_operator_what             L'?'
#define es_token_operator_comma            L','
/**
 * bw : bitwise  
 */
#define es_token_operator_bw_and           L'&'
#define es_token_operator_bw_or            L'|'
#define es_token_operator_bw_xor           L'^'
#define es_token_operator_bw_not           L'~'
#define es_token_operator_shift_l          L"<<"
#define es_token_operator_shift_r          L">>"
/**
 * lg : logic
 */
#define es_token_operator_lg_and           L"&&"
#define es_token_operator_lg_or            L"||"
#define es_token_operator_lg_not           L'!'

#define es_token_comment_short             L"//"
#define es_token_comment_long_l            L"/*"
#define es_token_comment_long_r            L"*/"
/**
 * c : compare
 * g : greater
 * l : less
 * e : equal
 * f : full
 */
#define es_token_operator_cg               L'>'
#define es_token_operator_cl               L'<'
#define es_token_operator_cge              L">="
#define es_token_operator_cle              L"<="
#define es_token_operator_ce               L"=="
#define es_token_operator_cef              L"==="
#define es_token_operator_ne               L"!="
#define es_token_operator_nef              L"!=="

#define es_token_operator_typeof           L"typeof"
#define es_token_operator_instof           L"instanceof"

#define es_token_keyword_this              L"this"
#define es_token_keyword_super             L"super"
#define es_token_keyword_consfun           L"constructor"
#define es_token_keyword_extends           L"extends"
#define es_token_keyword_set               L"set"
#define es_token_keyword_get               L"get"

#define es_token_keyword_true              L"true"
#define es_token_keyword_flase             L"false"
#define es_token_keyword_null              L"null"
#define es_token_keyword_undefined         L"undefined"

#define es_token_keyword_if                L"if"
#define es_token_keyword_else              L"else"
#define es_token_keyword_switch            L"switch"
#define es_token_keyword_case              L"case"
#define es_token_keyword_default           L"default"
#define es_token_keyword_do                L"do"
#define es_token_keyword_while             L"while"
#define es_token_keyword_for               L"for"
#define es_token_keyword_in                L"in"
#define es_token_keyword_try               L"try"
#define es_token_keyword_catch             L"catch"
#define es_token_keyword_continue          L"continue"
#define es_token_keyword_break             L"break"
#define es_token_keyword_return            L"return"

#define es_token_keyword_static            L"static"
#define es_token_keyword_const             L"const"
#define es_token_keyword_var               L"var"
#define es_token_keyword_let               L"let"
#define es_token_keyword_function          L"function"
#define es_token_keyword_class             L"class"
#define es_token_keyword_export            L"export"
#define es_token_keyword_import            L"import"
#define es_token_keyword_throw             L"throw"
#define es_token_keyword_new               L"new"

#define es_token_unsure        0
#define es_token_bracket_l     1     // L'('
#define es_token_bracket_r     2     // L')'
#define es_token_angle_l       3     // L'<'
#define es_token_angle_r       4     // L'>'
#define es_token_square_l      5     // L'['
#define es_token_square_r      6     // L']'
#define es_token_brace_l       7     // L'{'
#define es_token_brace_r       8     // L'}'
#define es_token_dot           9     // L'.'
#define es_token_space         10    // L' '
#define es_token_quote_s       11    // L'\'
#define es_token_quote_d       12    // L'"'
#define es_token_colon         13    // L':'
#define es_token_semi          14    // L';'
#define es_token_slash         15    // L'/'
#define es_token_bslash        16    // L'\'
#define es_token_vbar          17    // L'|'
#define es_token_wave          18    // L'~'
#define es_token_woo           19    // L'!'
#define es_token_at            20    // L'@'
#define es_token_sharp         21    // L'#'
#define es_token_usd           22    // L'$'
#define es_token_percent       23    // L'%'
#define es_token_arrow_up      24    // L'^'
#define es_token_and           25    // L'&'
#define es_token_what          26    // L'?'
#define es_token_comma         27    // L','

#define es_token_assign        28    // L'='
#define es_token_assign_add    29    // L"+="
#define es_token_assign_add_s  30    // L"++"
#define es_token_assign_sub    31    // L"-="
#define es_token_assign_sub_s  32    // L"--"
#define es_token_assign_mul    33    // L"*="
#define es_token_assign_exc    34    // L"/="
#define es_token_assign_mod    35    // L"%="
#define es_token_assign_exp    36    // L"^="
#define es_token_assign_bw_and 37    // L"&="
#define es_token_assign_bw_or  38    // L"|="
#define es_token_assign_bw_not 39    // L"~="

#define es_token_add           40    // L'+'
#define es_token_sub           41    // L'-'
#define es_token_mul           42    // L'*'
#define es_token_exc           43    // L'/'
#define es_token_mod           44    // L'%'
#define es_token_exp           45    // L'^'

#define es_token_bw_and        46    // L'&'
#define es_token_bw_or         47    // L'|'
#define es_token_bw_xor        48    // L'^'
#define es_token_bw_not        49    // L'~'
#define es_token_shift_l       50    // L"<<"
#define es_token_shift_r       51    // L">>"

#define es_token_lg_and        52    // L"&&"
#define es_token_lg_or         53    // L"||"
#define es_token_lg_not        54    // L'!'

#define es_token_cg            55    // L'>'
#define es_token_cl            56    // L'<'
#define es_token_cge           57    // L">="
#define es_token_cle           58    // L"<="
#define es_token_ce            59    // L"=="
#define es_token_cef           60    // L"==="
#define es_token_ne            61    // L"!="
#define es_token_nef           62    // L"!=="

#define es_token_typeof        63    // L"typeof"      https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Operators/typeof
#define es_token_instof        64    // L"instanceof"  https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Operators/instanceof

#define es_token_new           65     // L"new"
#define es_token_this          66     // L"this"
#define es_token_super         67     // L"super"
#define es_token_consfun       68     // L"constructor"
#define es_token_extends       69     // L"extends"
#define es_token_set           70     // L"set"
#define es_token_get           71     // L"get"

#define es_token_true          72    // L"true"
#define es_token_flase         72    // L"false"
#define es_token_null          73    // L"null"
#define es_token_undefined     74    // L"undefined"
#define es_token_number        75    
#define es_token_0             76    // L'0'
#define es_token_1             77    // L'1'
#define es_token_2             78    // L'2'
#define es_token_3             79    // L'3'
#define es_token_4             80    // L'4'
#define es_token_5             81    // L'5'
#define es_token_6             82    // L'6'
#define es_token_7             83    // L'7'
#define es_token_8             84    // L'8'
#define es_token_9             85    // L'9'
#define es_token_0b            86    // L"0b" // 二进制
#define es_token_0B            87    // L"0B" // 二进制
#define es_token_0x            88    // L"0x" // 十六进制
#define es_token_0X            89    // L"0X" // 十六进制
#define es_token_0o            90    // L"0o" // 八进制
#define es_token_0O            91    // L"0O" // 八进制
#define es_token_e             92    // L'e'   // 科学计数法
#define es_token_E             93    // L'E'   // 科学计数法

#define es_token_if            94    // L"if"
#define es_token_else          95    // L"else"
#define es_token_switch        96    // L"switch"
#define es_token_case          97    // L"case"
#define es_token_default       98    // L"default"
#define es_token_do            99    // L"do"
#define es_token_while         100   // L"while"
#define es_token_for           101   // L"for"
#define es_token_in            102   // L"in"
#define es_token_try           103   // L"try"
#define es_token_catch         104   // L"catch"
#define es_token_continue      105   // L"continue"
#define es_token_break         106   // L"break"
#define es_token_return        107   // L"return"

#define es_token_static        108   // L"static"
#define es_token_const         109   // L"const"
#define es_token_var           110   // L"var"
#define es_token_let           111   // L"let"
#define es_token_function      112   // L"function"
#define es_token_class         113   // L"class"
#define es_token_export        114   // L"export"
#define es_token_import        115   // L"import"
#define es_token_throw         116   // L"throw"

#define es_token_comment_s     117   // L"//"
#define es_token_comment_l     118   // L"/*"
#define es_token_comment_r     119   // L"*/"

typedef struct _es_token {
int type;
wchar_t* value;
wchar_t* documentURL;
unsigned int lineIndex;
unsigned int charIndex;
}es_token;

void es_token_init();
bool es_token_is_mask(const wchar_t& c);
#endif
