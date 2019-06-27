//
//  Game.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "Game.hpp"
#include "Coordinate.hpp"

Game::Game(std::shared_ptr<Player> circle, std::shared_ptr<Player> cross){
    this->circle = circle;
    this->cross = cross;
}

const TicTacToe& Game::play(){
    TicTacToe::game_state_t state;
    
    while((state = ttt.get_game_state()) == TicTacToe::going_on){
        Coordinate decision;
        if(ttt.get_turn() == TicTacToe::cell_state_t::circle){
            decision = circle->decide(ttt, TicTacToe::cell_state_t::circle);
            ttt.play_circle(decision.x, decision.y);
        }
        else if(ttt.get_turn() == TicTacToe::cell_state_t::cross){
            decision = cross->decide(ttt, TicTacToe::cell_state_t::cross);
            ttt.play_cross(decision.x, decision.y);
        }
    }
    
    return ttt;
}

