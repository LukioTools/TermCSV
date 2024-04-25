#pragma once


#include <codecvt>
#include <locale>
#include <ostream>
#include <string>
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
            case NONE:
                return {};
            case STRING:
                return std::get<STRING>(*this);
            case INTEGER:
                return std::to_wstring(std::get<INTEGER>(*this));
            case FLOAT:
                return std::to_wstring(std::get<FLOAT>(*this));
            default:
                return L"INVALID";
        }
    }

    std::string to_string()const {
        switch (index()) {
            case NONE:
                return {};
            case STRING:
                return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(std::get<STRING>(*this));
            case INTEGER:
                return std::to_string(std::get<INTEGER>(*this));
            case FLOAT:
                return std::to_string(std::get<FLOAT>(*this));
            default:
                return "INVALID";
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

};