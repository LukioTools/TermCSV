#pragma  once


#include "Column.hpp"
#include <cstddef>
#include <vector>
class Sheet{
private:
    std::vector<Column> columns;
public:
    Column& operator[](std::size_t i){
        if(i>=columns.size()) columns.resize(i);
        return columns[i];
    }

    bool defined(std::size_t i){
        return i<columns.size();
    }

    std::size_t size(){
        return  columns.size();
    }


    Sheet(){}
    ~Sheet(){}
};