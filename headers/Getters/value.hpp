#pragma once

#include "../Getter.hpp"
#include <memory>
#include <variant>

namespace Getters
{
    struct value : public Getter , public eval_value
    {
        std::vector<eval_value> get(Sheet &s) override{
            return {*this};
        }
        inline static std::unique_ptr<Getter> unique(const eval_value& ev){
            return std::make_unique<value>(ev);
        }
        inline static std::shared_ptr<Getter> shared(const eval_value& ev){
            return std::make_shared<value>(ev);
        }
        inline static std::shared_ptr<Getter> create(const std::span<const std::unicode> &span){
            return std::make_shared<value>(eval_value::create(span));
        }
        value(const eval_value& ev = std::monostate()) : eval_value(ev){}
    };
} // namespace Getters

