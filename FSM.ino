#include "FSM.h"

void initFSM(){
    // TODO Initialize pins used in state machine
}

FSMState nextStateFunction(FSMState currentState){
    // Log the current state
    Serial.print("Current state: ");
    Serial.println(currentState);

    if(currentState == sleep){

    }
    else if(currentState == poll){

    }
    else if(currentState == detected){

    }
    else if(currentState == snooze){

    }
    else if(currentState == transition){

    }
    else{

    }
}

void outputStateFunction(FSMState currentState){
    if(currentState == sleep){
        
    }
    else if(currentState == poll){

    }
    else if(currentState == detected){

    }
    else if(currentState == snooze){

    }
    else if(currentState == transition){

    }
    else{

    }
}