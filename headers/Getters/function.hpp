#pragma once

#include "../Getter.hpp"
#include "../Function.hpp"
#include <memory>


namespace Getters
{
    struct function : public Getter
    {
        Function f;
        std::vector<eval_value> get(Sheet &s) override{
            return {f.eval(s)};
        };
        inline static std::unique_ptr<Getter> unique(Function f){
            return std::make_unique<function>(f);
        }
        inline static std::shared_ptr<Getter> shared(Function f){
            return std::make_shared<function>(f);
        }
        function(const Function& f = {}): f(f){}
    };
} // namespace Getters



