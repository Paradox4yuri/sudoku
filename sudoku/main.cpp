#include "lib.h"
#include<iostream>

using namespace std;

int main(){
    Game game;
    game.start();
    int option;

    while(cin>>option){
        bool exitFlag = game.action(option);    // if exit game, Game::action will return false
        if(!exitFlag)
            break;
    }
    return 0;
}
