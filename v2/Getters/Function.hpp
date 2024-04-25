#pragma once

#include "Getter-ln.hpp"
#include <functional>
#include <memory>
#include <span>
#include <type_traits>
#include <variant>
#include <vector>



class Function : public Getter{
private:
public:
    using Type = std::function<Eval(Sheet& ,const std::span<const std::shared_ptr<Getter>> )>;
    std::vector<std::shared_ptr<Getter>> getters;
    Type function;

    std::vector<Eval> get(Sheet& s) override{
        if(!function) return {std::monostate()};
        return {function(s, getters)};
    }

    Function& fn(const Type& i){
        function = i;
        return *this;
    }
    Function& fn(Type&& i){
        function = i;
        return *this;
    }

    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& add(const va& ...copy){
        (getters.push_back(copy), ...);
        return *this;
    }
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& add(va&& ...move){
        (getters.emplace_back(std::move(move)), ...);
        return *this;
    }
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& set(const va& ...copy){
        getters.clear();
        (getters.push_back(copy), ...);
        return *this;
    }
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& set(va&& ...move){
        getters.clear();
        (getters.emplace_back(move), ...);
        return *this;
    }




    Function(){}
    ~Function(){}

};