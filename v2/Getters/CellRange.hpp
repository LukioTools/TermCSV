#pragma once
#include "../Getter.hpp"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include "../Sheet.hpp"

class CellRange : public Getter{
private:
public:
    glm::uvec2 invalid = {-1,-1};
    glm::uvec2 begin = invalid;    
    glm::uvec2 end = invalid;
    glm::bvec4 constants = {0,0,0,0};  

    std::vector<Eval> get(Sheet& s) override{
        if(!valid()) return {};
        std::vector<Eval> out;
        for (auto x = begin.x; x<=end.x && (end.x != -1 || s.defined(x)); x++) {
            auto& e = s[x];
            for(auto y = begin.y; y <= end.y && (end.y != -1 || e.defined(y)); y++){
                for (auto& ev : e[y]->get(s)) {
                    out.push_back(ev);
                }
            }
        }
        return out;
    }


    bool valid(){
        if(begin.x > end.x || begin.y > end.y) return false;
        if(begin == invalid) return false;
        return true;
    }

    CellRange(){
        
    }

    ~CellRange(){}

};