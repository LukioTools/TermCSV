#pragma once

#include "../Getter.hpp"
#include <algorithm>
#include <memory>
#include <variant>

namespace Getters
{
    struct value : public Getter
    {
        eval_value v;
        std::vector<eval_value> get(Sheet &s) override{
            return {v};
        }
        inline static std::unique_ptr<Getter> unique(const eval_value& ev){
            return std::make_unique<value>(ev);
        }
        inline static std::shared_ptr<Getter> shared(const eval_value& ev){
            return std::make_shared<value>(ev);
        }

        value(const eval_value& ev = std::monostate()) : v(ev){}
    };
} // namespace Getters
