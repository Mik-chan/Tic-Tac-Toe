//
//  Player.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <tuple>
#include "TicTacToe.hpp"
#include "Coordinate.hpp"

class Player{
public:
    Player();
    virtual ~Player();
    
    virtual Coordinate decide(const TicTacToe& ttt, TicTacToe::cell_state_t play_side) = 0;
    Coordinate operator()(const TicTacToe& ttt, TicTacToe::cell_state_t play_side);    
};

#endif /* Player_hpp */
