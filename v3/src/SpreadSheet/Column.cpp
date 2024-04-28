#include <cstddef>
#include <vector>
#include "../../lib/SpreadSheet/Column.hpp"



Cell& Column::operator[](std::size_t i){
    if(!defined(i)) cells.resize(i+1);
    return cells[i];
}
std::size_t Column::size()const{
    return cells.size();
}
bool Column::defined(std::size_t i)const{
    return i < cells.size();
}

Column::Column(){}
Column::~Column(){}

