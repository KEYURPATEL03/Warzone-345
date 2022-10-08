//written by keyur patel
#include <iostream>
#include <string>
#include <sstream>
#include "GameEngine.H"

GameEngine :: GameEngine():command(""),state(0),numOfMaps(0),numOfPlayer(0),partHandler(false){
    
}

GameEngine::GameEngine(const GameEngine& p)
{
    command = p.command;
    state = p.state;
    numOfMaps = p.numOfMaps;
    numOfPlayer = p.numOfPlayer;
    partHandler = p.partHandler;
}

GameEngine& GameEngine :: operator=(const GameEngine& p) //##??
{
    command = p.command;
    state = p.state;
    numOfMaps = p.numOfMaps;
    numOfPlayer = p.numOfPlayer;
    partHandler = p.partHandler;
    return *this;

}

void GameEngine :: start(){
    state = 0 ;

    cout<<"\n\n ## Welcome to the GAME ##\n\n";
    cout<<"\"Current-State: start\"\n";
    cout<< "WARNING! Every command typed MUST be<lower-case> !!!!"<<endl;
    cout<< "please type (loadmap) to load map and play the game" << endl;
    cout<< "There exist a default map, Which will be automatically loaded if you start to play." <<endl;
    cin>>this->command;
    if(command=="loadmap"){
        state=1;
    }
    else{
        cout<<"WRONG command entered!"<<endl;
        state=0;

    }
    partHandler=false;
    cout<<"\n";
}

void GameEngine :: mapLoaded(){
    numOfMaps=numOfMaps+1;
    cout<<"\"Current-State: map loaded\" \nMap has been loaded"<<endl;
    cout<< "Number of maps loaded :" << numOfMaps << " map(s)" <<endl;
    cout<< "To load other map, Please enter(yes)" << endl;
    cout<< "To validated map, Please enter(validate)" << endl;
    cin >> this->command;
    if (command == "yes"){
        state = 1;
    }
    else if (command == "validate"){
        state = 2; 
    }
    else if (command != "validate" && command != "yes"){
        state = 1;
        numOfMaps = numOfMaps - 1;
        cout << "WRONG command!" << endl;
    }
    cout<<"\n";

}

void GameEngine::mapValidated(){
    cout<<"Current-State: map validated.\n";
    cout<<numOfMaps<< " map(s) have been validated" << endl;
    state = 3;
    cout<< "\n" << endl;
}

void GameEngine::playersAdded(){
    cout<<"\"Current-State: players added\"\nPlayers needs to be added"<<endl;
    cout<<"Type (yes) to add a player" <<endl;
    cout<<"Type (no) to finish adding" <<endl;
    cin >> this->command;

    if (command == "yes"){
        numOfPlayer = numOfPlayer + 1;
        cout<<"now a new player has been added, you have "<< numOfPlayer << " player(s) right now" <<endl;
        state = 3;
        partHandler = false;
    }
    if(command == "no"){
        state = 4;
        partHandler = true;
    }
    if (numOfPlayer == 0){
        cout<<"you can not play the game without any players!!"<<endl;
        state = 3;
    }
    if (command != "yes" && command !="no"){
        state = 3;
        cout << "wrong command! " << endl;
    }
    cout<< "\n" << endl;
}

void GameEngine::assignReinforcement(){
    cout << "\"Current-State: assign reinforcement\"\nCountries has been assigned " <<endl;
    cout << "Assign reinforcement has been finished" << endl;
    cout << "issuing orders !!" << endl;
    state = 5;
    cout<< "\n" << endl;
}

void GameEngine::issueOrders(){
    cout << "\"Current-State:issue orders\"\norder has been issued" <<endl;
    cout << "Type (yes) for re-issue the order" <<endl;
    cout << "Type (no) for going executed order" <<endl;
    cin >> this->command;
    if (command == "yes"){
        cout << "comfirmed!" << endl;
        cout << "would you like to issue other order?" << endl;
        cout << "Type (yes) for issuing another order, Else enter (no) for execution" <<endl;
        cin >> this->command;
        if (command == "yes"){
            state = 5;
        }
        else if (command == "no"){
            state = 6;
        }
        else if (command != "yes" && command !="no"){
            state = 5;
            cout << "wrong command!" << endl;
        }
    }
    else if (command == "no"){
        cout << "comfirmed!" << endl;
        cout << "going to execute orders" << endl;
        state = 6;
    }
    else if (command != "yes" && command !="no"){
        state = 5;
        cout << "wrong command!" << endl;
    }
    cout<< "\n" << endl;
}

void GameEngine::executeOrders(){
    cout << "\"Current-State: execute orders\"\norders have been executed!" <<endl;
    cout << "Choose to win the game or not!" <<endl;
    cout << "Type (win) for winning" <<endl;
    cout << "Type (execute) for re-execute order!" <<endl;
    cout << "Type (assignreinforce) for re-assign reinforcement!" <<endl;
    cin >> this->command;
    if (command == "win"){
        state = 7;
    }
    if (command == "execute"){
        state = 6;
    }
    if (command == "assignreinforce"){
        state = 4;
    }
    else if (command != "win" && command !="execute" && command !="assignreinforce"){
        state = 6;
        cout << "wrong command!" << endl;
    }
    cout<< "\n" << endl;
}

void GameEngine::win(){
    cout << "\"Current-State: win\"\nYour enemy has beed defeated, You won! \n\t ****** WINNER WINNER ****** \t\n" << endl;
    cout << "Do you want to play again ?" << endl;
    cout << "Type (yes) for play again" << endl;
    cout <<  "Type any other command besides (yes) to end " << endl;
    cin >> this->command;
    if (command == "yes"){
        state = 0;
        cout << "Resetting the Game!" << endl;
        numOfMaps = 0;
        numOfPlayer = 0;
    }

    else {
        cout << "Thank you for playing this game!!!";
        state = 8; 
    }
    partHandler = false;
    cout<< "\n" << endl;
}

void GameEngine::startup(){
    while(state == 0){
        start();
    }
    while(state == 1){
        mapLoaded();
    }
    while(state == 2){
        mapValidated();
    }
    while(state == 3){
        playersAdded();
    }
}

void GameEngine::play(){
        while(state == 4)
        {
            assignReinforcement();
        while(state == 5){
            issueOrders();
        }
        while(state == 6){
            executeOrders();
        }
        while(state == 7){
            win();
        }
    }
}

void GameEngine::testGameStates(){
    partHandler = false;
    state = 0;
    while(partHandler == false && state == 0){
        startup();
            while(partHandler == true && state == 4){
            play();
        }
    }


}

int main(){
    GameEngine test;
    test.testGameStates();

    return 0;
}



