#pragma once
#include <variant>
#include "../../Term3D/Unicode/Unicode.hpp"

struct eval_value : public std::variant<std::monostate, std::ustring, long, double>
    {
    public:
        using std::variant<std::monostate, std::ustring, long, double>::variant;
        using std::variant<std::monostate, std::ustring, long, double>::operator=;
        using std::variant<std::monostate, std::ustring, long, double>::emplace;
        using std::variant<std::monostate, std::ustring, long, double>::index;
        using std::variant<std::monostate, std::ustring, long, double>::swap;
        using std::variant<std::monostate, std::ustring, long, double>::valueless_by_exception;

        enum {
            NONE,
            STRING,
            INTEGER,
            FLOATING,
        };


        template<std::size_t e>
        auto& as() const{
            return std::get<e>(*this);
        }
        public:

        template<class T>
        requires(std::is_arithmetic_v<T>)
        eval_value add(T n) const {
            switch (index()) {
                case STRING:
                    return as<STRING>() + std::to_wstring(n);
                case INTEGER:
                    return as<INTEGER>() + n;
                case FLOATING:
                    return as<FLOATING>()+n;
                case NONE:
                default:
                    return n;
            }
        }

        eval_value add(const std::ustring& n) const {
            return n + to_string();
        }

        std::ustring to_string() const {
            switch (index()) {
                case STRING: return as<STRING>();
                case INTEGER: return std::to_wstring(as<INTEGER>());
                case FLOATING: return std::to_wstring(as<FLOATING>());
                case NONE:
                default:
                    return {};
            }
        }

        eval_value add(const eval_value& n) const {
            switch (index()) {
                case STRING:
                    return n.add(as<STRING>());
                case INTEGER:
                    return n.add(as<INTEGER>());
                case FLOATING:
                    return n.add(as<FLOATING>());
                case NONE:
                default:
                    return n;
            }
        }

        template<class T>
        requires(std::is_arithmetic_v<T>)
        static std::ustring repeat(const std::ustring& string, const T& n) {
            std::ustring out;
            for (size_t i = 0; i < n; i++)
                out+=string;
            return out;
        }
        template<class T>
        requires(std::is_arithmetic_v<T>)
        eval_value multiply(const T& n) const{
            switch (index()) {
                case STRING:
                    return repeat(as<STRING>(), n);
                case INTEGER:
                    return as<INTEGER>() * n;
                case FLOATING:
                    return as<FLOATING>() * n;
                case NONE:
                default: //return none
                    return std::monostate();
            }
        }
        eval_value multiply(const std::ustring& n) const{
            switch (index()) {
                case STRING:
                    return *this;
                case INTEGER:
                    return repeat(n, as<INTEGER>());
                case FLOATING:
                    return repeat(n, as<FLOATING>());
                case NONE:
                default: //return none
                    return std::monostate();
                    break;
            }
        }
        eval_value multiply(const eval_value& n) const{
            switch (index()) {
                case STRING:
                    return n.multiply(as<STRING>());
                case INTEGER:
                    return n.multiply(as<INTEGER>());
                case FLOATING:
                    return n.multiply(as<FLOATING>());
                case NONE:
                default: //return none
                    return std::monostate();
            }
        }


        template<class T>
        requires(std::is_arithmetic_v<T>)
        eval_value subtract(const T& n) const{
            switch (index()) {
                case STRING:{
                    auto str = as<STRING>();
                    return str.substr(0, str.size()-n);
                }
                case INTEGER:
                    return as<INTEGER>() - n;
                case FLOATING:
                    return as<FLOATING>() - n;
                case NONE:
                default: //return none
                    return - n;
            }
        }
        eval_value subtract(const std::ustring& n) const{
            switch (index()) {
                case STRING:
                    return *this;
                case INTEGER:
                    return n.substr(0, n.size()-as<INTEGER>());
                case FLOATING:
                    return n.substr(0, n.size()-as<FLOATING>());
                case NONE:
                default: //return none
                    return n;
                    break;
            }
        }
        eval_value subtract(const eval_value& n) const{
            switch (n.index()) {
                case STRING:
                    return subtract(n.as<STRING>());
                case INTEGER:
                    return subtract(n.as<INTEGER>());
                case FLOATING:
                    return subtract(n.as<FLOATING>());
                case NONE:
                default: //return none
                    return *this;
            }
        }


        template<typename T>
        inline eval_value operator*(const T& e)const{
            return multiply(e);
        }
        template<typename T>
        inline eval_value operator+(const T& e)const{
            return add(e);
        }

    };