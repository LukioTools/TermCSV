#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <variant>
#include "../../Term3D/Unicode/Unicode.hpp"
#include "../headers/Cell.hpp"
#include "../headers/Equation.hpp"
#include "../headers/Column.hpp"


class cell_value : public std::variant<std::monostate, std::ustring, long, double, Equation, std::chrono::time_point<std::chrono::system_clock>>{
public:
    using std::variant<std::monostate, std::ustring, long, double, Equation, std::chrono::time_point<std::chrono::system_clock>>::variant;
    using std::variant<std::monostate, std::ustring, long, double, Equation, std::chrono::time_point<std::chrono::system_clock>>::operator=;
    using std::variant<std::monostate, std::ustring, long, double, Equation, std::chrono::time_point<std::chrono::system_clock>>::emplace;
    using std::variant<std::monostate, std::ustring, long, double, Equation, std::chrono::time_point<std::chrono::system_clock>>::index;
    using std::variant<std::monostate, std::ustring, long, double, Equation, std::chrono::time_point<std::chrono::system_clock>>::swap;
    using std::variant<std::monostate, std::ustring, long, double, Equation, std::chrono::time_point<std::chrono::system_clock>>::valueless_by_exception;

    enum {
        NONE,
        STRING,
        INTEGER,
        FLOATING,
        EQUATION,
        TIMEPOINT,
    };

    template<std::size_t e>
    auto& as() const{
        return std::get<e>(*this);
    }

    eval_value add(Sheet& s, const eval_value& e) const{
        return e.add(eval(s));
    }

    eval_value multiply(Sheet& s, const eval_value& e) const{
        return e.multiply(eval(s));
    }


    eval_value eval(Sheet& s)const{
        switch (index()) {
            case INTEGER:
                return  as<INTEGER>();
            case cell_value::FLOATING:
                return as<FLOATING>();
            case cell_value::EQUATION:
                return as<EQUATION>().eval(s);
            default:
                return std::monostate();
        }
    }

    
};
struct Cell
{
public:
    cell_value value = std::monostate();
    Column* parent = nullptr;

    static std::unique_ptr<Cell> unique(){
        return std::make_unique<Cell>();
    }
};
