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
