#pragma once

#include "Getter.hpp"
#include <functional>
#include <memory>
#include <span>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>
#include "eval_value.hpp"

typedef std::function<eval_value(Sheet&, std::span<eval_value>)> Function_t;

class Function
{
private:
public:
    std::function<eval_value(Sheet&, std::span<eval_value>)> fn = [](Sheet& s, std::span<eval_value>){return std::monostate();};
    std::vector<std::shared_ptr<Getter>> getters;   //shall be empty
    
    eval_value eval(Sheet& s)const{
        std::vector<eval_value> args;
        for(auto& e : getters){
            if(!e) {args.emplace_back(std::monostate());continue;}
            auto v = e->get(s);
            for(auto& e : v){
                args.push_back(e);
            }
        }
        if(fn) return fn(s, args);
        return std::monostate();
    }
    template<class ...shared_ptr_Getters>
    requires(std::is_same_v<std::shared_ptr<Getter>, shared_ptr_Getters> &&...)
    Function& add(const shared_ptr_Getters& ...va){
        (getters.push_back(va), ...);
        return *this;
    }

    template<class ...shared_ptr_Getters>
    requires(std::is_same_v<std::shared_ptr<Getter>, shared_ptr_Getters> &&...)
    Function& set(const shared_ptr_Getters& ...va){
        getters.clear();
        (getters.push_back(va), ...);
        return *this;
    }

    Function& func(const std::function<eval_value(Sheet&, std::span<eval_value>)>& f){
        fn=f;
        return *this;
    }

    eval_value operator()(Sheet& s)const{
        return eval(s);
    }
    inline static Function create(const std::span<std::unicode>& view){
        return Function();
    }

    Function() {}
    ~Function() {}
};