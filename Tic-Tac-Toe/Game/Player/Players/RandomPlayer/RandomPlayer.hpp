//
//  RandomPlayer.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef RandomPlayer_hpp
#define RandomPlayer_hpp

#include "Player.hpp"

class RandomPlayer : public Player{
public:
    RandomPlayer();
    ~RandomPlayer();
    
    std::pair<uint16_t, uint16_t> decide(const TicTacToe& ttt, TicTacToe::cell_state_t side);
};

#endif /* RandomPlayer_hpp */
