#pragma once

#include "Equation.hpp"
#include "Getter.hpp"
#include <functional>
#include <memory>
#include <span>
#include <variant>
#include <vector>
#include "eval_value.hpp"

class Function
{
private:
public:
    std::function<eval_value(std::span<eval_value>)> fn;
    std::vector<std::shared_ptr<Getter>> getters;
    eval_value eval(Sheet& s){
        std::vector<eval_value> args;
        for(auto& e : getters){
            if(!e) {args.emplace_back(std::monostate());continue;}
            auto v = e->get(s);
            for(auto& e : v){
                args.push_back(e);
            }
        }
        if(fn)
            return fn(args);
        return std::monostate();
    }
    Function() {}
    ~Function() {}
};