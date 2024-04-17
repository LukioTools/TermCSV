#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <tuple>
#include <type_traits>
#include <variant>
#include "../../Term3D/Unicode/Unicode.hpp"
#include "../headers/Cell.hpp"
#include "../headers/Function.hpp"
#include "../headers/Column.hpp"


class cell_value : public std::variant<std::monostate, std::ustring, long, double, Function, std::chrono::time_point<std::chrono::system_clock>>{
public:
    using std::variant<std::monostate, std::ustring, long, double, Function, std::chrono::time_point<std::chrono::system_clock>>::variant;
    using std::variant<std::monostate, std::ustring, long, double, Function, std::chrono::time_point<std::chrono::system_clock>>::operator=;
    using std::variant<std::monostate, std::ustring, long, double, Function, std::chrono::time_point<std::chrono::system_clock>>::emplace;
    using std::variant<std::monostate, std::ustring, long, double, Function, std::chrono::time_point<std::chrono::system_clock>>::index;
    using std::variant<std::monostate, std::ustring, long, double, Function, std::chrono::time_point<std::chrono::system_clock>>::swap;
    using std::variant<std::monostate, std::ustring, long, double, Function, std::chrono::time_point<std::chrono::system_clock>>::valueless_by_exception;

    enum {
        NONE,
        STRING,
        INTEGER,
        FLOATING,
        FUNCTION,
        TIMEPOINT,
    };

    template<std::size_t e>
    auto& as() const{
        return std::get<e>(*this);
    }
    template<class T>
    auto& get(){
        return std::get<T>(*this);
    }
    template<class T>
    auto& cget()const{
        return std::get<T>(*this);
    }
    template<class T>
    T& set(T&& obj){
        this->operator=(obj);
        return get<T>();
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
            case cell_value::FUNCTION:
                return as<FUNCTION>().eval(s);
            default:
                return std::monostate();
        }
    }

    
};
struct Cell : public cell_value
{
public:
    Column* parent;

    using cell_value::operator=;

    static std::unique_ptr<Cell> unique(Column* parent){
        return std::make_unique<Cell>(parent);
    }
    Cell(Column* parent, const cell_value& cv = std::monostate()): cell_value(cv), parent(parent){}
};
