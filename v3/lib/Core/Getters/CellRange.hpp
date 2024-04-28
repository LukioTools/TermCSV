#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <ostream>
#include <regex>
#include <span>
#include <string>
#include "../Getter.hpp"
#include "../../SpreadSheet/Sheet-.hpp"


namespace Getters {


class CellRange : public Getter{
private:
public:
    static constexpr glm::uvec2 invalid = {-1,-1};
    static std::wstring range;
    static std::wstring component;
    static wchar_t constant;
    static std::wregex is_range_regex;


    static bool is_cellrange(const std::span<wchar_t const> sp);
    static std::shared_ptr<CellRange> create(const std::span<wchar_t const> sp);
    static glm::uvec2 parse_comp(const std::span<wchar_t const> sp, bool cst[]);
    static uint parse_num(const std::wstring& sp);
    static bool parse_const(std::span<wchar_t const>& sp);

    glm::uvec2 begin = invalid;    
    glm::uvec2 end = invalid;
    glm::bvec4 constants = {0,0,0,0};  

    std::vector<Eval> get(Sheet& s) override;
    bool valid() const;

    friend std::ostream& operator<<(std::ostream& os, const CellRange& cr);
    friend std::wostream& operator<<(std::wostream& os, const CellRange& cr);

    CellRange();
    ~CellRange();
};


}
