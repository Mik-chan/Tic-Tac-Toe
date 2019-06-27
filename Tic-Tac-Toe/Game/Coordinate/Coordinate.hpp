//
//  Coord.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef Coord_hpp
#define Coord_hpp

#include <cstdlib>

struct Coordinate{
    uint16_t x, y;
    
    uint16_t minify(uint16_t row_size) const{
        return x + y * row_size;
    }
    
    Coordinate& coordify(uint16_t state, uint16_t row_size){
        x = state % row_size;
        y = state / row_size;
        return *this;
    }
};

#endif /* Coord_hpp */
