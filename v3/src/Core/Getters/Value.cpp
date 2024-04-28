#include <memory>
#include <span>
#include <utility>
#include "../../../lib/Core/Getters/Value.hpp"

namespace Getters {
    std::vector<Eval> Value::get(Sheet&){return {*this};}
    
    Eval& Value::value(){return *this;}


    //redo this  
    std::shared_ptr<Value> Value::create(const std::span<const wchar_t> sp){return std::make_shared<Value>(std::wstring(sp.begin(), sp.end()));}


    template<class T>
    Value::Value(const T& e) : Eval(e){};
    template<class T>
    Value::Value(T&& e) : Eval(std::move(e)){};
    Value::Value(const Eval& ev): Eval(ev) {};
    Value::Value(Eval&& ev): Eval(std::move(ev)) {};
    Value::~Value(){}
}