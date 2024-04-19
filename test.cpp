#include "headers/Getters/cell_range.hpp"
#include "headers/Getters/getters.hpp"
#include "headers/Function.hpp"
#include "headers/Getters/value.hpp"
#include "sources/Cell.hpp"
#include "sources/Sheet.hpp"
#include "sources/Function.hpp"
#include <iostream>
#include <memory>
#include <ostream>
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

    s[0][0].set(69L);

    //std::wcout << Function::create(str).eval(s).to_string() << std::endl;

    std::ustring pvs = L"003451";
    std::wcout << pvs << L": " << std::flush;
    for(auto& e : Function::parse_value(pvs)->get(s)){
        std::wcout << e.to_string() << std::endl;
    };

    std::ustring c = L"0:0->"; //select every cell plausable
    std::wcout << L"range: " << c << L" (aka every cell that exists)"<<std::endl;
    std::wcout << L"selected cell values: " << std::endl;
    for(auto& e : Function::parse_cell_range(c)->get(s)){
        std::wcout << e.to_string() << std::endl;
    }

    return 0;
}
