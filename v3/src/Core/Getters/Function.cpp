#include "../../../lib/Core/Getters/Function.hpp"
#include "../../../lib/Core/Parser/Parse.hpp"

namespace Getters {


    bool Function::is_function(const std::span<const wchar_t> span){
        return std::regex_match(span.begin(), span.end(), is_function_regex);
    }

    std::shared_ptr<Function> Function::create(const std::span<const wchar_t>& sp){
        auto o = split_function(sp);

        if(!o){
            std::wclog << L"o was null"  << std::endl;
            std::clog << "o was null"  << std::endl;
            return nullptr;
        }
        auto f = *o;
        auto fnptr = functions[std::wstring_view(f.fn.begin(), f.fn.end())];
        if(!fnptr){
            std::wclog << L"no fnpotr" << std::endl;
            std::clog << "no fnpotr" << std::endl;
            return nullptr;
        }

        return std::make_shared<Function>(
            fnptr,
            parse(f.args)
        );
    }

    std::vector<Eval> Function::get(Sheet& s){
        if(!function) return {std::monostate()};
        std::vector<Eval> ev;
        for (auto& gt : getters) {
            if(!gt) continue;
            for(auto& e : gt->get(s)){
                ev.emplace_back(e);
            }
        }
        return function(ev);
    }



    Function& Function::fn(const Type& i){
        function = i;
        return *this;
    }
    Function& Function::fn(Type&& i){
        function = i;
        return *this;
    }

    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& Function::add(const va& ...copy){
        (getters.push_back(copy), ...);
        return *this;
    }
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& Function::add(va&& ...move){
        (getters.emplace_back(std::move(move)), ...);
        return *this;
    }
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& Function::set(const va& ...copy){
        getters.clear();
        (getters.push_back(copy), ...);
        return *this;
    }
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& Function::set(va&& ...move){
        getters.clear();
        (getters.emplace_back(move), ...);
        return *this;
    }




    Function::Function(){}
    Function::Function(const Type& fn, const std::vector<std::shared_ptr<Getter>>& v): getters(v), function(fn){}
    Function::Function(const Type& fn, std::vector<std::shared_ptr<Getter>>&& v): getters(std::move(v)), function(fn){}
    Function::~Function(){}

};
