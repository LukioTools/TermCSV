
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
#include <glm/ext/vector_uint2.hpp>
#include <iostream>
#include <iterator>
#include <optional>
#include <spanstream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <thread>
#include <variant>
#include <vector>

std::ofstream logt("/dev/pts/3");

volatile bool run = true;
static size_t y_offset = 0;
static size_t scroll_speed = 1;
//add invert later or smth
    //returns how many charachters from the left side is reserved

struct equation
{
    //yeah....
    
};

typedef std::variant<std::monostate, std::ustring, long, double, equation, std::chrono::time_point<std::chrono::system_clock>> cell_value;


void draw_str(RenderBuffer<Pixel>& rb, const std::ustring& str, unsigned int x, unsigned int y, unsigned int w){
    for (size_t i = 0; i < w; i++)
    {
        auto xi = x+i;
        if(xi >= rb.w) break;
        rb.at(xi,y).charachter = (i < str.size() ? str[i] : ' ');
    }
    
}

void draw_bar(RenderBuffer<Pixel>& rb, unsigned int x){
    for(auto& e : rb.row(0)){
        e.attr.set(Pixel::Attributes::UNDERLIE, true);
    }
    for (size_t y = 1; y < rb.h; y++){
        rb.at(x, y) = L'│';
    }
}

size_t draw_numbers(RenderBuffer<Pixel>& rb){
    if(!rb.h) return 0;
    auto reserved = std::to_string(rb.h-2+y_offset).size();

    for (size_t y = 1; y < rb.h; y++){
        auto str = std::to_string(y+y_offset-1);
        for (size_t x = 0; x < reserved && x < rb.w; x++)
            rb.at(x,y).charachter = (x < str.size() ? str[x] : ' ');
    }
    draw_bar(rb, std::min((uint) reserved, rb.w));

    
    return reserved+1; //add the bars taken up space
}
size_t draw_numbers_n(RenderBuffer<Pixel>& rb){
    return std::to_string(rb.h-1+y_offset).size() + 1;
     
}


std::ustring to_string(const cell_value& a){
    switch (a.index()) {
        case 0: return {};
        case 1: return std::get<1>(a);
        case 2: return std::to_wstring(std::get<2>(a));
        case 3: return std::to_wstring(std::get<3>(a));
        case 4: return L"=";
        case 5:
        {
            std::wostringstream ss;
            ss << std::get<5>(a);
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
    std::ustring name;

    size_t draw(RenderBuffer<Pixel>& rb, size_t x_offset){
        for (size_t y = 1; y < rb.h; y++){
            auto i = y_offset+y-1;
            if(i >= colum_data.size()) break;
            auto str = to_string(colum_data[i]);
            draw_str(rb, str, x_offset, y, column_width);
        }
        draw_str(rb, name, x_offset, 0, column_width);
        draw_bar(rb, x_offset+column_width);
        return column_width + 1;
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
};


std::vector<Column> data;    ///el data

std::vector<uint> bar_placements(RenderBuffer<Pixel>& rb){
    std::vector<uint> out;
    uint cw=out.emplace_back(draw_numbers_n(rb)-1)+1;
    for(auto& e : data){
        cw=out.emplace_back(cw+e.column_width)+1;
    }
    return out;
}


cell_value* selected = nullptr; 

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

    data.push_back(Column{4,{1, 2,3124124,4,5,6}, Column::make_name(data.size())});
    data.push_back(Column{4,{7,8,9,10,11,12,13}, Column::make_name(data.size())});

    static constexpr glm::uvec2 mdown_invalid  = {-1,-1};
    glm::uvec2 mdown_pos = mdown_invalid;
    glm::uvec2 mdown_move_bar_pos = mdown_invalid;
    uint bar_index = 0;

    MouseEventLambda ml{[&rb, &mdown_move_bar_pos, &bar_index](MouseInput m){
        auto bars = bar_placements(rb);
        if(mdown_move_bar_pos == mdown_invalid && m.b == m.B_LEFT){
            bar_index = 0;
            for (size_t i = 0; i < bars.size(); i++)
                if(bars[i] == m.pos.x){
                    bar_index = i;
                    std::clog << "bar_index: " << bar_index << std::endl;
                }
        }
        
        if(m.b == m.B_SCROLL){
            if(m.a == m.A_UP){ //subtract
                if(y_offset < scroll_speed) y_offset =0;
                else y_offset-=scroll_speed;
            }
            else if(m.a == m.A_DOWN){ //add
                y_offset+=scroll_speed;
            }
        }
        if(m.b == m.B_LEFT){
            switch (m.a) {
                case m.A_DOWN:
                    if(bar_index){
                        mdown_move_bar_pos = m.pos;
                        break;
                    }
                    
                break;
                case m.A_HILIGHT:
                case m.A_UP:
                    if(mdown_move_bar_pos != mdown_invalid && bar_index){
                        long diff = long(m.pos.x) - long(mdown_move_bar_pos.x);
                        if (bar_index-1 < data.size())
                        {
                            auto& e = data[bar_index-1];
                            if(diff > 0) e.column_width+=diff;
                            else if(std::abs(diff)>= e.column_width) e.column_width = 0;
                            else e.column_width+=diff;
                        }
                        if(m.a == m.A_UP) mdown_move_bar_pos = mdown_invalid;
                        else mdown_move_bar_pos = m.pos;
                    }
                break;
                default:
                break;
            }
        }
    }};
    KeyboardEventLambda kl{[](std::unicode u){
        if(u == 'q') run = false;
    }};

    while (run) {
        screen_size = TermIOS::size();
        if(rb._need_to_resize(screen_size.x, screen_size.y)){
            rb.resize(screen_size);
            db.resize(screen_size).fill({-1});
        }
        rb.fill({});
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
