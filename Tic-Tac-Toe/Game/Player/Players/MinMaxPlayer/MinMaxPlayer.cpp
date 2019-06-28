//
//  MinMaxPlayer.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 27.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <cmath>
#include <vector>
#include "MinMaxPlayer.hpp"


MinMaxPlayer::MinMaxPlayer() {}
MinMaxPlayer::~MinMaxPlayer() {}

Coordinate MinMaxPlayer::decide(const TicTacToe& ttt, TicTacToe::cell_state_t side){
    uint16_t state = ttt.int_state();
    if(static_cast<int>(side) != 1) state = flip_sides(state);
    
    Coordinate c;
    c.coordify(minmax(state).where, 3);
    return c;
}

MinMaxPlayer::MinMaxS MinMaxPlayer::minmax(const uint16_t state){
    static std::map<uint16_t, MinMaxPlayer::MinMaxS> memory = {
        {0, {4, INFINITY}}
    };
    
    if(memory.find(state) == memory.end()){
        std::vector<MinMaxPlayer::MinMaxS> steps;
        std::array<uint16_t, 9> _state = get(state);
        
        MinMaxPlayer::MinMaxS best{9, -INFINITY};

        for(uint16_t i = 0; i < 9; i++){
            if(_state[i] != 0) continue;
            MinMaxPlayer::MinMaxS mm{i, 0};
            
            uint16_t tmp_state = set(state, i, 1);
            if(check_win(true, tmp_state)) mm.grade = 100;
            else if (check_win(false, tmp_state)) mm.grade = -100;
            else if (check_draw(tmp_state)) mm.grade = 0;
            else{
                tmp_state = flip_sides(tmp_state);
                mm.grade = 1 - minmax(tmp_state).grade;
            }
            
            if(mm.grade > best.grade)
                best = mm;
        }
        
        memory[state] = best;
    }
    
    return memory[state];
}

std::array<uint16_t, 9> MinMaxPlayer::get(uint16_t state) const{
    std::array<uint16_t, 9> res;
    for(uint16_t& cell : res){
        cell = state % 3;
        state /= 3;
    }
    return res;
}

uint16_t MinMaxPlayer::flip_sides(uint16_t state) const{
    std::array<uint16_t, 9> _state = get(state);
    for(uint16_t& cell : _state){
        if(cell == 1) cell = 2;
        else if(cell == 2) cell = 1;
    }
    int res = 0;
    for(int i = 8; i >= 0; i--){
        res *= 3;
        res += _state[i];
    }
    return res;
}

uint16_t MinMaxPlayer::set(uint16_t state, uint16_t where, uint16_t what) const{
    std::array<uint16_t, 9> _state = get(state);
    _state[where] = what;
    int res = 0;
    for(int i = 8; i >= 0; i--){
        res *= 3;
        res += _state[i];
    }
    return res;
}


bool MinMaxPlayer::check_win(bool me_winner, uint16_t state) const{
    int winner = 1 + !me_winner;
    
    std::array<uint16_t, 9> _state = get(state);
    
    bool row_win =
    (_state[0] == _state[1] && _state[1] == _state[2] && _state[2] == winner) ||
    (_state[3] == _state[4] && _state[4] == _state[5] && _state[5] == winner) ||
    (_state[6] == _state[7] && _state[7] == _state[8] && _state[8] == winner);
    
    bool col_win =
    (_state[0] == _state[3] && _state[3] == _state[6] && _state[6] == winner) ||
    (_state[1] == _state[4] && _state[4] == _state[7] && _state[7] == winner) ||
    (_state[2] == _state[5] && _state[5] == _state[8] && _state[8] == winner);
    
    bool diag_win =
    (_state[0] == _state[4] && _state[4] == _state[8] && _state[8] == winner) ||
    (_state[2] == _state[4] && _state[4] == _state[6] && _state[6] == winner);
    
    return row_win || col_win || diag_win;
}

bool MinMaxPlayer::check_draw(uint16_t state) const{
    std::array<uint16_t, 9> _state = get(state);
    int sum = 0;
    for(uint16_t val : _state)
        sum += !val;
    
    return sum == 0;
}
