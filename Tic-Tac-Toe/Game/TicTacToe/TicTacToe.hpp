//
//  TicTacToe.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <ostream>
#include <array>
#include <tuple>

class TicTacToe{
public:
    enum cell_state_t {
        empty = 0,
        cross = 1,
        circle = 2
    };
    
    enum game_state_t {
        error, going_on, cross_won, circle_won, draw
    };
    
    TicTacToe();
    TicTacToe(uint16_t state);
    TicTacToe(const std::array<cell_state_t, 9>& state);
    
    const std::array<cell_state_t, 9>& arr_state() const;
    uint16_t int_state() const;
    
    bool play_cross(uint16_t x, uint16_t y);
    bool play_circle(uint16_t x, uint16_t y);
    
    cell_state_t get_turn() const;
    game_state_t get_game_state() const;
    
private:
    std::pair<uint16_t, uint16_t> count_state() const;
    bool check_win(cell_state_t winner) const;
    
    
    std::array<cell_state_t, 9> state;
    cell_state_t turn = empty;
};

std::ostream& operator<<(std::ostream&, const TicTacToe&);
std::ostream& operator<<(std::ostream&, const TicTacToe::cell_state_t&);


#endif /* TicTacToe_hpp */
