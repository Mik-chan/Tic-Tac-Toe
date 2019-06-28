//
//  MSTRotate.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MSTRotate_hpp
#define MSTRotate_hpp

#include "MenaceStateTransformer.hpp"

class MSTRotate : public MenaceStateTransformer{
public:
    ~MSTRotate(){}
    
    uint16_t transform(uint16_t state) const;
    uint16_t revert(uint16_t state) const;
};

#endif /* MSTRotate_hpp */
