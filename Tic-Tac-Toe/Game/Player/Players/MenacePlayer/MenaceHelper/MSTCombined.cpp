//
//  MSTCombined.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "MSTCombined.hpp"

MSTCombined::MSTCombined(std::function<uint16_t(uint16_t)> transform, std::function<uint16_t(uint16_t)> revert) : _transform(transform), _revert(revert) {}

uint16_t MSTCombined::transform(uint16_t state) const{
    return _transform(state);
}

uint16_t MSTCombined::revert(uint16_t state) const{
    return _revert(state);
}

Coordinate MSTCombined::transform(Coordinate coord) const{
    std::array<uint16_t, 9> tmp;
    for(uint16_t& val : tmp) val = 0;
    tmp[coord.minify(3)] = 1;
    uint16_t tmp_int = transform(to_int(tmp));
    tmp = to_arr(tmp_int);
    return coord.coordify(std::distance(tmp.begin(), std::find(tmp.begin(), tmp.end(), 1)), 3);
}

Coordinate MSTCombined::revert(Coordinate coord) const{
    std::array<uint16_t, 9> tmp;
    for(uint16_t& val : tmp) val = 0;
    tmp[coord.minify(3)] = 1;
    uint16_t tmp_int = revert(to_int(tmp));
    tmp = to_arr(tmp_int);
    return coord.coordify(std::distance(tmp.begin(), std::find(tmp.begin(), tmp.end(), 1)), 3);
}

