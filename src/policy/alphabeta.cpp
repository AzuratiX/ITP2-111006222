#include <cstdlib>
#include "../state/state.hpp"
#include "./alphabeta.hpp"
#include "alphabeta.hpp"
#include <limits>

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBeta::get_move(State *state, int depth){

  int alpha = std::numeric_limits<int>::min();
  int beta = std::numeric_limits<int>::max();

  if(!state->legal_actions.size()){
    state->get_legal_actions();
  }

  Move goodMove;

  if(!state->player){
    int max = -100000;

    for(const auto& i : state->legal_actions){
      State* child = state->next_state(i);
      int value = pruning(child, depth-1, alpha, beta, false);

      if(value > max){
        max = value;
        goodMove = i;
      }
    }
    return goodMove;
  }

  else{
    int min = 100000;

    for(const auto& i : state->legal_actions){
      State* child = state->next_state(i);
      int value = pruning(child, depth-1, alpha, beta, true);

      if(value < min){
        min = value;
        goodMove = i;
      }
    }
    return goodMove;
  }
}

int AlphaBeta::pruning(State *node, int depth, int alpha, int beta, bool maximizingPlayer){

  if(depth == 0 || node->legal_actions.empty()){
    return node->evaluate();
  }
  
  if(maximizingPlayer){
    int value = -100000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    for(const auto& child : node->legal_actions){
      State *new_state = node->next_state(child);
      int score = pruning(new_state, depth - 1, alpha, beta, false);
      value = std::max(value,score);
      alpha = std::max(alpha,value);

      if(alpha >= beta){
        break;
      }
    }
    return value;
  }

  else{
    int value = 100000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    for(const auto& child : node->legal_actions){
      State *new_state = node->next_state(child);
      int score = pruning(new_state, depth - 1, alpha, beta, true);
      value = std::min(value,score);
      beta = std::min(beta,value);

      if(beta <= alpha){
        break;
      }
    }
    return value;
  }
}

