
#include "v3/lib/Core/Getters/Function.hpp"
#include <ios>
#include <iostream>
#include <ostream>
#include <span>
#include <sstream>
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
        if(sp.empty()) return std::vector<Eval>{std::monostate()};
        Eval out = sp.front();
        for(std::size_t i = 1; i < sp.size(); i++)
            out = out - sp[i];
        
        return std::vector<Eval>{out};
    };
    Getters::Function::functions[L"MULTIPLY"] = [](std::span<Eval> sp){
        if(sp.empty()) return std::vector<Eval>{};
        Eval out = sp.front();
        for(std::size_t i = 1; i < sp.size(); i++)
            out = out * sp[i];
        
        return std::vector<Eval>{out};
    };
    Getters::Function::functions[L"ABS"] = [](std::span<Eval> sp){
        std::vector<Eval> out;
        for(auto& e : sp) out.emplace_back(e.abs());
        
        return out;
    };

    Getters::Function::functions[L"HEX"] = [](std::span<Eval> sp){
        std::vector<Eval> out;
        for(auto& e : sp)try{
            if (e.index() == Eval::STRING) {
                out.emplace_back(Eval(std::stol(std::get<Eval::STRING>(e), 0, 16)));
            }
            else if (e.index() == Eval::INTEGER) {
                out.emplace_back((std::wostringstream() << L"0x" << std::hex << std::uppercase << std::get<Eval::INTEGER>(e)).str());           
            }
            else if(e.index() == Eval::FLOAT){
                out.emplace_back((std::wostringstream() << L"0x" << std::hexfloat << std::get<Eval::FLOAT>(e)).str());           
            }
            else{
                out.push_back(e);
            }
        }catch(...){out.push_back(e);}
        return out;
    };


    auto fn = Getters::Function::create(std::wstring(L"HEX(ADD(HEX(0xEAEDEA), 8))"));


    std::wcout << "fnptr: " << fn << std::endl;

    if(fn) std::wcout << fn->get(s) << std::endl;



    return 0;
}