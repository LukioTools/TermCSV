#pragma once

#include "../Getter.hpp"
#include "../Getters/getters.hpp"
#include "identify_term.hpp"
#include <memory>

std::shared_ptr<Getter> parse_term(const std::span<const std::unicode> &view){
    auto spt = identify_term(view);
    //UNKNOWN,
    //VALUE,
    //CELL_SPAN,
    //FUNCTION,
    switch (spt) {
        case TermType::VALUE:
            return Getters::value::shared(eval_value::create(view));
        case TermType::CELL_SPAN:
            return std::make_shared<Getters::cell_range>(view);
        case TermType::FUNCTION:{
            return parse_function(view);
        }
        default:
        case TermType::UNKNOWN:
            return nullptr;
    }

};