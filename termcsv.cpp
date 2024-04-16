
#include "../Term3D/RenderBuffer/RenderBuffer.hpp"
#include "../Term3D/Terminal/Terminal.hpp"
#include "../Term3D/Input/InputManager.hpp"
#include "../Term3D/Input/Parsers.hpp"
#include "../Term3D/Globals/screen_size.hpp"
#include <algorithm>
#include <any>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <spanstream>
#include <sstream>
#include <string>
#include <thread>
#include <variant>
#include <vector>

std::ofstream logt("/dev/pts/3");

volatile bool run = true;
static size_t y_offset = 0;
static size_t scroll_speed = 2;
//add invert later or smth
    //returns how many charachters from the left side is reserved

struct equation
{
    //yeah....
    
};

typedef std::variant<std::ustring, long, double, equation, std::chrono::time_point<std::chrono::system_clock>> cell_value;

void draw_bar(RenderBuffer<Pixel>& rb, unsigned int x){
    for (size_t y = 0; y < rb.h; y++){
        rb.at(x, y) = L'│';
    }
}

size_t draw_numbers(RenderBuffer<Pixel>& rb){
    if(!rb.h) return 0;
    auto reserved = std::to_string(rb.h-1+y_offset).size();

    for (size_t y = 0; y < rb.h; y++){
        auto str = std::to_string(y+y_offset);
        for (size_t x = 0; x < reserved && x < rb.w; x++)
            rb.at(x,y).charachter = (x < str.size() ? str[x] : ' ');
    }
    draw_bar(rb, std::min((uint) reserved, rb.w));
    return reserved+1; //add the bars taken up space
}

std::ustring to_string(const cell_value& a){
    switch (a.index()) {
        case 0: return std::get<0>(a);
        case 1: return std::to_wstring(std::get<1>(a));
        case 2: return std::to_wstring(std::get<2>(a));
        case 3: return L"=";
        case 4:
        {
            std::wostringstream ss;
            ss << std::get<4>(a);
            return ss.str();
        }
        default:
            return L"unknown";
    }
}

struct Column
{
    size_t column_width = 4;
    std::vector<cell_value> colum_data;

    size_t draw(RenderBuffer<Pixel>& rb, size_t x_offset){
        for (size_t y = 0; y < rb.h; y++){
            auto i = y_offset+y;
            if(i >= colum_data.size()) break;
            auto str = to_string(colum_data[i]);
            for (size_t x = 0; x < column_width; x++)
            {
                auto xi = x+x_offset;
                if(xi >= rb.w) break;
                rb.at(xi, y).charachter = (x < str.size() ? str[x] : ' ');
            }
        }
        draw_bar(rb, x_offset+column_width);
        return column_width + 1;
    }
};


std::vector<Column> data;    ///el data





int main(int argc, char const *argv[])
{
    std::locale::global(std::locale("en_US.UTF-8"));
    auto readbuffer = std::clog.rdbuf(logt.rdbuf());
    screen_size = TermIOS::size();
    RenderBuffer<Pixel> rb, db;
    Terminal t;

    InputManager im;
    addParsers(im);


    rb.resize(screen_size).fill({' '});
    db.resize(screen_size).fill({' '});
    rb.write();

    data.push_back(Column{4,{1, 2,3124124,4,5,6}});
    data.push_back(Column{4,{7,8,9,10,11,12,13}});


    MouseEventLambda ml{[](MouseInput m){
        if(m.b == m.B_SCROLL){
            if(m.a == m.A_UP){ //subtract
                if(y_offset < scroll_speed) y_offset =0;
                else y_offset-=scroll_speed;
            }
            else if(m.a == m.A_DOWN){ //add
                y_offset+=scroll_speed;
            }
        }
    }};
    KeyboardEventLambda kl{[](std::unicode u){
        if(u == 'q') run = false;
    }};

    while (run) {
        screen_size = TermIOS::size();
        if(rb._need_to_resize(screen_size.x, screen_size.y)){
            std::jthread rbt([&rb](){
                rb.resize(screen_size).fill({' '});
            });
            db.resize(screen_size).fill({-1});
        }
        else{
            rb.fill({' '});
        }
        auto x_offset = draw_numbers(rb);

        for(auto& e : data){
            if(x_offset >= rb.w) break;
            x_offset+=e.draw(rb, x_offset);
        }

        rb.write_diffrence(db);
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }






    std::clog.rdbuf(readbuffer);
    return 0;
}
