#pragma once

#include "../Getter.hpp"
#include <algorithm>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <span>
#include <string_view>
#include <variant>
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
        inline static std::shared_ptr<Getter> shared(const glm::uvec2 from, const glm::uvec2 to){
            return std::make_shared<cell_range>(from, to);
        }
        inline static std::unique_ptr<Getter> unique(const glm::uvec2 from, const glm::uvec2 to){
            return std::make_unique<cell_range>(from, to);
        }
        inline static std::ustring range_seperator = L"->";
        inline static std::ustring component_seperator = L":";
        inline static constexpr glm::uvec2 invalid = {-1, -1};

        inline static std::shared_ptr<Getter> shared(const std::span<const std::unicode>& span) try {
            auto sep = find(span, range_seperator);
            if(sep == span.end()) return nullptr;

            std::span<const std::unicode>beg{span.begin(), sep};
            std::span<const std::unicode>end{sep + range_seperator.size(), span.end()};
            auto from = components(beg);
            auto to = components(end);

            if(from == invalid) return nullptr;

            return std::make_shared<cell_range>(from, to);
        }catch(...){
            return nullptr;
        }

        cell_range(const glm::uvec2 from, const glm::uvec2 to) : b(from), e(to){}

    private:
        inline static std::span<const std::unicode>::iterator find(const std::span<const std::unicode>& span, const std::wstring_view v){
            std::wstring_view view(span.begin(), span.end());
            auto e = view.find(v);
            if(e == std::variant_npos) return span.end();
            return span.begin()+e;
        }
        inline static glm::uvec2 components(const std::span<const std::unicode>& span)try{
            
            return {-1, -1};
        }catch(...){
            return {-1, -1};
        }

    };
} // namespace Getters

