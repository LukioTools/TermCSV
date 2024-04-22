#pragma once

#include <regex>
#include <span>
#include "../../../Term3D/Unicode/Unicode.hpp"

enum TermType{
    UNKNOWN,
    VALUE,
    CELL_SPAN,
    FUNCTION,
};
inline static TermType identify_term(const std::span<const std::unicode> span){
    if(span.empty()) return UNKNOWN;
    static const std::wregex is_span(L"^!?\\d+:!?\\d+->!?\\d+:!?\\d+$");
    static const std::wregex is_fn(L"^\\w+\\(.*\\)$");
    if(std::regex_match(span.begin(), span.end(), is_span)) return CELL_SPAN;
    if(std::regex_match(span.begin(), span.end(), is_fn)) return FUNCTION;
    return VALUE;   //its the problem of the value constructor to determine what kind of value it is
}