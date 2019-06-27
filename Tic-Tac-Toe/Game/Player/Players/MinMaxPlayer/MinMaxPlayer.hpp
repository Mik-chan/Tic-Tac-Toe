//
//  MinMaxPlayer.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MinMaxPlayer_hpp
#define MinMaxPlayer_hpp

#include <map>
#include "Player.hpp"

class MinMaxPlayer : public Player{
public:
    MinMaxPlayer();
    ~MinMaxPlayer();
    
    Coordinate decide(const TicTacToe& ttt, TicTacToe::cell_state_t side);
    
private:
    std::pair<uint16_t, uint16_t> minmax(uint16_t state);
    uint16_t flip_sides(uint16_t state) const;
    uint16_t get(uint16_t coord, uint16_t state) const;
    
    static std::map<uint16_t, std::pair<uint16_t, uint16_t>> memory;
};

#endif /* MinMaxPlayer_hpp */
