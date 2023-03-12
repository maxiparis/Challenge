#include <iostream>
#include <string>
#include <time.h>

#include "Game.h"


using namespace std;

/**
 * Asks the user if he would like to play again.
 * @return true if user typed yes, false if user typed anything else
 */
bool playAgain(){
    string userInput;
    cout << "Would you like to try again? (answer yes or no):" << endl;
    cin >> userInput;
    if (userInput == "yes"){
        return true;
    } else {
        cout << "Thank you for playing!! " << endl;
        return false;
    }

}

int main() {

    string words[10] = {"spider", "eating", "house", "bottle",
                        "honey", "pencil", "lamp",
                        "switch", "kitchen", "table" };

    srand (time(NULL));


    do {
        int randomNumber = rand() % 10;
        string randomWord = words[randomNumber];
        Game myGame = Game(randomWord);
        myGame.startGame();
    } while (playAgain());

    return 0;
}
