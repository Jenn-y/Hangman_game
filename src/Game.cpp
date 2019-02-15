#include "Game.h"
#include <iostream>
#include <string>
#include <vector>

Game::Game(){
    countWrongGuesses = 0;
}
void Game::printMenu(){
    std::cout << R"(
                                      _________________________
                                     |                         |
                                     |       MAIN MENU         |
                                     |      -----------        |
                                     |                         |
                                     |       ~Hangman~         |
                                     |                         |
                                     |      1. Play            |
                                     |      2. How to play     |
                                     |      3. Exit the game   |
                                     |_________________________|

                       )" << "\nPlease choose option 1, 2 or 3 --> ";
     int option;
     std::cin >> option;
     while (option < 1 || option > 3){
        std::cout << "Please choose option 1, 2 or 3: ";
        std::cin >> option;
     }
     switch (option){
         case 1: Game().play(); break;
         case 2: printRules(); break;
         case 3: std::cout << "\n\t\t\t\t--> You have chosen to exit the game <--\n"; return;
     }
}
void Game::printRules(){
    std::cout << R"(
                           __________________________________________________
                          |                                                  |
                          |               ~ABOUT THE GAME~                   |
                          |                                                  |
                          | Hangman is a quick and easy game for at least    |
                          | two people that requires only the ability to     |
                          | spell. One player, the "host", makes up a secret |
                          | word, while the other player(s) guess(es) the    |
                          | word by the letters it contains.                 |
                          |                                                  |
                          |                ~INSTRUCTIONS~                    |
                          |                                                  |
                          | 1. Choose one person to be the "host"            |
                          | 2. Host enters a secret word                     |
                          | 3. Player(s) start(s) guessing letters           |
                          | 4. Player(s) may only miss 6 times               |
                          | 5. If the total number of wrong guesses is 6,    |
                          |    game is over - the "host" wins. On the other  |
                          |    hand, if the player(s) guess(es) the secret   |
                          |    word - win goes to the player(s)              |
                          | 6. The player(s) may attempt to guess the whole  |
                          |    word after two correct letter guesses. If it  |
                          |    is a wrong guess, it adds up to the total     |
                          |    number of wrong guesses                       |
                          |__________________________________________________|
                    )" << "\nPress 1 to return to the menu, and 2 to exit the game --> ";
    int option;
    std::cin >> option;
    while (option < 0 || option > 2){
        std::cout << "Press 1 to return to the menu, and 2 to exit the game --> ";
        std::cin >> option;
    }
    switch(option){
        case 1: printMenu(); break;
        case 2: std::cout << "\n\t\t\t\t--> You have chosen to exit the game <--\n"; return;
    }
}
void Game::drawHangman(){
    std::cout << " +---+\n";
    std::cout << " |   |\n";
    std::cout << " |   ";
    if (countWrongGuesses > 0) std::cout << "O";
    std::cout << "\n |  ";
    if (countWrongGuesses > 4) std::cout << "/";
    else std::cout << " ";
    if (countWrongGuesses > 1) std::cout << "|";
    if (countWrongGuesses > 5) std::cout << "\\";
    std::cout << "\n |  ";
    if (countWrongGuesses > 2) std::cout << "/";
    else std::cout << " ";
    if (countWrongGuesses > 3) std::cout << " \\";
    std::cout << "\n |\n";
    std::cout << "_|_\n";
}
void Game::play(){
    std::cout << "\nYou are chosen as a host!\nEnter your secret word and make sure other players do not see it --> ";
    // clears the buffer so that getline works properly
    std::cin.ignore();
    std::getline(std::cin, secretWord);
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    drawHangman();
    std::cout << "\n";
    // stores just letters in secretWord as _ and counts the number of letters to be guessed
    int countLetters = 0;
    for (int i = 0; i < secretWord.length(); i++)
        if (isalpha(secretWord.at(i))) {
            secretWord.at(i) = tolower(secretWord.at(i));
            playerWordProgress.push_back('_');
            countLetters++;
            }
        else playerWordProgress.push_back(secretWord.at(i));
    for (int i = 0; i < playerWordProgress.size(); i++) std::cout << playerWordProgress[i] << " ";
    std::cout << "\nNow we are all set - it is time to play the game!\n";
    char userGuess;
    int correctGuess = 0;
    do{
        // displays prompt to guess compete word when the players have
        // guessed more than two letters
        if (correctGuess > 2){
            std::cout << "\n\nWould you like to guess complete word? (y/n) ";
            std::cin >> userGuess;
            if (tolower(userGuess) == 'y'){
                std::cout << "Enter word: ";
                std::string word;
                std::cin.ignore();
                std::getline(std::cin, word);
                if (word == secretWord) gameOver();
                else {
                    std::cout << "Sorry! That is not the secret word!";
                    countWrongGuesses++;
                }
            }
        }
        std::cout << "\n\nPlayer, enter your guess: ";
        std::cin >> userGuess;
        userGuess = tolower(userGuess);
        bool in = false; // checks whether the word contains the letter
        for (int i = 0; i < secretWord.length(); i++){
            if (isalpha(userGuess) && secretWord.at(i) == userGuess){
                in = true;
                if (playerWordProgress[i] == userGuess){
                        std::cout << userGuess << " is already in the word\n";
                        break;
                }
                else {
                    playerWordProgress[i] = userGuess;
                    correctGuess++;
                }
            }
        }
        if (!in && isalpha(userGuess)){
            std::cout << userGuess << " is not in the word\n";
            countWrongGuesses++;
            bool isRepeating = false;
            // checks whether the letter is already stored as wrong guess
            for (int i = 0; i < missedLetters.size(); i++)
                if (userGuess == missedLetters[i]) isRepeating = true;
            if (!isRepeating) missedLetters.push_back(userGuess);
        }
        drawHangman(); std::cout << "\n";
        for (int i = 0; i < secretWord.length(); i++) std::cout << playerWordProgress[i] << " ";
        std::cout << "\n\nMissed letter guesses so far: ";
        if (missedLetters.empty()) std::cout << "none";
        else for (int i = 0; i < missedLetters.size(); i++) std::cout << missedLetters[i] << " ";
        if (countWrongGuesses == 6) gameOver();
    }while (correctGuess != countLetters);
    gameOver();
  }
void Game::gameOver(){
    std::cout << "\n\n\n\t\t\t\t\t    ~GAME OVER~\n\n\t\t";
    if (countWrongGuesses == 6) std::cout << "You have not guessed the secret word. The secret word is "
                                          << secretWord << ". - HOST WINS! CONGRATULATIONS!\n";
    else std::cout << "You have guessed the secret word. - WIN GOES TO THE PLAYER(S)! CONGRATULATIONS!\n";
    std::cout << "\n\t\t\t\t\tThank you for playing!\n";
    printMenu();
}
