#pragma once
#include <functional>
#include <span>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include "Cell.hpp"
#include "Sheet.hpp"
#include "../../Term3D/Unicode/Unicode.hpp"

class Equation{
private:
public:
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
        }    public:

        template<class T>
        requires(std::is_arithmetic_v<T>)
        eval_value add(T n) const {
            switch (index()) {
                case STRING:
                    return as<STRING>() + std::to_wstring(n);
                    break;
                case INTEGER:
                    return as<INTEGER>() + n;
                    break;
                case FLOATING:
                    return as<FLOATING>()+n;
                    break;
                case NONE:
                default:
                    return n;
                    break;
            }
        }

        eval_value add(const std::ustring& n) const {
            return n + to_string();
        }

        std::ustring to_string() const {
            switch (index()) {
                case STRING:
                    return as<STRING>();
                    break;
                case INTEGER:
                    return std::to_wstring(as<INTEGER>());
                    break;
                case FLOATING:
                    return std::to_wstring(as<FLOATING>());
                    break;
                case NONE:
                default:
                    return {};
                    break;
            }
        }

        eval_value add(const eval_value& n) const {
            switch (index()) {
                case STRING:
                    return n.add(as<STRING>());
                    break;
                case INTEGER:
                    return n.add(as<INTEGER>());
                    break;
                case FLOATING:
                    return n.add(as<FLOATING>());
                    break;
                case NONE:
                default:
                    return n;
                    break;
            }
        }
        template<class T>
        requires(std::is_arithmetic_v<T>)
        eval_value multiply(const T& n) const{
            switch (index()) {
                case STRING:
                    return std::ustring(as<STRING>(), n);
                    break;
                case INTEGER:
                    return as<INTEGER>() + n;
                    break;
                case FLOATING:
                    return as<FLOATING>()+n;
                    break;
                case NONE:
                default:
                    return n;
                    break;
            }
        }


    };

    struct Function
    {
        std::function<eval_value(Sheet&, std::span<cell_value>)> fn;
        std::vector<std::span<cell_value>> arguments;
    };
    
    //functions
    static eval_value multiply(Sheet&, std::span<cell_value> cv);
    static eval_value add(Sheet&, std::span<cell_value> cv);
    static eval_value divide(Sheet&, std::span<cell_value> cv);


    std::vector<Function> cv;
    eval_value eval(Sheet&) const;
    Equation(/* args */) {}
    ~Equation() {}
};

