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
#include "Game/Game.hpp"

int main(int argc, const char * argv[]) {
    Game game(std::shared_ptr<Player>(new ConsolePlayer("Player 1")),
              std::shared_ptr<Player>(new ConsolePlayer("Player 2")));
    
    std::cout << game.play() << std::endl;
    
    return 0;
}
