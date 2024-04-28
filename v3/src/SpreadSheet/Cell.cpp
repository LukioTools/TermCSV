#include <memory>
#include <string>
#include <utility>
#include <variant>
#include "../../lib/SpreadSheet/Cell.hpp"
#include "../../lib/Core/Getters/Value.hpp"
#include "../../lib/Core/Getter.hpp"


std::shared_ptr<Getter> Cell::none_value = std::make_shared<Getters::Value>(Eval(std::monostate()));

std::wstring Cell::to_wstring(Sheet &s){
    auto v = get()->get(s);
    if(v.empty()) return {};
    if(v.size() == 1){
        return v.back().to_wstring();
    }
    std::wstring out = L"{";
    for(std::size_t i = 0; i < v.size();){
        out+=v[i].to_wstring();
        i++;
        if(i == v.size()) out+=L"}";
        else out+=L", ";
    }
    return out;
}


Cell::Cell(const std::shared_ptr<Getter>& getter) : std::shared_ptr<Getter>(getter){}
Cell::Cell(std::shared_ptr<Getter>&& getter) : std::shared_ptr<Getter>(std::move(getter)){}
Cell::~Cell(){}
