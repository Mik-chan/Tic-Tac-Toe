//
//  MenacePlayer.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MenacePlayer_hpp
#define MenacePlayer_hpp

#include <map>
#include <vector>
#include "Player.hpp"

class MenacePlayer : public Player{
public:
    MenacePlayer();
    ~MenacePlayer();
    
    Coordinate decide(const TicTacToe& ttt, TicTacToe::cell_state_t side);
    
private:
    std::map<uint16_t, std::vector<uint64_t>> brain;
};

#endif /* MenacePlayer_hpp */
