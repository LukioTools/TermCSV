#pragma once
#include <vector>
#include "Sheet.hpp"
#include "eval_value.hpp"


class Getter
{
private:
public:
    virtual std::vector<eval_value> get(Sheet& s){return {};}
    std::vector<eval_value> operator()(Sheet& s){
        return get(s);
    }
    virtual ~Getter() {}
};