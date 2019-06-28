//
//  MSTMirror.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MSTMirror_hpp
#define MSTMirror_hpp

#include "MenaceStateTransformer.hpp"

class MSTMirror : public MenaceStateTransformer{
public:
    ~MSTMirror(){}
    
    uint16_t transform(uint16_t state) const;
    uint16_t revert(uint16_t state) const;    
};

#endif /* MSTMirror_hpp */
