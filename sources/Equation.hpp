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



inline Equation::eval_value Equation::add(Sheet& s, std::span<cell_value> cv){
    Equation::eval_value out = 0L;
    for(const auto& e : cv){
        out=e.add(s, out);
    }
    return out;
}

inline Equation::eval_value Equation::multiply(Sheet& s, std::span<cell_value> cv){
    Equation::eval_value out = 0L;
    for(const auto& e : cv){
        out=e.add(s, out);
    }
    return out;
}



