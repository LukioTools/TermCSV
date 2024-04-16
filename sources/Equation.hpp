#pragma once
#include <functional>
#include <span>
#include <utility>
#include <variant>
#include "../headers/Equation.hpp"
#include "../headers/Sheet.hpp"
#include "../headers/Cell.hpp"





#include "Cell.hpp"
#include "Sheet.hpp"
inline cell_value Equation::multiply(Sheet& s, std::span<cell_value> cv){
    cell_value out = 0L;
    for(auto& e : cv){
        switch (e.index()) {
            case cell_value::INTEGER: //e == long
            {
                auto t = e.as<out.INTEGER>();
                switch (out.index()) {
                    case cell_value::INTEGER:
                        out = out.as<out.INTEGER>() + t;
                        break;
                    case cell_value::FLOATING:
                        out = out.as<cell_value::FLOATING>() + t;
                        break;
                    default:
                        out = t;
                }
                break;
            }
            case cell_value::FLOATING:
            {
                auto t = e.as<out.FLOATING>();
                switch (out.index()) {
                    case cell_value::INTEGER:
                        out = out.as<out.INTEGER>() + t;
                        break;
                    case cell_value::FLOATING:
                        out = out.as<cell_value::FLOATING>() + t;
                        break;
                    default:
                        out = t;
                }
                break;
            }
            case cell_value::EQUATION:{
                auto t = e.as<out.EQUATION>().eval(s);
                switch (out.index()) {
                    case cell_value::INTEGER:
                        out = out.as<out.INTEGER>() + t;
                        break;
                    case cell_value::FLOATING:
                        out = out.as<cell_value::FLOATING>() + t;
                        break;
                    default:
                        out = t;
                }
            }

            default:
                break;
        }
    }
    return out;
}


