#pragma once
#include "Column.hpp"
#include <memory>
#include <utility>
#include <vector>


class Sheet
{
protected:
    std::vector<std::unique_ptr<Column>> columns;
public:

        //created as are needed
    Column& operator[](size_t i){
        while (i >= columns.size()){columns.emplace_back(nullptr);}
        auto& e = columns[i];
        if(!e) e = Column::unique(this, i);
        return *e;
    }

    inline size_t size(){
        return columns.size();
    }

    Sheet() {}
    ~Sheet() {}
};
