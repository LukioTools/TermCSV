#include "v2/Eval.hpp"
#include "v2/Getters/Value.hpp"
#include "v2/Getters/Function.hpp"
#include "v2/Getters/CellRange.hpp"
#include <iostream>
#include <variant>
int main(int argc, const char* argv[]){

    Sheet s;
    Getters::Value v;
    std::wcout << v.value().to_wstring() << std::endl;


    return 0;
}