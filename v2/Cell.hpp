#pragma once



#include <memory>
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

    Cell(const std::shared_ptr<Getter> getter = none_value) : std::shared_ptr<Getter>(getter){}
    ~Cell(){}
};