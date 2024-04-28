#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <variant>

struct Eval : public std::variant<std::monostate, std::wstring, long, double> {

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
    Eval(const std::variant<std::monostate, std::wstring, long, double>& v);

    std::wstring to_wstring()const;

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Eval& ev);
    friend std::wostream& operator<<(std::wostream& os, const Eval& ev);

    template<int TYPE>
    auto& as() const;

    template<typename T>
    requires(std::is_arithmetic_v<T>)
    Eval operator+(const T& l)const;
    Eval operator+(const std::wstring& l) const;
    Eval operator+(const Eval& e)const;
    template<typename T>
    requires(std::is_integral_v<T>)
    inline static std::wstring repeat(const std::wstring& str,  const T& times);

    template<typename T>
    requires(std::is_floating_point_v<T>)
    inline static std::wstring repeat(const std::wstring& str,  const T& times);

    template<typename T>
    requires(std::is_arithmetic_v<T>)
    Eval operator*(const T& l) const;
    Eval operator*(const std::wstring& l) const;
    Eval operator*(const Eval& e) const;

    /////////////////////POW////////////////////////
    /*
    returns 1 if any of the inputs is a string or other non arithmetic type
    */
    Eval operator^(const std::wstring& exponent)const;
    template<typename T>
    requires(std::is_arithmetic_v<T>)
    Eval operator^(const T& exponent)const;
        //pow
    Eval operator^(const Eval& e) const;

    /////////////////////MODULO////////////////////////
    Eval operator%(const std::wstring& exponent) const;
    template<typename T>
    requires(std::is_integral_v<T>)
    Eval operator%(const T& exponent)const;
    template<typename T>
    requires(std::is_floating_point_v<T>)
    Eval operator%(const T& exponent)const;
    Eval operator%(const Eval& e)const;



    Eval invert() const;
    Eval negate() const;
    Eval operator/(const Eval& e) const;
    Eval operator-(const Eval& e) const;

};