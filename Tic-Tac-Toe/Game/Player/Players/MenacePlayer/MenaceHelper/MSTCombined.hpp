//
//  MSTCombined.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MSTCombined_hpp
#define MSTCombined_hpp

#include <functional>
#include "MenaceStateTransformer.hpp"

class MSTCombined : public MenaceStateTransformer{
public:
    MSTCombined(std::function<uint16_t(uint16_t)> transform, std::function<uint16_t(uint16_t)> revert);
    ~MSTCombined(){}
    
    uint16_t transform(uint16_t state) const;
    uint16_t revert(uint16_t state) const;
    
    Coordinate transform(Coordinate coord) const;
    Coordinate revert(Coordinate coord) const;
    
private:
    std::function<uint16_t(uint16_t)> _transform, _revert;
};

#endif /* MSTCombined_hpp */
