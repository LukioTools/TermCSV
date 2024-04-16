#pragma once
#include <functional>
#include <span>
#include "Cell.hpp"
#include "Sheet.hpp"

class Equation{
private:
public:
    //functions
    static cell_value multiply(Sheet&, std::span<cell_value> cv);

    std::vector<std::function<cell_value(Sheet&, std::span<cell_value>)>> cv;
    cell_value eval(Sheet&);
    Equation(/* args */) {}
    ~Equation() {}
};

