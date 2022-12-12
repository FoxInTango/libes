#include "es_token.h"
#include <set>

static std::set<wchar_t> mask_set;
static wchar_t es_token_mask_null = 0;
wchar_t mask_table[] = {
es_number_0,
es_number_1,
es_number_2,
es_number_3,
es_number_4,
es_number_5,
es_number_6,
es_number_7,
es_number_8,
es_number_9,
es_token_mark_bracket_l,
es_token_mark_bracket_r,
es_token_mark_angle_l,
es_token_mark_angle_r,
es_token_mark_square_l,
es_token_mark_square_r,
es_token_mark_brace_l,
es_token_mark_brace_r,
es_token_mark_dot,
es_token_mark_space,
es_token_mark_quote_s,
es_token_mark_quote_d,
es_token_mark_colon,
es_token_mark_semi,
es_token_mark_slash,
es_token_mark_bslash,
es_token_mark_vbar,
es_token_mark_wave,
es_token_mark_woo,
es_token_mark_at,
es_token_mark_sharp,
es_token_mark_usd,
es_token_mark_percent,
es_token_mark_arrow_up,
es_token_mark_and,
es_token_mark_what,
es_token_mark_comma,
es_token_mark_cross,
es_token_mark_hyphen,
es_token_mark_star,
es_token_mark_dhbar,
es_token_mask_null
};

void es_token_init() {
    int mask_index = 0;
    while(mask_table[mask_index] != es_token_mask_null){
        mask_set.insert(mask_table[mask_index]);
        mask_index ++;
    }
}

bool es_token_is_mask(const wchar_t& c){
    return mask_set.count(c);
}