#pragma once
#include <functional>
#include <span>
#include <type_traits>
#include <utility>
#include <variant>
#include "../headers/Equation.hpp"
#include "../headers/Sheet.hpp"
#include "../headers/Cell.hpp"





#include "Cell.hpp"
#include "Sheet.hpp"



inline eval_value add_f(Sheet& s, std::span<cell_value> cv){
    eval_value out = 0L;
    for(const auto& e : cv){
        out=e.eval(s)+out;
    }
    return out;
}

inline eval_value multiply_f(Sheet& s, std::span<cell_value> cv){
    eval_value out = 0L;
    for(const auto& e : cv){
        out=e.eval(s)*out;
    }
    return out;
}



