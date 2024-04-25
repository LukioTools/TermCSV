#include "v2/Eval.hpp"
#include "v2/Getters/Value.hpp"
#include "v2/Getters/Function.hpp"
#include "v2/Getters/CellRange.hpp"
#include <iostream>
#include <span>
#include <variant>
#include <vector>



Eval func(const std::span<const Eval> vals){

    Eval out = 0;
    for(auto& e : vals){
        out = out + e;
    }
    return out;
}

int main(int argc, const char* argv[]){

    Sheet s;
    Getters::Value v = L"1VALTHING ";
    Getters::Value v2 = 2;

    std::wcout << v.value().to_wstring() << std::endl;
    std::wcout << v2.value().to_wstring() << std::endl;

    std::wcout << (v+v2).to_wstring() << std::endl; 



    return 0;
}