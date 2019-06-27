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

MinMaxPlayer::MinMaxS MinMaxPlayer::minmax(uint16_t state){
    static std::map<uint16_t, MinMaxPlayer::MinMaxS> memory = {
        {0, {4, INFINITY}}
    };
    
    if(memory.find(state) == memory.end()){
        std::vector<MinMaxPlayer::MinMaxS> steps;
        std::array<uint16_t, 9> _state = get(state);
        for(uint16_t i = 0; i < 9; i++){
            if(_state[i] != 0) continue;
            steps.push_back({i, -INFINITY});
        }
        
        if(steps.size() == 0){
            memory[state] = {9, 1};
        }
        else{
            MinMaxPlayer::MinMaxS total;
            MinMaxPlayer::MinMaxS best = steps.front();
            total.grade = 0;
            for(auto& mm : steps){
                uint16_t tmp_state = set(state, mm.where, 1);
                if(check_win(true, tmp_state)) mm.grade = 1;
                else if (check_win(false, tmp_state)) mm.grade = -1;
                else{
                    std::array<uint16_t, 9> _state = get(state);
                    int sum = 0;
                    for(uint16_t v : _state) sum += !v;
                    if(!sum){
                        mm.grade = 0;
                    }
                    else{
                        tmp_state = flip_sides(tmp_state);
                        auto tmp_mm = minmax(tmp_state);
                        mm.grade = -tmp_mm.grade;
                    }
                }
                
                if(mm.grade > best.grade)
                    best = mm;
                
                //total.grade += mm.grade;
            }
            
            //total.where = best.where;
            //total.grade = best.grade;
            memory[state] = best;
        }
        
    }
    
    MinMaxPlayer::MinMaxS result = memory[state];
    return result;
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
