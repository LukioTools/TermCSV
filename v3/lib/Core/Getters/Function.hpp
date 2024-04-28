#pragma once

#include "../Getter.hpp"
#include <functional>
#include <map>
#include <memory>
#include <regex>
#include <span>
#include <string_view>
#include <type_traits>
#include <vector>

namespace Getters {

class Function : public Getter{
private:
public:
    using Type = std::function<std::vector<Eval>(std::span<Eval>)>;
    std::vector<std::shared_ptr<Getter>> getters;
    Type function;

    static inline std::map<std::wstring_view, Type> functions;

    static inline std::wregex is_function_regex = std::wregex(L"^.*?\\(.*\\)$");

    static bool is_function(const std::span<const wchar_t> span);

    static std::shared_ptr<Function> create(const std::span<const wchar_t>& sp);

    std::vector<Eval> get(Sheet& s) override;

    Function& fn(const Type& i);

    Function& fn(Type&& i);

    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& add(const va& ...copy);
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& add(va&& ...move);
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& set(const va& ...copy);
    template<class ...va>
    requires(std::is_same_v<va, std::shared_ptr<Getter>> &&...)
    Function& set(va&& ...move);


    Function();
    Function(const Type& fn, const std::vector<std::shared_ptr<Getter>>& v);
    Function(const Type& fn, std::vector<std::shared_ptr<Getter>>&& v);
    ~Function();

};
}