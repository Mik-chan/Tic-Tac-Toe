//
//  RandomPlayer.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <random>
#include "RandomPlayer.hpp"

RandomPlayer::RandomPlayer() {}
RandomPlayer::~RandomPlayer() {}

Coordinate RandomPlayer::decide(const TicTacToe& ttt, TicTacToe::cell_state_t side){
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<uint16_t> dist(0, 8);
    uint16_t r;
    
    do{ r = dist(engine); }while(ttt.arr_state()[r] != TicTacToe::empty);
    
    return {static_cast<uint16_t>(r % 3), static_cast<uint16_t>(r / 3)};
}
