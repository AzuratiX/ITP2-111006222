#include <cstdlib>
#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size()){
    state->get_legal_actions();
  }

  Move goodMove;

  if(!state->player){
    int max = -100000;
    auto gerak = state->legal_actions;
    for(const auto& i : gerak){
      State* child = state->next_state(i);
      int value = minimax(child, depth-1, false);

      if(value > max){
        max = value;
        goodMove = i;
      }
    }
    return goodMove;
  }

  else{
    int min = 100000;
    auto gerak = state->legal_actions;
    for(const auto& i : gerak){
      State* child = state->next_state(i);
      int value = minimax(child, depth-1, true);

      if(value < min){
        min = value;
        goodMove = i;
      }
    }
    return goodMove;
  }
  
}

int Minimax::minimax(State *node, int depth, bool maximizingPlayer){
  if(depth == 0 || node->legal_actions.empty()){
    return node->evaluate();
  }
  
  if(maximizingPlayer){
    int value = -100000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    auto gerak = node->legal_actions;
    for(const auto& child : gerak){
      State *new_state = node->next_state(child);
      int score = minimax(new_state, depth - 1, false);
      value = std::max(value,score);
    }
    return value;
  }

  else{
    int value = 100000;
    if(!node->legal_actions.size()){
      node->get_legal_actions();
    }
    auto gerak = node->legal_actions;
    for(const auto& child : gerak){
      State *new_state = node->next_state(child);
      int score = minimax(new_state, depth - 1, true);
      value = std::min(value,score);
    }
    return value;
  }
}
