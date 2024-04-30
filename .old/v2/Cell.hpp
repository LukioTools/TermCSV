#pragma once



#include <memory>
#include <string>
#include <utility>
#include "Getter.hpp"
#include "Getters/Value.hpp"


class Cell : public std::shared_ptr<Getter>{
private:
public:

    inline static std::shared_ptr<Getter> none_value = std::make_shared<Getters::Value>(std::monostate());

    using std::shared_ptr<Getter>::operator=;
    using std::shared_ptr<Getter>::operator bool;
    using std::shared_ptr<Getter>::get;
    using std::shared_ptr<Getter>::owner_before;
    using std::shared_ptr<Getter>::reset;
    using std::shared_ptr<Getter>::operator->;
    using std::shared_ptr<Getter>::operator*;
    using std::shared_ptr<Getter>::use_count;
    using std::shared_ptr<Getter>::unique;
    using std::shared_ptr<Getter>::swap;

    std::wstring to_wstring(Sheet &s){
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


    Cell(const std::shared_ptr<Getter>& getter = none_value) : std::shared_ptr<Getter>(getter){}
    Cell(std::shared_ptr<Getter>&& getter) : std::shared_ptr<Getter>(std::move(getter)){}
    ~Cell(){}
};