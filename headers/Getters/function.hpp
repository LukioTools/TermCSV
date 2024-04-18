#pragma once

#include "../Getter.hpp"
#include "../Function.hpp"
#include <memory>


namespace Getters
{
    struct function_getter : public Getter, public ::Function
    {
        std::vector<eval_value> get(Sheet &s) override{
            return {eval(s)};
        };
        inline static std::unique_ptr<Getter> unique(const Function& f){
            return std::make_unique<function_getter>(f);
        }
        inline static std::shared_ptr<Getter> shared(const Function& f){
            return std::make_shared<function_getter>(f);
        }

        inline static std::unique_ptr<Getter> unique(Function&& move){
            return std::make_unique<function_getter>(move);
        }
        inline static std::shared_ptr<Getter> shared(Function&& move){
            return std::make_shared<function_getter>(move);
        }


        function_getter() = default;
        ~function_getter() = default;
        function_getter(const ::Function& copy) : ::Function(copy) {}
        function_getter(::Function&& move) : ::Function(move) {}

    };
} // namespace Getters



