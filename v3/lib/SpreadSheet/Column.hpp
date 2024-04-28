#pragma  once
#include <cstddef>
#include <vector>
#include "Cell.hpp"

class Column{
private:
    std::vector<Cell> cells;
public:

    Cell& operator[](std::size_t i);

    std::size_t size()const;

    bool defined(std::size_t i)const;

    Column();
    ~Column();
};

