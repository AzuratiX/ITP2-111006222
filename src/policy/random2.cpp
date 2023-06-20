#include <cstdlib>
#include "../state/state.hpp"
#include "./random2.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Random2::get_move(State *state, int depth){
if(!state->legal_actions.size()){
    state->get_legal_actions();
}
    auto actions = state->legal_actions;
    int maxVal = -10000000;
    Move flag;

    for(auto go : actions){
        State* new_state = state->next_state(go);
        int check = new_state->evaluate();

        if(check > maxVal){
            maxVal = check;
            flag = go;
        }
    }
    return flag;
}

