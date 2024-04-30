#pragma once

#include "Cell.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <span>
#include <sys/types.h>
#include <vector>
#include "../headers/Sheet.hpp"
struct Column
{
public:
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
        while (i >= size()) {
            cells.emplace_back(nullptr);
        }
        auto& e = cells[i];
        if(!e) e = Cell::unique(this);
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

    inline static std::unique_ptr<Column> unique(Sheet* parent, size_t index, uint width = 4){
        return std::make_unique<Column>(parent, index, width);
    }

    inline static std::unique_ptr<Column> unique(Sheet* parent, std::ustring name, uint width = 4){
        return std::make_unique<Column>(parent, name, width);
    }

    Column(Sheet* p, size_t index, uint width = 4) : parent(p), n(make_name(index)), w(width) {}
    Column(Sheet* p, std::ustring name, uint width = 4) : n(name), w(width) {}
    Column(Column&& move) :parent(move.parent), n(std::move(move.n)), w(move.w), cells(std::move(move.cells)) {}


    ~Column() = default;

    Sheet* parent = nullptr;
    std::ustring n;
    uint w = 4;
    std::vector<std::unique_ptr<Cell>> cells;
};
