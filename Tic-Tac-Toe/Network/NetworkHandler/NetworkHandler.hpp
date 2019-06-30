//
//  NetworkHandler.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 30.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef NetworkHandler_hpp
#define NetworkHandler_hpp

#include <memory>

class NetworkHandler : public std::enable_shared_from_this<NetworkHandler>{
public:
    typedef std::shared_ptr<NetworkHandler> ptr;
    
    virtual void run() = 0;
};

#endif /* NetworkHandler_hpp */
