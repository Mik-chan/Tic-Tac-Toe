//
//  MenacePlayer.hpp
//  Tic-Tac-Toe
//
//  Created by George Endo on 28.06.2019.
//  Copyright © 2019 George Endo. All rights reserved.
//

#ifndef MenacePlayer_hpp
#define MenacePlayer_hpp

#include <map>
#include <vector>
#include <tuple>
#include <string>
#include "Player.hpp"

#include "MSTCombined.hpp"

class MenacePlayer : public Player{
public:
    MenacePlayer();
    ~MenacePlayer();
    
    Coordinate decide(const TicTacToe& ttt, TicTacToe::cell_state_t side);
    
    void learn(TicTacToe::game_state_t state, TicTacToe::cell_state_t side);
    
    void save(const std::string& name);
    void load(const std::string& name);
    
private:
    std::map<uint16_t, std::array<uint64_t, 9>> brain;
    std::vector<std::pair<uint16_t, uint16_t>> memory;
    static const std::vector<MSTCombined> transformers;

    size_t weighted_random(const std::array<uint64_t, 9>& weights);
    uint16_t revert_state(uint16_t state) const;
    const MSTCombined& best_transform(uint16_t state) const;
};

#endif /* MenacePlayer_hpp */
