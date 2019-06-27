//
//  TicTacToe.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include "TicTacToe.hpp"

TicTacToe::TicTacToe(){
    for(cell_state_t& cell : state)
        cell = empty;
    turn = circle;
}

TicTacToe::TicTacToe(uint16_t state){
    for(cell_state_t& cell : this->state){
        cell = static_cast<cell_state_t>(state % 3);
        state /= 3;
    }
    auto count = count_state();
    if(count.first == count.second) turn = circle;
    else if(count.first == count.second + 1) turn = cross;
}

TicTacToe::TicTacToe(const std::array<cell_state_t, 9>& state){
    this->state = state;
    auto count = count_state();
    if(count.first == count.second) turn = circle;
    else if(count.first == count.second + 1) turn = cross;
}

const std::array<TicTacToe::cell_state_t, 9>& TicTacToe::arr_state() const{
    return this->state;
}

uint16_t TicTacToe::int_state() const{
    uint16_t res = 0;
    
    for(int i = 8; i >= 0; i--){
        res *= 3;
        res += state[i];
    }
    
    return res;
}

bool TicTacToe::play_cross(uint16_t x, uint16_t y){
    if(x > 2 || y > 2) return false;
    if(state[x + y * 3] != empty) return false;
    if(turn != cross) return false;
    state[x + y * 3] = cross;
    turn = circle;
    return true;
}

bool TicTacToe::play_circle(uint16_t x, uint16_t y){
    if(x > 2 || y > 2) return false;
    if(state[x + y * 3] != empty) return false;
    if(turn != circle) return false;
    state[x + y * 3] = circle;
    turn = cross;
    return true;
}

std::pair<uint16_t, uint16_t> TicTacToe::count_state() const{
    uint16_t cross = 0, circle = 0;
    for(const cell_state_t& cell : state){
        cross += cell == cross;
        circle += cell == circle;
    }
    return {cross, circle};
}

TicTacToe::cell_state_t TicTacToe::get_turn() const{
    return turn;
}

TicTacToe::game_state_t TicTacToe::get_game_state() const{
    if(check_win(circle)) return circle_won;
    else if(check_win(cross)) return cross_won;
    
    auto count = count_state();
    if(count.first + count.second == 9) return draw;
    
    return going_on;
}

bool TicTacToe::check_win(TicTacToe::cell_state_t winner) const{
    bool row_win =
    (state[0] == state[1] && state[1] == state[2] && state[2] == winner) ||
    (state[3] == state[4] && state[4] == state[5] && state[5] == winner) ||
    (state[6] == state[7] && state[7] == state[8] && state[8] == winner);
    
    bool col_win =
    (state[0] == state[3] && state[3] == state[6] && state[6] == winner) ||
    (state[1] == state[4] && state[4] == state[7] && state[7] == winner) ||
    (state[2] == state[5] && state[5] == state[8] && state[8] == winner);
    
    bool diag_win =
    (state[0] == state[4] && state[4] == state[8] && state[8] == winner) ||
    (state[2] == state[4] && state[4] == state[6] && state[6] == winner);
    
    return row_win || col_win || diag_win;
}

std::ostream& operator<<(std::ostream& os, const TicTacToe& ttt){
    for(size_t i = 0; i < 9; i++){
        if(i % 3 == 0) os << std::endl;
        os << ttt.arr_state()[i];
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const TicTacToe::cell_state_t& state){
    switch (state) {
        case TicTacToe::empty: os << ' '; break;
        case TicTacToe::cross: os << 'x'; break;
        case TicTacToe::circle: os << 'o'; break;
    }
    return os;
}
