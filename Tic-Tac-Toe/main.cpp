//
//  main.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <iostream>
#include <memory>
#include <random>

#include <boost/asio.hpp>

#include "ConsolePlayer.hpp"
#include "RandomPlayer.hpp"
#include "MinMaxPlayer.hpp"
#include "MenacePlayer.hpp"
#include "Game/Game.hpp"

#include "Network/Network.hpp"

#include "WebSocketServerHandler.hpp"

using tcp = boost::asio::ip::tcp;

int main(int argc, const char * argv[]) {
    
    Network net;
    
    WebSocketServerHandler::ptr wss = std::make_shared<WebSocketServerHandler>(net.io_context(),
                                                                              tcp::endpoint(tcp::v4(), 1234));
    
    std::shared_ptr<MinMaxPlayer> mmp = std::make_shared<MinMaxPlayer>();
    wss->read_handler = [wss, mmp](std::string msg, int id){
        TicTacToe ttt(std::stod(msg));
        
        std::cout << id << ": " << std::endl;
        std::cout << ttt << std::endl;
        Coordinate coord = mmp->decide(ttt, TicTacToe::cell_state_t::circle);
        ttt.play_circle(coord.x, coord.y);
        std::cout << ttt << std::endl;
        
        WebSocketSession::ptr wsses = wss->get_session(id);
        
        if(ttt.get_game_state() != TicTacToe::game_state_t::going_on){
            if(ttt.get_game_state() == TicTacToe::game_state_t::circle_won)
                wsses->write(std::to_string(ttt.int_state() + 0 * std::pow(3, 9) + 1 * std::pow(3, 10)));
            else if(ttt.get_game_state() == TicTacToe::game_state_t::cross_won)
                wsses->write(std::to_string(ttt.int_state() + 1 * std::pow(3, 9) + 0 * std::pow(3, 10)));
            else if(ttt.get_game_state() == TicTacToe::game_state_t::draw)
                wsses->write(std::to_string(ttt.int_state() + 1 * std::pow(3, 9) + 1 * std::pow(3, 10)));
            else if(ttt.get_game_state() == TicTacToe::game_state_t::error)
                wsses->write(std::to_string(0));
        }
        else{
            wsses->write(std::to_string(ttt.int_state()));
        }
    };
    
    net.add_handler(wss);
    
    net.run();
    
    /*
    int wins = 0;
    int draw = 0;
    
    std::shared_ptr<MenacePlayer> menace(new MenacePlayer);
    std::shared_ptr<Player> minmax(new MinMaxPlayer);
    std::shared_ptr<Player> rand(new RandomPlayer);
    
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<bool> decision(false, true);
    std::shared_ptr<Game> g;

    menace->load("brain.menace");

    const int TIMES = 100;
    
    for(size_t i = 0; i < TIMES; i++){
        TicTacToe::cell_state_t side;
        TicTacToe::game_state_t win_state;
        
        if(decision(engine)){
            side = TicTacToe::circle;
            win_state = TicTacToe::circle_won;
            if(decision(engine))
                g = std::make_shared<Game>(menace, minmax);
            else
                g = std::make_shared<Game>(menace, rand);
        }
        else{
            side = TicTacToe::cross;
            win_state = TicTacToe::cross_won;
            if(decision(engine))
                g = std::make_shared<Game>(minmax, menace);
            else
                g = std::make_shared<Game>(rand, menace);
        }
        
        TicTacToe ttt = g->play();
        menace->learn(ttt.get_game_state(), side);
        wins += ttt.get_game_state() == win_state;
        draw += ttt.get_game_state() == TicTacToe::draw;

        std::cout << ttt << std::endl;
    }
    
    std::cout << 100. * wins / TIMES << "%" << std::endl;
    std::cout << 100. * draw / TIMES << "%" << std::endl;

    menace->save("brain.menace");
    
    {
        Game game(menace, rand);
        std::cout << game.play() << std::endl;
    }
     
     */
    return 0;
}
