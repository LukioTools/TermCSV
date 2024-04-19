#pragma once

#include "Cell.hpp"
#include "Getter.hpp"
#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
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
    Function_t fn = [](Sheet& s, std::span<eval_value>){return std::monostate();};
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

    Function& func(const Function_t& f){
        fn=f;
        return *this;
    }

    eval_value operator()(Sheet& s)const{
        return eval(s);
    }

    enum term_type{
        UNKNOWN,
        VALUE,
        CELL_SPAN,
        FUNCTION,
    };
    inline static term_type identify_term(const std::span<const std::unicode> span){
        if(span.empty()) return UNKNOWN;
        static const std::wregex is_span(L"^!?\\d+:!?\\d+->!?\\d+:!?\\d+$");
        static const std::wregex is_fn(L"^\\w+\\(.*\\)$");
        if(std::regex_match(span.begin(), span.end(), is_span)) return CELL_SPAN;
        if(std::regex_match(span.begin(), span.end(), is_fn)) return FUNCTION;
        return VALUE;   //its the problem of the value constructor to determine what kind of value it is
    }

    inline static std::shared_ptr<Getter> parse_term(const std::span<const std::unicode>& view);
    inline static std::vector<std::span<std::unicode const>> parse_terms(const std::span<const std::unicode>& view){
        std::vector<std::span<std::unicode const>> out;
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
    inline static std::pair<std::span<std::unicode const>, std::span<std::unicode const>> parse_func(const std::span<const std::unicode>& view){
        std::unicode ch = '(';
        auto inside_begin = std::find_first_of(view.begin(), view.end(), &ch, (&ch)+1);
        if(inside_begin == view.end()) return {view, {}}; 
        return {{view.begin(), inside_begin}, {inside_begin+1, view.end()-1}};
    }
    inline static std::ustring to_string(const std::span<std::unicode const> span){
        return std::ustring(span.begin(), span.end());
    }
    

    inline static std::shared_ptr<Getter> parse_value(const std::span<const std::unicode>& args);
    /*
    {
        return Getters::value::shared(eval_value::create(args));
    }
    */
        //figure out parsing and other shit
    inline static std::shared_ptr<Getter> parse_cell_range(const std::span<const std::unicode>& args);
    /*
    {
        //ait so pares %d:%d->d%:d%
        return nullptr;
        //return Getters::cell_range::shared({},{});
    }
    */

    inline static std::shared_ptr<Getter> parse_function(const std::span<const std::unicode>& args);
        /*
        {
            Function fn;
            return Getters::function_getter::shared(fn);
        }
        */

public:
    inline static Function create(const std::span<std::unicode>& view){
        Function fn;
        return fn;
    }

    Function() = default;
    ~Function() = default;
    Function(const Function& copy):fn(copy.fn), getters(copy.getters){};
    Function(Function&& move): fn(std::move(move.fn)), getters(std::move(move.getters)){};

    inline static std::map<std::ustring, Function_t> parsers;
};