#pragma once

#include "Cell.hpp"
#include "Getter.hpp"
#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <span>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
#include "Getters/value.hpp"
#include "eval_value.hpp"

typedef std::function<eval_value(Sheet&, std::span<eval_value>)> Function_t;

class Function
{
private:
public:
    std::function<eval_value(Sheet&, std::span<eval_value>)> fn = [](Sheet& s, std::span<eval_value>){return std::monostate();};
    std::vector<std::shared_ptr<Getter>> getters;   //shall be empty
    
    eval_value eval(Sheet& s)const{
        std::vector<eval_value> args;
        for(auto& e : getters){
            if(!e) {args.emplace_back(std::monostate());continue;}
            auto v = e->get(s);
            for(auto& e : v){
                args.push_back(e);
            }
        }
        if(fn) return fn(s, args);
        return std::monostate();
    }
    template<class ...shared_ptr_Getters>
    requires(std::is_same_v<std::shared_ptr<Getter>, shared_ptr_Getters> &&...)
    Function& add(const shared_ptr_Getters& ...va){
        (getters.push_back(va), ...);
        return *this;
    }

    template<class ...shared_ptr_Getters>
    requires(std::is_same_v<std::shared_ptr<Getter>, shared_ptr_Getters> &&...)
    Function& set(const shared_ptr_Getters& ...va){
        getters.clear();
        (getters.push_back(va), ...);
        return *this;
    }

    Function& func(const std::function<eval_value(Sheet&, std::span<eval_value>)>& f){
        fn=f;
        return *this;
    }

    eval_value operator()(Sheet& s)const{
        return eval(s);
    }


private:

    inline static std::vector<std::span<std::unicode>> parse_terms(const std::span<std::unicode>& view){
        std::vector<std::span<std::unicode>> out;
        long depth = 0;
        size_t pos = 0;
        for (size_t i = 0; i < view.size(); i++)
        {
            if(view[i] == '(')
                depth++;
            else if(view[i] == ')')
                depth--;
            else if(!depth && view[i] == ','){
                out.push_back(view.subspan(pos, i-pos));
                pos = i+1;
            }
        }
        if(pos+1 < view.size())
            out.push_back(view.subspan(pos));
        return out;        
    }

    inline static std::pair<std::span<std::unicode>, std::span<std::unicode>> parse_func(const std::span<std::unicode>& view){
        std::unicode ch = '(';
        auto inside_begin = std::find_first_of(view.begin(), view.end(), &ch, (&ch)+1);
        if(inside_begin == view.end()) return {view, {}}; 
        return {{view.begin(), inside_begin}, {inside_begin+1, view.end()-1}};
    }


    inline static std::span<std::unicode> func_name(const std::span<std::unicode>& view){
        for (size_t i = 0; i < view.size(); i++)
            if(view[i] == '(')
                return view.subspan(0, i);
        return view;        
    }


    inline static std::vector<std::shared_ptr<Getter>> recursive(Function fn, std::span<std::unicode> view){

        return {};
    }
    inline static Function_t find(std::span<std::unicode> fname){
        for(auto& e : parsers){
            if(e.fname.size() != fname.size()) continue;
            bool cont = false;
            for (size_t i = 0; i < fname.size(); i++)
            {
                if(e.fname[i] != fname[i]){
                    cont = true;
                    break;
                };
            }
            if(cont) continue;
            return e.fn;
        }
        return nullptr;
    }

    std::shared_ptr<Getter> parse_value(std::span<std::unicode> args){
        return Getters::value::shared(eval_value::create(args));
    }

        //figure out parsing and other shit
    std::shared_ptr<Getter> parse_cell_range(std::span<std::unicode> args){
        //ait so pares %d:%d->d%:d%
        return nullptr;
        //return Getters::cell_range::shared({},{});
    }
public:
    inline static Function create(const std::span<std::unicode>& view){
        Function fn;
        std::wcout << L"input string: " << std::ustring(view.begin(), view.end()) << std::endl;
        auto func = parse_func(view);
        std::wcout << L"func name: " << std::ustring(func.first.begin(), func.first.end()) << std::endl;
        std::wcout << L"func ptr found: " <<  (bool)find(func.first) << std::endl;

        std::wcout << L"func args: " << std::ustring(func.second.begin(), func.second.end()) << std::endl;
        auto terms = parse_terms(func.second);
        std::wcout << L"terms: " << terms.size() << std::endl;
        for(auto& e : terms){
            std::wcout << std::ustring(e.begin(), e.end()) << std::endl;
        }
        return fn;
    }

    Function() {}
    ~Function() {}

    struct FunctionParser
    {
        Function_t fn;
        std::ustring fname;
        std::shared_ptr<Getter>(*create)(std::span<std::unicode const> args) = nullptr;
    };

    inline static std::map<std::ustring, std::function<std::shared_ptr<Getter>(std::span<std::unicode const>)>> parsers;
};