//
//  MinMaxPlayer.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MinMaxPlayer_hpp
#define MinMaxPlayer_hpp

#include <array>
#include "Player.hpp"

class MinMaxPlayer : public Player{
public:
    MinMaxPlayer();
    ~MinMaxPlayer();
    
    Coordinate decide(const TicTacToe& ttt, TicTacToe::cell_state_t side);
    
private:
    struct MinMaxS{
        uint16_t where;
        double grade;
    };
    
    MinMaxS minmax(uint16_t state);
    uint16_t flip_sides(uint16_t state) const;
    std::array<uint16_t, 9> get(uint16_t state) const;
    uint16_t set(uint16_t state, uint16_t where, uint16_t what) const;
    
    bool check_draw(uint16_t state) const;
    bool check_win(bool me_winner, uint16_t state) const;
};

#endif /* MinMaxPlayer_hpp */
