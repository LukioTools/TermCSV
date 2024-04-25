#pragma  once
#include <cstddef>
#include <vector>
#include "Cell.hpp"


class Column{
private:
    std::vector<Cell> cells;
public:
    Cell& operator[](std::size_t i){
        if(!defined(i)) cells.resize(i);
        return cells[i];
    }

    inline std::size_t size()const{
        return cells.size();
    }

    inline bool defined(std::size_t i)const{
        return i < cells.size();
    }

    Column(){}
    ~Column(){}
};

