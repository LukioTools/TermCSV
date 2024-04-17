#include "headers/Getters/value.hpp"
#include "headers/Function.hpp"
#include "sources/Cell.hpp"
#include "sources/Sheet.hpp"
#include <iostream>
#include <span>
#include <tuple>
#include <variant>
#include <vector>

eval_value fn(Sheet &, std::span<eval_value> values) {
    eval_value out = 0L;
    for(auto& e : values){
        out = out + e;
    }
    return out;
}
int main(int argc, char const *argv[])
{
    Sheet s;

    auto& c = s[0];
    auto& e = c[0];
    e.set(Function()).add(
        Getters::value::shared(15), 
        Getters::value::shared(17)
    ).func(fn);


    std::wcout << e.eval(s).to_string() << std::endl;
    return 0;
}
