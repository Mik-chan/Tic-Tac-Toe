//
//  MenacePlayer.cpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#include <algorithm>
#include <numeric>
#include <random>

#include "MenacePlayer.hpp"
#include "MSTMirror.hpp"
#include "MSTRotate.hpp"

MenacePlayer::MenacePlayer(){
    memory.clear();
}

MenacePlayer::~MenacePlayer(){}

Coordinate MenacePlayer::decide(const TicTacToe& ttt, TicTacToe::cell_state_t side){
    uint16_t state = ttt.int_state();
    if(static_cast<int>(side) != 1) state = revert_state(state);
    auto tf = best_transform(state);
    
    state = tf.transform(state);
    
    if(brain.find(state) != brain.end()){
        if(std::accumulate(brain[state].begin(), brain[state].end(), 0) == 0)
            brain.erase(state);
    }
    
    if(brain.find(state) == brain.end()){
        uint16_t tmp_state = state;
        for(int i = 0; i < 9; i++){
            uint16_t tmp = tmp_state % 3;
            tmp_state /= 3;
            
            if(tmp == 0)
                brain[state][i] = 10;
        }
    }
    
    int idx = static_cast<int>(weighted_random(brain[state]));
    
    memory.push_back({state, idx});
    
    Coordinate coord;
    coord.coordify(idx, 3);
    
    return tf.revert(coord);
}

void MenacePlayer::learn(TicTacToe::game_state_t state, TicTacToe::cell_state_t side){
    int prize = 0;
    switch (state) {
        case TicTacToe::cross_won:
            prize = side == TicTacToe::cross ? 5 : -3;
            break;
            
        case TicTacToe::circle_won:
            prize = side == TicTacToe::circle ? 5 : -3;
            break;
            
        case TicTacToe::draw:
            prize = 2;
            break;
        default:
            break;
    }
    
    for(auto mem : memory)
        brain[mem.first][mem.second] = std::abs(static_cast<int64_t>(brain[mem.first][mem.second]) + prize);
    
    memory.clear();
}


size_t MenacePlayer::weighted_random(const std::array<uint64_t, 9>& weights){
    uint64_t sum = std::accumulate(weights.begin(), weights.end(), 0);
    
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<uint64_t> dist(0, sum - 1);
    
    uint64_t pool = 0;
    uint64_t rand = dist(engine);
    for(int i = 0; i < 9; i++){
        pool += weights[i];
        if(rand < pool)
            return i;
    }
    
    return 10;
}


uint16_t MenacePlayer::revert_state(uint16_t state) const{
    uint16_t res = 0;
    int mul = 1;
    
    for(int i = 0; i < 9; i++){
        uint16_t tmp = state % 3;
        
        if(tmp == 1) tmp = 2;
        else if(tmp == 2) tmp = 1;
        
        res += tmp * mul;
        
        state /= 3;
        mul *= 3;
    }
    
    return res;
}

const MSTCombined& MenacePlayer::best_transform(uint16_t state) const{
    return *std::max_element(transformers.begin(), transformers.end(),
                             [state](const MSTCombined& a, const MSTCombined& b){
                                 return a.transform(state) < b.transform(state);
                             });
}

const std::vector<MSTCombined> MenacePlayer::transformers{
    //Transform 1 : none
    {
        [](uint16_t state) -> uint16_t{
            return state;
        },
        [](uint16_t state) -> uint16_t{
            return state;
        }
    },
    //Transform 2 : mirror
    {
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            return mirror.transform(state);
        },
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            return mirror.revert(state);
        }
    },
    //Transform 3 : rotate
    {
        [](uint16_t state) -> uint16_t{
            MSTRotate rotate;
            return rotate.transform(state);
        },
        [](uint16_t state) -> uint16_t{
            MSTRotate rotate;
            return rotate.revert(state);
        }
    },
    //Transform 4 : mirror -> rotate
    {
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            MSTRotate rotate;
            return rotate.transform(mirror.transform(state));
        },
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            MSTRotate rotate;
            return mirror.revert(rotate.revert(state));
        }
    },
    //Transform 5 : rotate -> rotate
    {
        [](uint16_t state) -> uint16_t{
            MSTRotate rotate;
            return rotate.transform(rotate.transform(state));
        },
        [](uint16_t state) -> uint16_t{
            MSTRotate rotate;
            return rotate.revert(rotate.revert(state));
        }
    },
    //Transform 6 : mirror -> rotate -> rotate
    {
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            MSTRotate rotate;
            return rotate.transform(rotate.transform(mirror.transform(state)));
        },
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            MSTRotate rotate;
            return mirror.revert(rotate.revert(rotate.revert(state)));
        }
    },
    //Transform 7 : rotate -> rotate -> rotate
    {
        [](uint16_t state) -> uint16_t{
            MSTRotate rotate;
            return rotate.transform(rotate.transform(rotate.transform(state)));
        },
        [](uint16_t state) -> uint16_t{
            MSTRotate rotate;
            return rotate.revert(rotate.revert(rotate.revert(state)));
        }
    },
    //Transform 8 : mirror -> rotate -> rotate -> rotate
    {
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            MSTRotate rotate;
            return rotate.transform(rotate.transform(rotate.transform(mirror.transform(state))));
        },
        [](uint16_t state) -> uint16_t{
            MSTMirror mirror;
            MSTRotate rotate;
            return mirror.revert(rotate.revert(rotate.revert(rotate.revert(state))));
        }
    },



};
