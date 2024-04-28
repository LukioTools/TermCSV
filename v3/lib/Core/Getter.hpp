#pragma once

#include <vector>
#include "Eval.hpp"
#include "../SpreadSheet/Sheet.hpp"

class Getter{
private:
public:
    virtual std::vector<Eval> get(Sheet& sheet);

    Getter();
    virtual ~Getter();
};