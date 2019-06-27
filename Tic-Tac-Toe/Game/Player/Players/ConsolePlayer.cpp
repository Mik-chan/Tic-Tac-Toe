//
//  ConsolePlayer.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <iostream>
#include "ConsolePlayer.hpp"

ConsolePlayer::ConsolePlayer(const std::string& name) : name(name) {}
ConsolePlayer::~ConsolePlayer() {}

std::pair<uint16_t, uint16_t> ConsolePlayer::decide(const TicTacToe& ttt, TicTacToe::cell_state_t side){
    std::cout <<
    name << "'s turn (" << side << ")" << std::endl <<
    "Current game state: " << ttt << std::endl <<
    "Your decision: ";
    std::pair<uint16_t, uint16_t> res;
    std::cin >> res.first >> res.second;
    return res;
}


/*
 ~ConsolePlayer();
 
 std::pair<uint16_t, uint16_t> decide(const TicTacToe& ttt, TicTacToe::cell_state_t side);

 */

