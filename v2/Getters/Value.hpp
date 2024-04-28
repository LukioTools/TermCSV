#pragma  once
#include "Getter-ln.hpp"
#include "../Eval.hpp"
#include <memory>
#include <span>
#include <string>
#include <variant>

namespace Getters {
    class Value : public Getter, public Eval{
    private:
    public:
        using Eval::operator=;
        using Eval::emplace;
        using Eval::index;
        using Eval::swap;
        using Eval::valueless_by_exception;
        std::vector<Eval> get(Sheet&) override{
            return {*this};
        }
        Eval& value(){
            return *this;
        }

        inline static std::shared_ptr<Value> create(const std::span<const wchar_t> sp){
            return std::make_shared<Value>(std::wstring(sp.begin(), sp.end()));
        }

        template<class ...Va>
        inline static std::shared_ptr<Getter> shared(Va...a){
            return std::make_shared<Value>(a...);
        }

        template<class T>
        Value(const T& e) : Eval(e){};
        template<class T>
        Value(T&& e) : Eval(std::move(e)){};

        Value(const Eval& ev): Eval(ev) {}
        Value(Eval&& ev = std::monostate()): Eval(ev) {}
        ~Value(){}
    };
}