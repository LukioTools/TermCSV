#pragma once

#include "../Getter.hpp"
#include <glm/glm.hpp>
#include "../../sources/Sheet.hpp"
namespace Getters
{
        //can be used for individual cells
    struct cell_range : public Getter
    {
        //has to be actually a range, aka [0, 2[, where 2 is excluded
        glm::uvec2 b = {0,0};
        glm::uvec2 e = {0,0};
            //one column at a time, empty cells, empty columns left out
        std::vector<eval_value> get(Sheet &s) override{
            if(b == e) return {};
            std::vector<eval_value> out;
            for (size_t x = b.x; x < e.x && x < s.size(); x++){
                auto& c = s[x];
                for (size_t y = b.y; y < e.y && y < c.size(); y++){
                    auto& v = c[y];
                    out.emplace_back(v.value.eval(s));
                }
            }
            return out;
        };
        cell_range(const glm::uvec2 from, const glm::uvec2 to) : b(from), e(to){}
    };
} // namespace Getters

