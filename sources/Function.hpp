#pragma once

#include "../headers/Function.hpp"
#include "../headers/Getters/getters.hpp"
#include <memory>


std::shared_ptr<Getter> Function::parse_value(const std::span<const std::unicode>& args){
    return nullptr;
};
std::shared_ptr<Getter> Function::parse_cell_range(const std::span<const std::unicode>& args){
    return Getters::cell_range::shared(args);
};

std::shared_ptr<Getter> Function::parse_term(const std::span<const std::unicode> &view){
    auto spt = identify_term(view);
    //UNKNOWN,
    //VALUE,
    //CELL_SPAN,
    //FUNCTION,
    switch (spt) {
        case Function::VALUE:
            return Function::parse_value(view);
        case Function::CELL_SPAN:
            return Function::parse_cell_range(view);
        case Function::FUNCTION:{
            return Function::parse_function(view);
        }
        default:
        case Function::UNKNOWN:
            return nullptr;
    }

};

std::shared_ptr<Getter> Function::parse_function(const std::span<const std::unicode>& whole_string){
    Function fn;
    auto func = Function::parse_func(whole_string);
    auto args = Function::parse_terms(func.second);
    auto it = parsers.find(to_string(func.first));
    if(it == parsers.end())
        return Getters::function_getter::shared({});
    fn.func(it->second);
    for(auto& e : args){
        auto term = parse_term(e);
        if(term) fn.add(term);
    }
    return Getters::function_getter::shared(std::move(fn));
}



