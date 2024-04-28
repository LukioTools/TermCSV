#include <memory>
#include <regex>
#include <span>
#include <string>
#include <utility>
#include "../../../lib/Core/Getters/Value.hpp"

namespace Getters {
    std::vector<Eval> Value::get(Sheet&){return {*this};}
    
    Eval& Value::value(){return *this;}

    //redo this  
    std::shared_ptr<Value> Value::create(const std::span<const wchar_t> sp) try{
        static std::wregex is_int = std::wregex(L"^-?\\d+$");
        static std::wregex is_float = std::wregex(L"^-?\\d*(\\.|,)\\d*$");
        auto str = std::wstring(sp.begin(), sp.end());
        if(std::regex_match(str, is_int)) return std::make_shared<Value>(std::stol(str));
        if(std::regex_match(str, is_float)) return std::make_shared<Value>(std::stod(str));
        return std::make_shared<Value>(str);
    }catch(...){
        return std::make_shared<Value>(std::wstring(sp.begin(), sp.end()));
    }


    template<class T>
    Value::Value(const T& e) : Eval(e){};
    template<class T>
    Value::Value(T&& e) : Eval(std::move(e)){};
    Value::Value(const Eval& ev): Eval(ev) {};
    Value::Value(Eval&& ev): Eval(std::move(ev)) {};
    Value::~Value(){}
}