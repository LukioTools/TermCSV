#pragma  once
#include "../Getter.hpp"
#include "../Eval.hpp"
#include <memory>
#include <span>
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
        std::vector<Eval> get(Sheet&) override;
        Eval& value();

        
        static std::shared_ptr<Value> create(const std::span<const wchar_t> sp);

        template<class T>
        Value(const T& e);
        template<class T>
        Value(T&& e);

        Value(const Eval& ev);
        Value(Eval&& ev = std::monostate());
        ~Value();
    };
}