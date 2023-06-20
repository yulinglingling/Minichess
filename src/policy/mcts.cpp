#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include "../state/state.hpp"
#include "./mcts.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

float mcts(State *state, int depth, int maximize){
  if(state -> game_state == WIN && !state -> player) return 1;
  if(state -> game_state == WIN && state -> player) return -1;
  if(!depth || !state -> legal_actions.size()){
    return state -> evaluate() / 10000;
  }
  auto actions = state->legal_actions;
  
  int r = rand() % actions.size();
  State *s = state -> next_state(actions[r]);
  return mcts(s, depth - 1, 0);
  
}

//int now = 0;
Move MCTS::get_move(State *state, int depth, int player){
  
  //std::cout << "now " << now << '\n';
  int cnt = 0;
  for(int i = 0; i < BOARD_H; i++){
    for(int j = 0; j < BOARD_W; j++){
      if(state -> board.board[!state -> player][i][j]) cnt++;
    }
  }
  //int stand = std :: min((10 - cnt) * 0.1 + 0.5, 0.9);
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int sz = actions.size();
   
  float score[50] = {0}, visit[50] = {0};
  
  float val = -1e9;
  int ans = 0, round = 3;
  
  while(val < 0.8 && round > 0){
    std::fill(score, score + sz, 0);
    std::fill(visit, visit + sz, 0);
    //val = -1e9;
    for(size_t i = 0; i < sz * 300; i++){
    
      int r = rand() % sz;
      State *s = state -> next_state(actions[r]);
      float tmp = mcts(s, depth - 1, (0 - player)) * player;
      
      visit[r] += 1, score[r] += (tmp * player);
      //if(tmp > val) val = tmp, ans = r;
    }
    for(int i = 0; i < sz; i++){
      if(score[i] / visit[i] > val) val = score[i] / visit[i], ans = i;
    }
    round--;
  }
  
  return actions[ans];

}







