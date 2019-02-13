#ifndef GAME.H
#define GAME.H
#include <string>
#include <vector>

class Game{
public:
    Game();
    static void printMenu();
    static void printRules();
    void drawHangman();
    void play();
    void gameOver();

private:
    int countWrongGuesses;
    std::string secretWord;
    std::vector<char> playerWordProgress;
    std::vector<char> missedLetters;
};
#endif // GAME
