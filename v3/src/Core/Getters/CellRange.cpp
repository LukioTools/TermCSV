#include <cstddef>
#include <cstdlib>
#include <cwchar>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <ostream>
#include <regex>
#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include "../../../lib/Core/Getters/CellRange.hpp"


namespace Getters {

    std::wstring CellRange::component = L":";
    std::wstring CellRange::range = L"->";
    std::wregex CellRange::is_range_regex = std::wregex(L"^!?\\d+:!?\\d+(->!?\\d*:?!?\\d*)?$");
    wchar_t CellRange::constant = L'!';

    bool CellRange::is_cellrange(const std::span<wchar_t const> sp){
        return std::regex_match(sp.begin(), sp.end(), is_range_regex);
    }
    std::shared_ptr<CellRange> CellRange::create(const std::span<wchar_t const> sp){
        auto sr = std::make_shared<CellRange>();
        auto& r = *sr;

        auto sw = std::wstring_view(sp.begin(), sp.end());
        auto sep = sw.find(range);

        r.begin = parse_comp(sp.subspan(0, sep), &r.constants[0]);
        if(sep == std::variant_npos){
            r.end = r.begin;
            return sr;
        };

        r.end = parse_comp(sp.subspan(sep+range.size()), &r.constants[2]);
        return sr;
    }

    glm::uvec2 CellRange::parse_comp(const std::span<wchar_t const> sp, bool cst[])try {//parse x,y
        glm::uvec2 out = invalid;
        if (sp.empty()) {return out;}

        auto sw = std::wstring_view(sp.begin(), sp.end());
        auto sep = sw.find(component);

        if(sep == std::variant_npos) return out;

        auto xs = sp.subspan(0, sep);
        auto ys = sp.subspan(sep+component.size());

        cst[0] = parse_const(xs);
        cst[1] = parse_const(ys);

        out.x = parse_num(std::wstring(xs.begin(), xs.end()));
        out.y = parse_num(std::wstring(ys.begin(), ys.end()));
        return out;
    }catch (...) {return invalid;}
    uint CellRange::parse_num(const std::wstring& sp)try{
        if(sp.empty()) return -1;
        return std::stoi(sp);
    }catch (...) {return -1;}


    bool CellRange::parse_const(std::span<wchar_t const>& sp)try {
        if(!sp.empty() && sp.front() == constant){
            sp = sp.subspan(1);
            return true;
        }
        return false;
    }catch(...) {return false;}

    std::vector<Eval> CellRange::get(Sheet& s){
        if(!valid()) return {};
        std::vector<Eval> out;
        for(std::size_t x = begin.x; x <= end.x && x < s.size(); x++){
            auto& e = s[x];
            for(std::size_t y = begin.y; y <= end.y && y < e.size(); y++){
                auto v = e[y];
                if(v)
                for(auto& e : v->get(s)){
                    out.emplace_back(std::move(e));
                };
            }
        }


        return out;
    }


    bool CellRange::valid() const{
        if(begin.x > end.x || begin.y > end.y) return false;
        if(begin.x == -1U || begin.y == -1U) return false;

        return true;
    }

    std::ostream& operator<<(std::ostream& os, const CellRange& cr){
        os << "{valid: " << (cr.valid() ? "True, [": "False, [") <<  cr.begin.x << ", " << cr.begin.y << "]/[" << cr.end.x << ", " << cr.end.y << "]}";
        return os;
    }

    std::wostream& operator<<(std::wostream& os, const CellRange& cr){
        os << L"{valid: " << (cr.valid() ? L"True, [": L"False, [") <<  cr.begin.x << L", " << cr.begin.y << L"]/[" << cr.end.x << L", " << cr.end.y << L"]}";
        return os;
    }

    CellRange::CellRange(){}

    CellRange::~CellRange(){}

};
