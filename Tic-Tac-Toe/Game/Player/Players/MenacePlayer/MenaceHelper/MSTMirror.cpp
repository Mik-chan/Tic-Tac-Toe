//
//  MSTMirror.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "MSTMirror.hpp"

uint16_t MSTMirror::transform(uint16_t state) const{
    auto a = to_arr(state);
    
    std::array<uint16_t, 9> new_arr{
        a[2], a[1], a[0],
        a[5], a[4], a[3],
        a[8], a[7], a[4]
    };
    
    return to_int(new_arr);
}

uint16_t MSTMirror::revert(uint16_t state) const{
    return transform(state);
}
