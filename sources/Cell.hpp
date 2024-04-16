#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <variant>
#include "../../Term3D/Unicode/Unicode.hpp"
#include "../headers/Cell.hpp"
#include "../headers/Equation.hpp"


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
    auto& as(){
        return std::get<e>(*this);
    }
};
struct Cell
{
public:
    cell_value value = std::monostate();

    static std::unique_ptr<Cell> unique(){
        return std::make_unique<Cell>();
    }
};
