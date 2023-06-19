#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Smart{
public:
  static Move get_move(State *state, int depth);
  //static int minimax(State *state, int depth, int maximize);
};