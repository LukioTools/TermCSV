#pragma once

#include "../Getter.hpp"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>
#include "../../sources/Sheet.hpp"
namespace Getters
{
        //can be used for individual cells
    struct cell_range : public Getter
    {
        //has to be actually a range, aka [0, 2[, where 2 is excluded
        glm::uvec2 b = {0,0};
        glm::uvec2 e = {0,0};
        glm::bvec4 state = {0,0,0,0};


            //one column at a time, empty cells, empty columns left out
        std::vector<eval_value> get(Sheet &s) override{
            if(b == e) return {};
            std::vector<eval_value> out;
            for (size_t x = b.x; x < e.x && x < s.size(); x++){
                auto& c = s[x];
                for (size_t y = b.y; y < e.y && y < c.size(); y++){
                    auto& v = c[y];
                    out.emplace_back(v.eval(s));
                }
            }
            return out;
        };
        inline static cell_range create(const std::span<std::unicode const>& span){
            return cell_range{{},{}};
        }
        inline static std::shared_ptr<Getter> shared(const glm::uvec2 from, const glm::uvec2 to){
            return std::make_shared<cell_range>(from, to);
        }
        inline static std::unique_ptr<Getter> unique(const glm::uvec2 from, const glm::uvec2 to){
            return std::make_unique<cell_range>(from, to);
        }
        cell_range(const glm::uvec2 from, const glm::uvec2 to) : b(from), e(to){}
    };
} // namespace Getters

