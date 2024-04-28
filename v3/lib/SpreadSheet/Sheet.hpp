#pragma  once


#include "Column.hpp"
#include <cstddef>
#include <vector>


class Sheet{
private:
    std::vector<Column> columns;
public:

    Column& operator[](std::size_t i);
    bool defined(std::size_t i);
    std::size_t size();

    Sheet();
    ~Sheet();
};