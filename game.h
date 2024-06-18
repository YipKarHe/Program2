#ifndef GAME_H
#define GAME_H

#include "Racer.h"
#include <string>
using namespace std;

class Game {
public:
    Game();
    void mainMenu();
    void playMenu();
    void displayTrack();
    void playRound(int round);

private:
    Racer xwing, tiefighter, soullessone;
    int raceRounds, turnOfRace, option, players, xw, yw, zw;
    float bet;
    string racer1;
    int boostAmount, gunAmount, swapAmount;

    void playerMove();
    void useItem();
    void getItem();
    void aiMove();
    bool isRaceOver();
    void displayResults();
    void assignRacerSymbol(char track[][45], char symbol, int position, int height, int width);
};

#endif // GAME_H
