#include "headers/Filter.hpp"
#include "headers/Getters/cell_range.hpp"
#include "headers/Getters/getters.hpp"
#include "headers/Function.hpp"
#include "headers/Getters/value.hpp"
#include "headers/eval_value.hpp"
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
    Sheet s;

    for (size_t x = 0; x < 100; x++)
        for (size_t y = 0; y < 100; y++)
        s[x][y].set(long(x*y+x));

    //std::wcout << Function::create(str).eval(s).to_string() << std::endl;

    std::ustring pvs = L"003451";
    std::wcout << pvs << L": " << std::flush;
    for(auto& e : Getters::value::create(pvs)->get(s)){
        std::wcout << e.to_string() << std::endl;
    };

    std::span span = pvs;
    span = span.subspan(span.size());
    std::wcout << L"span: " << std::ustring(span.begin(), span.end()) << std::endl; 

    std::ustring c = L"0:0->"; //select every cell plausable
    std::wcout << L"range: " << c << L" (aka every cell that exists)"<<std::endl;
    std::wcout << L"selected cell values: " << std::endl;
    Filter f;

    f.add(Getters::cell_range::create(c))
    .func([](Sheet&, eval_value& ev){
        if(ev.index() == eval_value::INTEGER && ev.as<eval_value::INTEGER>()%2 == 1) return true; 
        return false;
    });
    
    for(auto& e :  f.eval(s)){
        std::wcout << e.to_string() << std::endl;
    }

    return 0;
}
