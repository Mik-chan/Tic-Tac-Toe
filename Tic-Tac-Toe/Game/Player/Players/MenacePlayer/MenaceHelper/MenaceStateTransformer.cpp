//
//  MenaceStateTransformer.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <algorithm>
#include "MenaceStateTransformer.hpp"

Coordinate MenaceStateTransformer::transform(Coordinate coord) const{
    std::array<uint16_t, 9> tmp;
    for(uint16_t& val : tmp) val = 0;
    tmp[coord.minify(3)] = 1;
    uint16_t tmp_int = transform(to_int(tmp));
    tmp = to_arr(tmp_int);
    return coord.coordify(std::distance(tmp.begin(), std::find(tmp.begin(), tmp.end(), 1)), 3);
}

Coordinate MenaceStateTransformer::revert(Coordinate coord) const{
    std::array<uint16_t, 9> tmp;
    for(uint16_t& val : tmp) val = 0;
    tmp[coord.minify(3)] = 1;
    uint16_t tmp_int = revert(to_int(tmp));
    tmp = to_arr(tmp_int);
    return coord.coordify(std::distance(tmp.begin(), std::find(tmp.begin(), tmp.end(), 1)), 3);
}

std::array<uint16_t, 9> MenaceStateTransformer::to_arr(uint16_t state) const{
    std::array<uint16_t, 9> res;
    for(uint16_t& val : res){
        val = state % 3;
        state /= 3;
    }
    return res;
}

uint16_t MenaceStateTransformer::to_int(const std::array<uint16_t, 9>& state) const{
    uint16_t res = 0;
    for(int i = 8; i >= 0; i--){
        res *= 3;
        res += state[i];
    }
    return res;
}
