//
//  ConsolePlayer.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef ConsolePlayer_hpp
#define ConsolePlayer_hpp

#include <string>
#include "Player.hpp"

class ConsolePlayer : public Player{
public:
    ConsolePlayer(const std::string& name);
    ~ConsolePlayer();
    
    Coordinate decide(const TicTacToe& ttt, TicTacToe::cell_state_t side);
    
private:
    std::string name;
};

#endif /* ConsolePlayer_hpp */
