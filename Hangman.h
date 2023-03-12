//
// Created by Maximiliano París Gaete on 3/11/23.
//

#ifndef PROGRAMMING_CHALLENGE_HANGMAN_H
#define PROGRAMMING_CHALLENGE_HANGMAN_H

#include <string>

using namespace std;

class Hangman {
private:
    string five =
                "\n_______ \n"
                "|      | \n"
                "|      |\n"
                "|      |\n"
                "|      o\n"
                "|     /|\\ \n"
                "|      | \n"
                "|      \n"
                "|           \n"
                "______________";

    string four =
            "\n_______ \n"
            "|      | \n"
            "|      |\n"
            "|      |\n"
            "|      o\n"
            "|     /|\\ \n"
            "|       \n"
            "|      \n"
            "|           \n"
            "______________";

    string three =
            "\n_______ \n"
            "|      | \n"
            "|      |\n"
            "|      |\n"
            "|      o\n"
            "|     /| \n"
            "|       \n"
            "|      \n"
            "|           \n"
            "______________";

    string two =
            "\n_______ \n"
            "|      | \n"
            "|      |\n"
            "|      |\n"
            "|      o\n"
            "|     / \n"
            "|       \n"
            "|      \n"
            "|           \n"
            "______________";

    string one =
            "\n_______ \n"
            "|      | \n"
            "|      |\n"
            "|      |\n"
            "|      o\n"
            "|      \n"
            "|       \n"
            "|      \n"
            "|           \n"
            "______________";

    string zero =
            "\n_______ \n"
            "|      | \n"
            "|      |\n"
            "|      |\n"
            "|      o\n"
            "|     /|\\ \n"
            "|      | \n"
            "|     / \\\n"
            "|           \n"
            "______________";








public:
    Hangman(){};

    const string &getZero() const {
        return zero;
    }

    const string &getOne() const {
        return one;
    }

    const string &getTwo() const {
        return two;
    }

    const string &getThree() const {
        return three;
    }

    const string &getFour() const {
        return four;
    }

    const string &getFive() const {
        return five;
    }

    /**
     *
     * @return the last state of the hangman, fully drawn.
     */
    string printLost(){
        return getZero();
    }

    /**
     * Calculates how much of the total guesses have been made. If 80 percent of the total guesses have been made,
     * then it returns five, and so on.
     * @param guesses the number of guesses the user has made (whether it was correct or wrong).
     * @param totalGuesses the total guesses the user is given to make.
     * @return a string with the corresponding hangman drawing to display.
     */
    string printHangman(int guesses, int totalGuesses){
        double newTotalGuesses = (double)totalGuesses * 3;
        double percent = (double(guesses)/newTotalGuesses)*100;


        if (percent > 80){
            return getFive();
        } else if (percent > 60){
            return getFour();
        }else if (percent > 40){
            return getThree();
        }else if (percent > 20){
            return getTwo();
        } else {
            return getOne();
        }
    }



};
#endif //PROGRAMMING_CHALLENGE_HANGMAN_H
