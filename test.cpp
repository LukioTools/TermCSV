#include "headers/Getters/getters.hpp"
#include "headers/Function.hpp"
#include "headers/Getters/value.hpp"
#include "sources/Cell.hpp"
#include "sources/Sheet.hpp"
#include <iostream>
#include <span>
#include <tuple>
#include <variant>
#include <vector>


eval_value fn_add(Sheet &, std::span<eval_value> values) {
    if(values.empty()) return std::monostate();
    eval_value out = values.front();
    for (size_t i = 1; i < values.size(); i++)
        out = out + values[i];
    
    return out;
}

eval_value fn_multiply(Sheet &, std::span<eval_value> values) {
    if(values.empty()) return std::monostate();
    eval_value out = values.front();
    for (size_t i = 1; i < values.size(); i++)
        out = out * values[i];

    std::wcout << L"returning: " << out.to_string() << std::endl;
    return out;
}

int main(int argc, char const *argv[])
{
    std::ustring str = L"ADD(MULTIPLY(VALUE(6),VALUE(6)),VALUE(15),VALUE(17))";

    Sheet s;

    std::wcout << Function::create(str).eval(s).to_string() << std::endl;

    /*
    auto& c = s[0];
    auto& e = c[0];
    e.set(Function()).add(
        Getters::function::shared(Function().add(
            Getters::value::shared(6),
            Getters::value::shared(6)
        ).func(fn_multiply)),
        Getters::value::shared(15), 
        Getters::value::shared(17)
    ).func(fn_add);

    std::wcout << e.eval(s).to_string() << std::endl;

    std::ustring str(L"123 banana");
    std::wcout << cell_value::create(str).eval(s).to_string() << std::endl;
    */

    return 0;
}
