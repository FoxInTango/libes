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

/**
 * bracket 圆括号
 * angle   尖括号
 * square  方括号
 * Braces  大括号
 */

/** Todo
 *  this
 *  super
 *  auguments
 *  
 *  constructor
 *  prototype
 *  extends
 * 
 *  true
 *  false
 * 
 *  number
 * 
 *  if 
 *  else
 *  else if
 *  
 *  switch 
 *  case 
 *  default
 *  
 *  do
 *  while
 *  for 
 *  in
 * 
 *  continue
 *  break
 *  return 
 *
 *  try
 *  cach
 *
 *  static
 * 
 *  typeof
 *  instanceof
 *  +
 *  -
 *  * 
 *  /
 *  ^
 *  %
 *  = 
 *  get
 *  set
 *  ==
 *  ===
 *  !
 *  &
 *  |
 *  ~
 *  ||
 *  &&
 */

#define es_number_0 L'0'
#define es_number_1 L'1'
#define es_number_2 L'2'
#define es_number_3 L'3'
#define es_number_4 L'4'
#define es_number_5 L'5'
#define es_number_6 L'6'
#define es_number_7 L'7'
#define es_number_8 L'8'
#define es_number_9 L'9'

#define es_token_mark_bracket_l    L'('
#define es_token_mark_bracket_r    L')'
#define es_token_mark_angle_l      L'<'
#define es_token_mark_angle_r      L'>'
#define es_token_mark_square_l     L'['
#define es_token_mark_square_r     L']'
#define es_token_mark_brace_l      L'{'
#define es_token_mark_brace_r      L'}'
#define es_token_mark_dot          L'.'
#define es_token_mark_space        L' '
#define es_token_mark_quote_s      L'\''
#define es_token_mark_quote_d      L'"'
#define es_token_mark_colon        L':'
#define es_token_mark_semi         L';'

#define es_token_keyword_const     L"const"
#define es_token_keyword_var       L"var"
#define es_token_keyword_let       L"let"
#define es_token_keyword_function  L"function"
#define es_token_keyword_class     L"class"
#define es_token_keyword_export    L"export"
#define es_token_keyword_import    L"import"
#define es_token_keyword_throw     L"throw"
#define es_token_keyword_new       L"new"

 /**
  * bracket  ()
  * angle    <>
  * square   []
  * Braces   {}
  */
#define es_unsure             0
#define es_token_bracket_l    1
#define es_token_bracket_r    2
#define es_token_angle_l      3
#define es_token_angle_r      4
#define es_token_square_l     5
#define es_token_square_r     6
#define es_token_brace_l      7
#define es_token_brace_r      8
#define es_token_dot          9
#define es_token_space        10
#define es_token_quote_s      11
#define es_token_quote_d      12

#define es_token_const        13
#define es_token_var          14
#define es_token_let          15
#define es_token_function     16
#define es_token_class        17
#define es_token_export       18
#define es_token_import       19
#define es_token_throw        20
#define es_token_colon        21
#define es_token_semi         22
#define es_token_new          23
#define es_token_number       24
#define es_token_bool         25

typedef struct _es_token {
int type;
wchar_t* value;
}es_token;
#endif
