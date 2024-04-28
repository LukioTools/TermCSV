
#include "v3/lib/Core/Getters/Function.hpp"
#include <iostream>
#include <ostream>
#include <span>
#include <string>
#include <variant>
#include <vector>


std::wostream& operator<<(std::wostream& os, const std::vector<Eval>& ev){
    os << L"{ ";
    for(std::size_t i = 0; i < ev.size(); i++){
        os << ev[i].to_wstring();
        if(i+1 != ev.size()) os << L", ";
    }
    os << L" }";
    return os;
}



int main(int argc, const char* argv[]){


    Sheet s;



    Getters::Function::functions[L"ADD"] = [](std::span<Eval> sp){
        Eval out = std::monostate();
        for(auto& e : sp) out = out + e;
        
        return std::vector<Eval>{out};
    };
    Getters::Function::functions[L"SUB"] = [](std::span<Eval> sp){
        Eval out = std::monostate();
        for(auto& e : sp) out = out - e;
        
        return std::vector<Eval>{out};
    };
    Getters::Function::functions[L"MULTIPLY"] = [](std::span<Eval> sp){
        if(sp.empty()) return std::vector<Eval>{};
        Eval out = sp.front();
        for(std::size_t i = 1; i < sp.size(); i++)
            out = out * sp[i];
        
        return std::vector<Eval>{out};
    };


    auto fn = Getters::Function::create(std::wstring(L"SUB(1,-6)")); // repeat " XD" ((1+2)*5-> 15) times


    std::wcout << fn << std::endl;

    if(fn)
        std::wcout << fn->get(s) << std::endl;



    return 0;
}