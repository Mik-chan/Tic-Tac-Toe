//
//  Game.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <memory>
#include "Player.hpp"
#include "TicTacToe.hpp"

class Game{
public:
    Game(std::shared_ptr<Player> circle, std::shared_ptr<Player> cross);
    
    const TicTacToe& play();
    
private:
    TicTacToe ttt;
    std::shared_ptr<Player> circle, cross;
};

#endif /* Game_hpp */
