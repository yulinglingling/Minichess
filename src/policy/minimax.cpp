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
const std::string file_log = "getmove.txt";

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


int minimax(State *state, int depth, int maximize){
  auto actions = state->legal_actions;
  int val = 0;
  if(depth == 0){
    return state -> evaluate();
  }
  if(maximize){
    val = INT_MIN;
    for(size_t i = 0; i < actions.size(); i++){
      State *s = state -> next_state(actions[i]);
      int tmp = minimax(s, depth - 1, 0);
      if(tmp > val) val = tmp;
      if(val == INT_MAX) return val; 
    }
  }else if(!maximize){
    val = INT_MAX;
    for(size_t i = 0; i < actions.size(); i++){
      State *s = state -> next_state(actions[i]);
      int tmp = minimax(s, depth - 1, 1);
      if(tmp < val) val = tmp;
      if(val == INT_MIN) return val;
    }
  }
  return val;
}

Move Minimax::get_move(State *state, int depth){
  std::ofstream log("getmove.txt");
  log << "getmove " << state -> player << '\n';
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int val = 0, ans = 0;
  
  if(state -> player){
    val = INT_MAX;
    for(size_t i = 0; i < actions.size(); i++){
      State *s = state -> next_state(actions[i]);
      int tmp = minimax(s, depth - 1, 1);
      //int tmp = alphabelta(s, depth - 1, INT_MIN, INT_MAX, 1);
      if(tmp < val) val = tmp, ans = i;
      if(val == INT_MIN) return actions[i];
    }
  }else if(!state -> player){
    val = INT_MIN;
    for(size_t i = 0; i < actions.size(); i++){
      State *s = state -> next_state(actions[i]);
      int tmp = minimax(s, depth - 1, 0);
      //int tmp = alphabelta(s, depth - 1, INT_MIN, INT_MAX, 0);
      if(tmp > val) val = tmp, ans = i;
      if(val == INT_MAX) return actions[i];
    }
  }
  
  return actions[ans];
}




