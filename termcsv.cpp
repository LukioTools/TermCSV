
#include "../Term3D/RenderBuffer/RenderBuffer.hpp"
#include "../Term3D/Terminal/Terminal.hpp"
#include "../Term3D/Input/InputManager.hpp"
#include "../Term3D/Input/Parsers.hpp"
#include "../Term3D/Globals/screen_size.hpp"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

std::ofstream logt("/dev/pts/3");

volatile bool run = true;
static size_t y_offset = 0;
static size_t scroll_speed = 2;
//add invert later or smth
    //returns how many charachters from the left side is reserved
size_t draw_numbers(RenderBuffer<Pixel>& rb){
    if(!rb.h) return 0;
    auto reserved = std::to_string(rb.h-1+y_offset).size();

    for (size_t y = 0; y < rb.h; y++){
        auto str = std::to_string(y+y_offset);
        for (size_t x = 0; x < reserved && x < rb.w; x++)
            rb.at(x,y).charachter = (x < str.size() ? str[x] : ' ');
    }
    auto min = std::min((uint) reserved, rb.w);
    for (size_t y = 0; y < rb.h; y++){
        rb.at(min, y) = L'│';
    }
    return reserved+1;
}


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
        draw_numbers(rb);
        rb.write_diffrence(db);
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }






    std::clog.rdbuf(readbuffer);
    return 0;
}
