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
#include "Game/Game.hpp"

int main(int argc, const char * argv[]) {
    for(size_t i = 0; i < 100; i++){
        Game game(std::shared_ptr<Player>(new RandomPlayer),
                  std::shared_ptr<Player>(new MinMaxPlayer));
        
        std::cout << game.play() << std::endl;

    }
    
    return 0;
}
