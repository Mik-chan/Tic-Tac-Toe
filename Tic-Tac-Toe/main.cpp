//
//  main.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <iostream>
#include <memory>

#include "ConsolePlayer.hpp"
#include "RandomPlayer.hpp"
#include "MinMaxPlayer.hpp"
#include "MenacePlayer.hpp"
#include "Game/Game.hpp"

int main(int argc, const char * argv[]) {
    int wins = 0;
    int draw = 0;
    
    std::shared_ptr<MenacePlayer> menace(new MenacePlayer);
    std::shared_ptr<Player> menace_ptr = menace;

    std::shared_ptr<Player> minmax(new MinMaxPlayer);
    
    for(size_t i = 0; i < 100000; i++){
        Game game(menace_ptr, minmax);
        
        TicTacToe ttt = game.play();
        menace->learn(ttt.get_game_state(), TicTacToe::circle);
        wins += ttt.get_game_state() == TicTacToe::circle_won;
        draw += ttt.get_game_state() == TicTacToe::draw;

        std::cout << ttt << std::endl;
    }
    
    std::cout << wins << "/" << 100000 << std::endl;
    std::cout << draw << "/" << 100000 << std::endl;

    {
        Game game(menace_ptr, minmax);
        std::cout << game.play() << std::endl;
    }
    
    return 0;
}
