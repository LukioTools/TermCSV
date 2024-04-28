#include "../../lib/SpreadSheet/Sheet.hpp"

#include <cstddef>
#include <vector>

Column& Sheet::operator[](std::size_t i){
    if(i>=columns.size()) columns.resize(i+1);
    return columns[i];
}

bool Sheet::defined(std::size_t i){
    return i<columns.size();
}
std::size_t Sheet::size(){
    return  columns.size();
}

Sheet::Sheet(){}
Sheet::~Sheet(){}