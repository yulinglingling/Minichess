#include <iostream>

#include <fstream>
#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int minimax(State *state, int depth, int maximize){
  auto actions = state->legal_actions;
  int sz = actions.size();
  
  if(depth == 0 || !sz){
    return state -> evaluate();
  }

  int val = -1e9;
  for(size_t i = 0; i < sz; i++){
    State *s = state -> next_state(actions[i]);
    int tmp = minimax(s, depth - 1, 0 - maximize) * maximize;
    val = std::max(tmp, val);
  }
  return val * maximize;

}

Move Minimax::get_move(State *state, int depth, int player){
  
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;

  int sz = actions.size();
  
  int val = INT_MIN, ans = 0;
  for(size_t i = 0; i < sz; i++){
    State *s = state -> next_state(actions[i]);
    int tmp = minimax(s, depth - 1, (0 - player)) * player;
    if(tmp > val) val = tmp, ans = i;
  }
  return actions[ans];

}





