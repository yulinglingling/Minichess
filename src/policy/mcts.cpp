#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./mcts.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
//const std::string file_log = "getmove.txt";

// int alphabelta(State *state, int depth, int bigger, int smaller, int maximize){
//   auto actions = state->legal_actions;
//   int val = 0;
//   if(depth == 0){
//     return state -> evaluate();
//   }
//   if(maximize){
//     val = INT_MIN;
//     for(size_t i = 0; i < actions.size(); i++){
//       if(bigger >= smaller) break;
//       State *s = state -> next_state(actions[i]);
//       int tmp = alphabelta(s, depth - 1, bigger, smaller, 0);
//       if(tmp > val) val = tmp;
//       if(tmp > bigger) bigger = tmp; 
//       if(val == INT_MAX) return val; 
//     }
//   }else if(!maximize){
//     val = INT_MAX;
//     for(size_t i = 0; i < actions.size(); i++){
//       if(smaller <= bigger) break;
//       State *s = state -> next_state(actions[i]);
//       int tmp = alphabelta(s, depth - 1, bigger, smaller, 1);
//       if(tmp < val) val = tmp;
//       if(tmp < smaller) smaller = tmp;
//       if(val == INT_MIN) return val;
//     }
//   }
//   return val;
// }


float mcts(State *state, int depth, int maximize){
  if(state -> game_state == WIN && !state -> player) return 1;
  if(state -> game_state == WIN && state -> player) return -1;
  if(!depth || !state -> legal_actions.size()){
    return state -> evaluate() / 100000;
  }
  auto actions = state->legal_actions;
  //float val = -1e9;
  //for(size_t i = 0; i < 10000; i++){
  int r = rand() % actions.size();
  State *s = state -> next_state(actions[r]);
  return mcts(s, depth - 1, 0);
  //State *s = state -> next_state(actions[r]);
    //float tmp = mcts(s, depth - 1, 0 - maximize) * maximize;
    //val = std::max(tmp, val);
    //if(val == 1 || val == -1) break;
  //}
  //return val * maximize;


//   if(maximize){
//     val = INT_MIN;
//     for(size_t i = 0; i < actions.size(); i++){
//       State *s = state -> next_state(actions[i]);
//       int tmp = minimax(s, depth - 1, 0);
//       if(tmp > val) val = tmp;
//       //if(val == INT_MAX) return val; 
//     }
//   }else if(!maximize){
//     val = INT_MAX;
//     for(size_t i = 0; i < actions.size(); i++){
//       State *s = state -> next_state(actions[i]);
//       int tmp = minimax(s, depth - 1, 1);
//       if(tmp < val) val = tmp;
//       //if(val == INT_MIN) return val;
//     }
//   }
  //return val;
}

Move MCTS::get_move(State *state, int depth, int player){
  //std::ofstream log("getmove.txt");
  //log << "getmove " << state -> player << '\n';
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  //int val = INT_MIN, ans = 0;
//   for(size_t i = 0 ; i < actions.size(); i++){
//     State *s = state -> next_state(actions[i]);
//     int tmp = minimax(s, depth - 1, 0);
//     if(tmp > val) val = tmp, ans = i;
//     if(tmp == INT_MAX) return actions[i];
//   }
//   return actions[ans];
  float val = -1e9, ans = 0;
  for(size_t i = 0; i < 10000; i++){
    int r = rand() % actions.size();
    State *s = state -> next_state(actions[r]);
    float tmp = mcts(s, depth - 1, (0 - player)) * player;
    if(tmp > val) val = tmp, ans = r;
  }
  return actions[ans];
//   if(state -> player){
//     val = INT_MAX;
//     for(size_t i = 0; i < actions.size(); i++){
//       State *s = state -> next_state(actions[i]);
//       int tmp = minimax(s, depth - 1, 1);
//       //int tmp = alphabelta(s, depth - 1, INT_MIN, INT_MAX, 1);
//       if(tmp < val) val = tmp, ans = i;
//       //if(val == INT_MIN) return actions[i];
//     }
//   }else if(!state -> player){
//     val = INT_MIN;
//     for(size_t i = 0; i < actions.size(); i++){
//       State *s = state -> next_state(actions[i]);
//       int tmp = minimax(s, depth - 1, 0);
//       //int tmp = alphabelta(s, depth - 1, INT_MIN, INT_MAX, 0);
//       if(tmp > val) val = tmp, ans = i;
//       //if(val == INT_MAX) return actions[i];
//     }
//   }
  
    //return actions[ans];
}





