#pragma once


#include <memory>
#include <vector>
#include <span>
#include "../Getter.hpp"


enum TermType{
    UNKNOWN,
    VALUE,
    FUNCTION,
    CELLRANGE,
};

struct split_function_t{
    const std::span<const wchar_t> fn;
    const std::span<const wchar_t> args;

    friend std::wostream& operator<<(std::wostream& os, const split_function_t& sf){
        os << "{ fn: " <<  std::wstring_view(sf.fn.begin(), sf.fn.end()) << ", args: { " << std::wstring_view(sf.args.begin(), sf.args.end()) << "} }";
        return os;
    }
};

std::span<wchar_t> trim(std::span<wchar_t> sp);
std::vector<std::span<wchar_t>> parse_terms(const std::span<wchar_t>& sp);
std::unique_ptr<split_function_t>  split_function(const std::span<const wchar_t> span);
std::vector<std::shared_ptr<Getter>> parse(const std::span<const wchar_t> wc);

