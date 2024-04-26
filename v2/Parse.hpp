#pragma once


#include "Getter.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <span>
#include <string>
#include <vector>


inline static std::span<wchar_t> trim(std::span<wchar_t> sp){
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

inline static std::vector<std::span<wchar_t>> parse_terms(const std::span<wchar_t>& sp){
    std::vector<std::span<wchar_t>> terms;
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
            terms.emplace_back(trim(sp.subspan(pos, i-pos)));
            pos = i+1;
            continue;
        }
    }
    if(pos+1 != sp.size())
        terms.emplace_back(trim(sp.subspan(pos)));
    return terms;
};

static inline std::wstring& rm_spaces(std::wstring& ws){
    std::erase(ws, L' ');
    return ws;
}


inline static std::shared_ptr<Getter> parse(std::span<wchar_t> wc){



    return  {};
}

