#pragma once
#include "eval_value.hpp"
#include "Function.hpp"
#include <functional>
#include <span>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include "Cell.hpp"
#include "Sheet.hpp"
#include "../../Term3D/Unicode/Unicode.hpp"
#include <glm/glm.hpp>



class Equation{
private:
public:
    
    

    //functions
    static eval_value multiply_f(Sheet&, std::span<cell_value> cv);
    static eval_value add_f(Sheet&, std::span<cell_value> cv);
    static eval_value divide_f(Sheet&, std::span<cell_value> cv);


    Function f; // the primary function, since this class is the root, the endpoint :3 
    std::ustring value;

    Equation& parse(){

        return *this;
    }
    Equation& parse(const std::ustring& str){
        value = str;
        return *this;
    }


    eval_value eval(Sheet&) const;
    Equation(/* args */) {}
    ~Equation() {}
};

