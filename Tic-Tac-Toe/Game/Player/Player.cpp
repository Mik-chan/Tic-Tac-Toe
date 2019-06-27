//
//  Player.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "Player.hpp"
#include "TicTacToe.hpp"

Player::Player(){}
Player::~Player(){}

Coordinate Player::operator()(const TicTacToe& ttt, TicTacToe::cell_state_t play_side){
    return decide(ttt, play_side);
}
