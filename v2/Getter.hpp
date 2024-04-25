#pragma once

#include <vector>
#include "Eval.hpp"
#include "head/Sheet.hpp"

class Getter{
private:
public:
    virtual std::vector<Eval> get(Sheet& sheet){return {};}

    Getter(){}
    virtual ~Getter(){}
};