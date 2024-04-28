#pragma once


#include "../Getter.hpp"
#include "../Getters/CellRange.hpp"
#include "../Getters/Function.hpp"
#include "../Getters/Value.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <span>
#include <string_view>
#include <variant>
#include <vector>
#include "Parse.hpp"


inline std::span<const wchar_t> trim(std::span<const wchar_t> sp){
    for(std::size_t i = 0; i < sp.size(); i++){
        if(sp[i] != L' '){
            sp = sp.subspan(i);
            break;
        }
    }
    std::size_t i = sp.size();
    while (i) {
        --i;
        std::wcout << i << ": " << sp[i] << std::endl;
        if(sp[i] != L' '){
            sp = sp.subspan(0, i+1);
            break;
        }
    }
    return sp;
}


std::vector<std::span<const wchar_t>> parse_terms(const std::span<const wchar_t>& sp){
    std::vector<std::span<const wchar_t>> terms;
    std::size_t pos = 0;
    long depth = 0;
    for(std::size_t i = 0; i < sp.size(); i++){
        auto e = sp[i];
        if(e == '('){
            ++depth;
            continue;
        }
        else if(e == ')'){
            --depth;
            continue;
        }
        else if(e == ',' && depth == 0){
            auto s = trim(sp.subspan(pos, i-pos));
            if(!s.empty()) terms.emplace_back(s);
            pos = i+1;
            continue;
        }
    }
    if(pos+1 != sp.size()){
        auto s = trim(sp.subspan(pos));
        if(!s.empty()) terms.emplace_back(s);
        terms.emplace_back(s);
    }

    return terms;
};


inline std::unique_ptr<split_function_t> split_function(const std::span<const wchar_t> span){
    std::wstring_view sw(span.begin(), span.end());
    auto b =  sw.find_first_of('(');
    auto e =  sw.find_last_of(')');

    if( b == std::variant_npos || 
        e == std::variant_npos || 
        e < b+1 
    ) return nullptr;

    return std::make_unique<split_function_t>(
        span.subspan(0, b),
        span.subspan(b+1,e-b)
    );
}



inline std::vector<std::shared_ptr<Getter>> parse(const std::span<const wchar_t> wc){
    std::vector<std::shared_ptr<Getter>> out;
    auto terms = parse_terms(trim(wc));
    for(auto& e : terms){
        using namespace Getters;

        if(CellRange::is_cellrange(e)){
            auto getter = CellRange::create(e);
            if(getter) out.emplace_back(getter);
        }
        else if (Function::is_function(e)) {
            auto getter = Function::create(e);
            if(getter) out.emplace_back(getter);
        }
        else if(!e.empty()){
            auto getter = Value::create(e);
            if(getter) out.emplace_back(getter);
        }
    }

    return  out;
}

