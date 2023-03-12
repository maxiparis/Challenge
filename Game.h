//
// Created by Maximiliano París Gaete on 3/11/23.
//

#ifndef PROGRAMMING_CHALLENGE_GAME_H
#define PROGRAMMING_CHALLENGE_GAME_H
#include "Word.h"
#include <set>
#include <vector>
#include <map>

#include "Hangman.h"
using namespace std;

class Game {
private:
    Hangman myHangman = Hangman();
    string word;
    int GuessesLeft = 0;
    int numberOfGuesses = 0;
    char guessedLetter;
    set <char> wrongGuesses;
    vector <char> correctGuesses; //it allows duplicates
//    multimap<int, string> correctGuesses;




public:
    /**
     * Creates a new Game
     * @param word the word that the user will have to guess.
     */
    explicit Game(const string &word) : word(word) {
        GuessesLeft = word.size()*3;
    }

    /**
     * Tells the user he won or guessed the word.
     */
    void winnerGame() {
        cout << " ====================\n"
                "**** You WON THE GAME **** \n"
                "It took you " << numberOfGuesses << " guesses in total. \n" << endl;
    }
    /**
     * Tells the user he failed, because he could not guess.
     */
    void runOutOfGuesses() {
        cout << myHangman.printLost() << endl;
        cout << " ====================\n"
                "**** You LOST THE GAME **** \n" << endl;
    }

    /**
     * if the user guessed the word then the function winnerGame() is called. Otherwise, he missed his guesses.
     */
    void finishGame() {
        if (guessedWord() == word){
        winnerGame();
        } else {
            runOutOfGuesses();
        }

    }

    void welcome() {//I took this text from https://ascii.co.uk/text, I am not sure if it was allowed but i thought it was kinda cool.

        cout << "***************************\n"
                "Welcome to the\n"
                " ___  ___  ________  ________   ________  _____ ______   ________  ________\n"
                "|\\  \\|\\  \\|\\   __  \\|\\   ___  \\|\\   ____\\|\\   _ \\  _   \\|\\   __  \\|\\   ___  \\\n"
                "\\ \\  \\\\\\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\ \\  \\___|\\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\\\ \\  \\\n"
                " \\ \\   __  \\ \\   __  \\ \\  \\\\ \\  \\ \\  \\  __\\ \\  \\\\|__| \\  \\ \\   __  \\ \\  \\\\ \\  \\\n"
                "  \\ \\  \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\|\\  \\ \\  \\    \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \n"
                "   \\ \\__\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\ \\__\\    \\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\\n"
                "    \\|__|\\|__|\\|__|\\|__|\\|__| \\|__|\\|_______|\\|__|     \\|__|\\|__|\\|__|\\|__| \\|__|\n"
                "***************************" << endl;

    }

/**
     * Starts the game, with an introductory message, tells the user the length of the word and ask for letters
     * The user will be asked until he guesses all the letters in the word or until he does not have more chances.
     * After that the game will finish.
     */
    void startGame(){
        welcome();
        cout << "Your word has " << getWord().size() << " letters." << endl;

        do{
            askForLetter();
            GuessesLeft--;
            cout << "You have " << GuessesLeft << " guesses left. " << endl;
        } while (guessedWord() != word && GuessesLeft > 0); // i can keep playing as long as i have more guesses or I havent guessed yet.

        finishGame();


    }

    /**
     * Compares each letter in the word with each letter in the vector of correctGuesses.
     * If the word is in the vector, then it will be displayed in the correct position, otherwise, a dash will be displayed.
     *
     * @return an string with all the guessed letters, in the correct position. All other not-guessed letters will be replaced
     * with a dash.
     */
    string guessedWordWithDashes() {
        string r;
        bool guessed;
        for (int i = 0; i<word.size() ; i++){
            guessed = false;
            for (int e = 0; e<correctGuesses.size(); e++){
                if (correctGuesses.at(e) == word.at(i)) {
//                    r += word.at(i);
                    guessed = true;
                }
            }
            if(guessed) {
                r += word.at(i);
            } else {
                r += "-";
            }
        }
        return r;
    }

    /**
     * Displays the correct words the user has guessed.
     */
    void displayCorrect() {
        numberOfGuesses++;
        cout << "\nCorrect! Guessed word so far: " << guessedWordWithDashes() << endl;
    }
    /**
     * Displays all the wrong guesses. It will not be duplicated and it will be in alphabetical order.
     */
    void displayIncorrect() {
        string wrong;
        cout << "\nIncorrect!. Incorrect words you have used so far: " << endl;
        for (auto it = wrongGuesses.begin(); it !=wrongGuesses.end(); ++it) {
            cout << ' ' << *it;
        }
        numberOfGuesses++;

        cout << myHangman.printHangman(numberOfGuesses, word.size()) << endl;
        cout << endl;


    }

    /**
     * Asks the user for a letter to guess. Then the input is passed as a parameter to check if the it is a correct guess.
     *
     */
    void askForLetter() {
        cout << "Please guess a letter:" << endl;
        cin >> guessedLetter;
        if(isLetterInside(guessedLetter)){
            displayCorrect();
        } else {
            displayIncorrect();

        }
//        numberOfGuesses++;
    }

    /**
     *
     * @return the correct guesses in order but missing dashes (a little bit hard to see what letter
     * is missing)
     */
    string guessedWord(){
        string r;
        for (int i = 0; i<word.size() ; i++){
            for (int e = 0; e<correctGuesses.size(); e++){
                if (correctGuesses.at(e) == word.at(i)) {
                    r += word.at(i);
                }
            }

        }
        return r;
    }

    /**
     * Checks if the letter is already in the vector of correctGuesses.
     * If is not then is added, if is then is not added. Avoids duplicates.
     *
     * @param letter the user guess
     * @return true, if the user input is already in the vector (duplicated)
     * false, if is not in the vector.
     */
    bool isAlreadyInVector(char letter) {
        for (int i = 0; i < correctGuesses.size(); ++i) {
            if (correctGuesses.at(i) == letter) { return true;}
        }
        return false;
    }

    /**
     * Checks if the letter or the guess by the user is correct is part of the word.
     * @param letter The guess by the user.
     * @return true if the guess is correct, false if not.
     */
    bool isLetterInside(char letter){
        for (int i = 0; i < word.size(); ++i) {
            if (word.at(i) == letter) {
                if(isAlreadyInVector(letter)){
                    return true;
                } else {
                    correctGuesses.push_back(letter);
                    return true;
                }

            };
        }
        wrongGuesses.insert(letter);
        return false;
    }

    /**
     * Gets the word to guess.
     * @return the word to guess.
     */
    const string &getWord() const {
        return word;
    }

};



#endif //PROGRAMMING_CHALLENGE_GAME_H
