#pragma once
#include <memory>
#include <string>
#include <variant>
#include "../Core/Getter-.hpp"
#include "Sheet-.hpp"


class Cell : public std::shared_ptr<Getter>{
private:
public:
    static std::shared_ptr<Getter> none_value;

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

    std::wstring to_wstring(Sheet &s);

    Cell(const std::shared_ptr<Getter>& getter = none_value);
    Cell(std::shared_ptr<Getter>&& getter);
    ~Cell();
};