



#include "Cell.hpp"
#include <memory>
#include <span>
#include <sys/types.h>
#include <vector>
struct Column
{
    inline size_t size()const{
        return cells.size();
    }
    bool exists(size_t i){
        if(i >= size()) return false;
        return static_cast<bool>(cells[i]);
    }
    std::span<std::unique_ptr<Cell>> span(size_t from, size_t to){
        if(to >= size()){
            cells.resize(to);
        }
        return std::span<std::unique_ptr<Cell>>{cells.begin()+from, cells.begin()+to};
    }
    Cell& operator[](size_t i){
        if(i >= size()){
            cells.resize(i);
        }

        auto& e = cells[i];
        if(e) return *e;
        e = e->unique();
        return *e;
    }
    uint width(){
        return w;
    }
    Column& width(uint i){
        w= i;
        return *this;
    }
    std::ustring name(){
        return n;
    }
    Column& name(const std::ustring& s){
        n=s;
        return *this;
    }
    static std::ustring make_name(size_t i){
        std::ustring out;
        constexpr size_t d = 'Z'-'A';
        do {
            out+= 'A'+(i%d);
            i/=d;
        }
        while (i);
        return out;
    }

    Column(){}
    Column(size_t index, uint width = 4) : n(make_name(index)), w(width) {}
    Column(std::ustring name, uint width = 4) : n(name), w(width) {}
    ~Column() = default;

protected:
    std::ustring n;
    uint w = 4;
    std::vector<std::unique_ptr<Cell>> cells;
};
