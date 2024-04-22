#pragma once

#include "Getter.hpp"
#include "Sheet.hpp"
#include "eval_value.hpp"
#include <functional>
#include <map>
#include <memory>
#include <span>
#include <variant>
#include <vector>

    //can be also used as a transformer
typedef std::function<bool(Sheet&, eval_value&)> Filter_t;


//TODO: parse from text
//function is evaluated for each member
//each member may be mutated
class Filter : public Getter
{
private:
public:
    Filter_t filter;
    std::vector<std::shared_ptr<Getter>> getters;
    inline static std::map<std::ustring, Filter_t> filters;

        //same as get
    inline std::vector<eval_value> eval(Sheet& s) const{
        if(!filter) return {std::monostate()}; 
        std::vector<eval_value> out;

        for(auto& e : getters){
            if(!e) {out.emplace_back(std::monostate());continue;}
            for(auto& e : e->get(s)) if(filter(s,e)) out.push_back(e);
        }

        return out;
    }

    std::vector<eval_value> get(Sheet& s) override{
        return eval(s);
    }

    template<class ...shared_ptr_Getters>
    requires(std::is_same_v<std::shared_ptr<Getter>, shared_ptr_Getters> &&...)
    Filter& add(const shared_ptr_Getters& ...va){
        (getters.push_back(va), ...);
        return *this;
    }

    template<class ...shared_ptr_Getters>
    requires(std::is_same_v<std::shared_ptr<Getter>, shared_ptr_Getters> &&...)
    Filter& set(const shared_ptr_Getters& ...va){
        getters.clear();
        (getters.push_back(va), ...);
        return *this;
    }

    Filter& func(const Filter_t& f){
        filter=f;
        return *this;
    }

    inline auto operator()(Sheet& s)const{
        return eval(s);
    }



    //do the parse
 


    Filter(/* args */) {}
    ~Filter() {}
};