#pragma once

#include "../Getter.hpp"
#include <algorithm>
#include <charconv>
#include <exception>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <variant>
#include "../../sources/Sheet.hpp"
namespace Getters
{
        //can be used for individual cells
    struct cell_range : public Getter
    {
        //has to be actually a range, aka [0, 2[, where 2 is excluded
        glm::uvec2 b = invalid;
        glm::uvec2 e = invalid;
        glm::bvec4 state = {0,0,0,0};


            //one column at a time, empty cells, empty columns left out
        std::vector<eval_value> get(Sheet &s) override{
            if(!valid()) return {};
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
        std::shared_ptr<Getter> create(const std::span<std::unicode>& span){
            return std::make_shared<cell_range>(span);
        }
        
        cell_range(const glm::uvec2 from, const glm::uvec2 to, const glm::bvec4 staticb = {0,0,0,0}) : b(from), e(to), state(staticb) {}
        cell_range(const std::span<const std::unicode> span){
            auto sep = Getters::cell_range::find_pos(span, Getters::cell_range::range_seperator);
            std::cout << sep << "/" << span.size() << std::endl;
            if(sep == std::variant_npos || sep+range_seperator.size() > span.size()) throw std::runtime_error("cell_range::invalid constructor argument (could not find seperator): " + std::to_string(sep+ range_seperator.size()) + "/" + std::to_string(span.size()) );

            auto beg = span.subspan(0, sep);
            auto end = span.subspan(sep+range_seperator.size());

            auto from = Getters::cell_range::components(beg);
            auto to = Getters::cell_range::components(end);

            b = from.first;
            e = to.first;
            state = {from.second.x, from.second.y, to.second.x, to.second.y};
        }

    private:
        inline static std::span<const std::unicode>::iterator find(const std::span<const std::unicode>& span, const std::wstring_view v){
            std::wstring_view view(span.begin(), span.end());
            auto e = view.find(v);
            if(e == std::variant_npos) return span.end();
            return span.begin()+e;
        }
        inline static std::size_t find_pos(const std::span<const std::unicode>& span, const std::wstring_view v){
            return std::wstring_view(span.begin(), span.end()).find(v);
        }

        inline static std::pair<glm::uvec2, glm::bvec2> components(const std::span<const std::unicode>& span)noexcept try{
            auto it = find_pos(span, component_seperator);
            if(it == std::variant_npos) return {invalid, {0,0}};
            if(it+component_seperator.size() >= span.size()) return {invalid, {0,0}};

            auto xs = span.subspan(0, it);
            bool xc = false;
            if(!xs.empty() && xs.front() == const_marker){
                xc = true;
                xs = xs.subspan(1);
            }

            auto ys = span.subspan(it+component_seperator.size());
            bool yc = false;
            if(!ys.empty() && ys.front() == const_marker){
                yc = true;
                ys = ys.subspan(1);
            }
            long x = std::stol(std::ustring(xs.begin(), xs.end()));
            long y = std::stol(std::ustring(ys.begin(), ys.end()));
            return {{x, y}, {xc,yc}};
        }catch(const std::exception& e){
            return {invalid, {0,0}};
        }

        bool valid()const{
            return b != invalid;
        }
        operator bool()const{
            return valid();
        }

    public:
        inline static std::ustring range_seperator = L"->";
        inline static std::ustring component_seperator = L":";
        inline static std::unicode const_marker = L'!';

        inline static constexpr glm::uvec2 invalid = {-1, -1};

    };
} // namespace Getters

