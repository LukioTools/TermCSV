#pragma once


#include <cmath>
#include <codecvt>
#include <exception>
#include <iostream>
#include <locale>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <variant>

struct Eval : public std::variant<std::monostate, std::wstring, long, double>{

    enum {
        NONE,
        STRING,
        INTEGER,
        FLOAT
    };
    using std::variant<std::monostate, std::wstring, long, double>::variant;
    using std::variant<std::monostate, std::wstring, long, double>::operator=;
    using std::variant<std::monostate, std::wstring, long, double>::emplace;
    using std::variant<std::monostate, std::wstring, long, double>::index;
    using std::variant<std::monostate, std::wstring, long, double>::swap;
    using std::variant<std::monostate, std::wstring, long, double>::valueless_by_exception;
    Eval(const std::variant<std::monostate, std::wstring, long, double>& v): std::variant<std::monostate, std::wstring, long, double>(v){};

    std::wstring to_wstring()const {
        switch (index()) {
            case NONE:  return {};
            case STRING:    return std::get<STRING>(*this);
            case INTEGER:   return std::to_wstring(std::get<INTEGER>(*this));
            case FLOAT: return std::to_wstring(std::get<FLOAT>(*this));
            default:    return L"INVALID";
        }
    }

    std::string to_string()const {
        switch (index()) {
            case NONE:  return {};
            case STRING:    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(std::get<STRING>(*this));
            case INTEGER:   return std::to_string(std::get<INTEGER>(*this));
            case FLOAT: return std::to_string(std::get<FLOAT>(*this));
            default:    return "INVALID";
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const Eval& ev){
        os << ev.to_string();
        return os;
    }
    friend std::wostream& operator<<(std::wostream& os, const Eval& ev){
        os << ev.to_wstring();
        return os;
    }

    template<int TYPE>
    auto& as() const{
        return std::get<TYPE>(*this);
    }

    template<typename T>
    requires(std::is_arithmetic_v<T>)
    Eval operator+(const T& l) const {
        switch (index()) {
            case STRING:    return as<STRING>() + std::to_wstring(l);
            case INTEGER:   return as<INTEGER>() + l;
            case FLOAT: return as<FLOAT>() + l;
            case NONE:  default:  return l;
        }
    }
    Eval operator+(const std::wstring& l) const {
        switch (index()) {
            case STRING: return as<STRING>() + l;
            case INTEGER: return std::to_wstring(as<INTEGER>()) + l;
            case FLOAT: return std::to_wstring(as<FLOAT>()) + l;
            case NONE: default: return l;
        }
    }
    Eval operator+(const Eval& e) const {
        switch (e.index()) {
            case STRING: return this->operator+(e.as<STRING>());
            case INTEGER: return this->operator+(e.as<INTEGER>());
            case FLOAT: return this->operator+(e.as<FLOAT>());
            case NONE: default: return *this;
        }
    }
    template<typename T>
    requires(std::is_integral_v<T>)
    std::wstring repeat(const std::wstring& str,  const T& times){
        std::wstring out;
        for(std::size_t i = 0; i < times; i++)
            out+=str;
        return out;
    }
    template<typename T>
    requires(std::is_floating_point_v<T>)
    std::wstring repeat(const std::wstring& str,  const T& times){
        std::wstring out;
        for(std::size_t i = 0; i < times; i++)
            out+=str;
        double frac = std::modf(times);
        if(frac > 1) frac = 1;
        size_t n = str.size()*frac;
        out.append(str.begin(), str.begin()+n);
        return out;
    }

    template<typename T>
    requires(std::is_arithmetic_v<T>)
    Eval operator*(const T& l) const {
        switch (index()) {
            case STRING: return repeat(as<STRING>(), l);
            case INTEGER:   return as<INTEGER>() * l;
            case FLOAT: return as<FLOAT>() * l;
            case NONE:  default:  return std::monostate();
        }
    }
    Eval operator*(const std::wstring& l) const {
        switch (index()) {
            case STRING: return as<STRING>() + l;
            case INTEGER: return std::to_wstring(as<INTEGER>()) + l;
            case FLOAT: return std::to_wstring(as<FLOAT>()) + l;
            case NONE: default: return l;
        }
    }
    Eval operator*(const Eval& e) const {
        switch (e.index()) {
            case STRING: return this->operator+(e.as<STRING>());
            case INTEGER: return this->operator+(e.as<INTEGER>());
            case FLOAT: return this->operator+(e.as<FLOAT>());
            case NONE: default: return *this;
        }
    }


};