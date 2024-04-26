#include "v2/Eval.hpp"
#include "v2/Getters.hpp"
#include "v2/Getters/CellRange.hpp"
#include "v2/Getters/Function.hpp"
#include "v2/Getters/Value.hpp"
#include "v2/Parse.hpp"
#include <glm/detail/qualifier.hpp>
#include <glm/fwd.hpp>
#include <iostream>
#include <memory>
#include <ostream>
#include <span>
#include <string>
#include <variant>
#include <vector>



Eval func(const std::span<const Eval> vals){

    Eval out = 0;
    for(auto& e : vals){
        out = out + e;
    }
    return out;
}

std::wostream& operator<<(std::wostream& os, const std::vector<Eval>& v){
    os << L'{';
    for(std::size_t i = 0; i < v.size();){
        os << v[i].to_wstring();
        i++;
        if(i != v.size()) os<<L", ";
    }
    os << L'}';
    return os;
}

std::wostream& operator<<(std::wostream& os, const std::vector<std::span<wchar_t>>& v){
    os << L'{';
    for(std::size_t i = 0; i < v.size();){
        os << v[i].size() << ':';
        os << '\'' << std::wstring(v[i].begin(), v[i].end()) << '\'';
        i++;
        if(i != v.size()) os<<L", ";
    }
    os << L'}';
    return os;
}

template<glm::length_t L, typename T>
std::wostream& operator<<(std::wostream& os, const glm::vec<L,T>& v){
    os << L'[';
    for(std::size_t i = 0; i < L;){
        os << v[i];
        i++;
        if(i != L) os<<L", ";
    }
    os << L']';
    return os;
}


int main(int argc, const char* argv[]){

    Sheet s;

    for(long x = 0; x < 10; x++)
        for(long y = 0; y < 10; y++){
        s[x][y] = Getters::Value::shared(x*y+x+y);
    }
        
    /*
    
    std::wclog << "s.size(): " << s.size() << std::endl;

    auto single = CellRange::create(std::wstring(L"3:5"));
    auto row = CellRange::create(std::wstring(L"3:5->:5"));
    auto column = CellRange::create(std::wstring(L"3:5->3:"));
    auto all = CellRange::create(std::wstring(L"0:0->"));

    std::wclog << L"single " << std::wstring(L"3:5") << ": " << *single << ": "  << single->get(s) << std::endl;
    std::wclog << L"row " << std::wstring(L"3:5->:5") << ": " << *row << ": "  << row->get(s) << std::endl;
    std::wclog << L"column " << std::wstring(L"3:5->3:") << ": " << *column << ": "  << column->get(s) << std::endl;
    std::wclog << L"all " << std::wstring(L"0:0->") << ": " << *all << ": "  << all->get(s) << std::endl;

    */

    auto str = std::wstring(L"Hello World, FUNCTION(1, ADD(1,3), WORLD), 3:5, 3:5->");
    std::wcout << parse_terms(str) << std::endl;
    
    //std::wstring str = L"  Hello World  ";
    //std::span<wchar_t> span = trim(str);

    //std::wcout << std::wstring(span.begin(), span.end()) << std::endl;



    return 0;
}