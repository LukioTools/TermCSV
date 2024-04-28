
#include "v3/lib/Core/Getters/Function.hpp"
#include <iostream>
#include <ostream>
#include <string>
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
    auto fn = Getters::Function::create(std::wstring(L"ADD(1,2)"));


    std::wcout << fn << std::endl;

    if(fn)
        std::wcout << fn->get(s) << std::endl;;



    return 0;
}