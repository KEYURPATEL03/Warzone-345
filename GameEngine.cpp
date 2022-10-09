//written by keyur patel
#include <iostream>
#include <string>
#include <sstream>
#include "GameEngine.H"
//default constructor
GameEngine :: GameEngine():command(""),state(0),numOfMaps(0),numOfPlayer(0),partHandler(false){
    
}
//copy constructor
GameEngine::GameEngine(const GameEngine& p) 
{
    command = p.command;
    state = p.state;
    numOfMaps = p.numOfMaps;
    numOfPlayer = p.numOfPlayer;
    partHandler = p.partHandler;
}

GameEngine& GameEngine :: operator=(const GameEngine& p) 
{
    command = p.command;
    state = p.state;
    numOfMaps = p.numOfMaps;
    numOfPlayer = p.numOfPlayer;
    partHandler = p.partHandler;
    return *this;

}

void GameEngine :: start(){  //This is the start state
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
//map loaded state
void GameEngine :: mapLoaded(){         
    numOfMaps=numOfMaps+1;
    cout<<"\"Current-State: map loaded\" \nMap has been loaded"<<endl;
    cout<< "Number of maps loaded :" << numOfMaps << " map(s)" <<endl;
    cout<< "To load other map, Please type(loadmap)" << endl;
    cout<< "To validated map, Please enter(validatemap)" << endl;
    cin >> this->command;
    if (command == "loadmap"){
        state = 1;
    }
    else if (command == "validatemap"){
        state = 2; 
    }
    else if (command != "validatemap" && command != "loadmap"){
        state = 1;
        numOfMaps = numOfMaps - 1;
        cout << "WRONG command!" << endl;
    }
    cout<<"\n";

}
//map validated state , in next iterations of the game map will be validated here
void GameEngine::mapValidated(){
    cout<<"Current-State: map validated.\n";
    cout<<numOfMaps<< " map(s) have been validated" << endl;
    state = 3;
    cout<< "\n" << endl;
}
//player added state 
void GameEngine::playersAdded(){
    cout<<"\"Current-State: players added\"\nPlayers needs to be added"<<endl;
    cout<<"Type (addplayer) to add a player" <<endl;
    cout<<"Type (assigncountries) to finish adding and assign countries!" <<endl;
    cin >> this->command;

    if (command == "addplayer"){
        numOfPlayer = numOfPlayer + 1;
        cout<<"now a new player has been added, you have "<< numOfPlayer << " player(s) right now" <<endl;
        state = 3;
        partHandler = false;
    }
    if(command == "assigncountries"){
        state = 4;
        partHandler = true;
    }
    if (numOfPlayer == 0){
        cout<<"you can not play the game without any players!!"<<endl;
        state = 3;
    }
    if (command != "addplayer" && command !="assigncountries"){
        state = 3;
        cout << "wrong command! " << endl;
    }
    cout<< "\n" << endl;
}
// Play part , assign reinforcement state
void GameEngine::assignReinforcement(){
    cout << "\"Current-State: assign reinforcement\"\nCountries has been assigned " <<endl;
    cout << "Assign reinforcement has been finished" << endl;
    cout << "issuing orders !!" << endl;
    state = 5;
    cout<< "\n" << endl;
}
// issue order state
void GameEngine::issueOrders(){
    cout << "\"Current-State:issue orders\"\norder has been issued" <<endl;
    cout << "Type (issueorder) for re-issue the order" <<endl;
    cout << "Type (endissueorders) for execute orders" <<endl;
    cin >> this->command;
    if (command == "issueorder"){
        cout << "comfirmed!" << endl;
        cout << "would you like to issue other order?" << endl;
        cout << "Type (issueorder) for issuing another order, Else enter (endissueorder) for execution" <<endl;
        cin >> this->command;
        if (command == "issueorder"){
            state = 5;
        }
        else if (command == "endissueorder"){
            state = 6;
        }
        else if (command != "issueorder" && command !="endissueorder"){
            state = 5;
            cout << "wrong command!" << endl;
        }
    }
    else if (command == "endissueorder"){
        cout << "comfirmed!" << endl;
        cout << "going to execute orders" << endl;
        state = 6;
    }
    else if (command != "issueorder" && command !="endissueorder"){
        state = 5;
        cout << "wrong command!" << endl;
    }
    cout<< "\n" << endl;
}
//execute order state
void GameEngine::executeOrders(){
    cout << "\"Current-State: execute orders\"\norders have been executed!" <<endl;
    cout << "Choose to win the game or not!" <<endl;
    cout << "Type (win) for winning" <<endl;
    cout << "Type (execoder) for re-execute order!" <<endl;
    cout << "Type (endexecoders) for re-assign reinforcement!" <<endl;
    cin >> this->command;
    if (command == "win"){
        state = 7;
    }
    if (command == "execoder"){
        state = 6;
    }
    if (command == "endexecoders"){
        state = 4;
    }
    else if (command != "win" && command !="execoder" && command !="endexecoders"){
        state = 6;
        cout << "wrong command!" << endl;
    }
    cout<< "\n" << endl;
}
//win state
void GameEngine::win(){
    cout << "\"Current-State: win\"\nYour enemy has beed defeated, You won! \n\t ****** WINNER WINNER ****** \t\n" << endl;
    cout << "Do you want to play again ?" << endl;
    cout << "Type (play) for play again" << endl;
    cout <<  "Type any other command besides (play) to end " << endl;
    cin >> this->command;
    if (command == "play"){
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
//start part
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
//play part
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
// function to check the current state of the game
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



