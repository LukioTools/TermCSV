#pragma once

#include "Getter-ln.hpp"
#include <functional>
#include <memory>
#include <regex>
#include <span>
#include <type_traits>
#include <variant>
#include <vector>


namespace Getters {

class Function : public Getter{
private:
public:
    using Type = std::function<std::vector<Eval>(std::span<Eval>)>;
    std::vector<std::shared_ptr<Getter>> getters;
    Type function;

    static inline std::wregex is_function_regex = std::wregex(L"^.*?\\(.*\\)$");

    inline static bool is_function(const std::span<const wchar_t> span){
        return std::regex_match(span.begin(), span.end(), is_function_regex);
    }

    std::vector<Eval> get(Sheet& s) override{
        if(!function) return {std::monostate()};
        std::vector<Eval> ev;
        for (auto& gt : getters) {
            if(!gt) continue;
            for(auto& e : gt->get(s)){
                ev.emplace_back(e);
            }
        }
        return function(ev);
    }

    template<class ...Va>
    requires(std::is_same_v<Va, std::shared_ptr<Getter>> &&...)
    inline static std::shared_ptr<Getter> shared(const Type& fn, const Va& ...args){
        return  std::make_shared<Function>(fn, std::vector<std::shared_ptr<Getter>>{args...});
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
    Function(const Type& fn, const std::vector<std::shared_ptr<Getter>> v): getters(v), function(fn){}
    ~Function(){}

};
}