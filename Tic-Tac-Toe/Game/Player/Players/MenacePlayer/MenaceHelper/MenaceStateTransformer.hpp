//
//  MenaceStateTransformer.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MenaceStateTransformer_hpp
#define MenaceStateTransformer_hpp

#include <cstdlib>
#include <array>
#include "Coordinate.hpp"

class MenaceStateTransformer{
public:
    virtual ~MenaceStateTransformer(){};
    
    virtual uint16_t transform(uint16_t state) const = 0;
    virtual uint16_t revert(uint16_t state) const = 0;
    
    virtual Coordinate transform(Coordinate coord) const;
    virtual Coordinate revert(Coordinate coord) const;
    
protected:
    std::array<uint16_t, 9> to_arr(uint16_t state) const;
    uint16_t to_int(const std::array<uint16_t, 9>& state) const;

};

#endif /* MenaceStateTransformer_hpp */
