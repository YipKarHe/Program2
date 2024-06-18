#include <iostream>
#include <algorithm>
#include <ctime> //for generate random number
#include <chrono> //for pause between iteration
#include <thread> //for pause function
#include <iomanip> //for list of bets
using namespace std;
using namespace std::chrono;

// Function to generate random steps within a range for each racer
int generateRandomSteps(int minSteps, int maxSteps) {
    return rand() % (maxSteps - minSteps + 1) + minSteps;
}

class Racer {
public:
    string name;
    int speedMin, speedMax, position;

    Racer(string n, int minSpeed, int maxSpeed) : name(n), speedMin(minSpeed), speedMax(maxSpeed), position(0) {}

    void move() {
        int steps = generateRandomSteps(speedMin, speedMax);
        position += steps;
        cout << name << " moved " << steps << " steps" << endl;
    }

    void useBoost() {
        int steps = generateRandomSteps(speedMin, speedMax);
        position += steps + 2;
        cout << name << " used boost and moved " << steps + 2 << " steps" << endl;
    }
    
    void usegun() {
        int steps = generateRandomSteps(speedMin, speedMax);
        position += steps - 2;
        cout << name << "uses gun on designated racers" << steps - 2 << " steps" << endl;
    }

    
void useswap(int& position1, int& position2) {
    swap(position1, position2);
    cout << "Racers swapped positions" << endl;
}

};


class Game {
public:
    Game() : xwing("X Wing", 2, 4), tiefighter("Tie Fighter", 1, 5), soullessone("Soulless One", 3, 6),
             raceRounds(0), turnOfRace(1), bet(0), players(0), xw(0), yw(0), zw(0), 
             boostAmount(0), gunAmount(0), swapAmount(0) {
        srand(time(0));  // Seed for random number generation
    }

    void mainMenu() {
        cout << "Main Menu" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        if (option == 1) {
            playMenu();
        } else {
            exit(0);
        }
    }

    void playMenu() {
        cout << "Enter your bet: ";
        cin >> bet;
        cout << "Enter number of race rounds: ";
        cin >> raceRounds;
        cout << "Enter number of players: ";
        cin >> players;
        cout << "Choose your racer (X/Y/Z): ";
        cin >> racer1;
        if (players == -1) {
            mainMenu();
        } else {
            for (int round = 1; round <= raceRounds; ++round) {
                playRound(round);
            }
        }
        displayResults();
    }

    void displayTrack() {
        const int width = 45;
        const int height = 17;

        char track[height][width];
        
        char xwing_char = 'x';
        char tiefighter_char = 'y';
        char soullessone_char = 'z';

        //Initialize all to spaces
        for (int i = 0; i < height; i++) // Loop through each row of the track
            for (int j = 0; j < width; j++) // Loop through each column in the current row
                track[i][j] = ' ';

        //Top track
        for (int i = 0; i <= 2; i = i + 2) // Loop through 0 & 2 row of the track
        {
            for (int j = 4; j < width - 1; j = j + 4) // Loop through each 3 column in the current row
            {
                track[i][j] = '+';
                track[i][j + 1] = '-';
                track[i][j + 2] = '-';
                track[i][j + 3] = '-';
            }
            track[i][width - 1] = '+';
        }

        for (int j = 4; j < width; j = j + 4) // Loop through each 3 column in the current row
            track[1][j] = '|';

        //Left and right tracks - vertical lines top part
        for (int i = 3; i < height - 8; i = i + 2) // Loop through between 3 & 12 / each 2 row of the track
        {
            track[i][4] = '|';
            track[i][8] = '|';
            track[i][width - 5] = '|';
            track[i][width - 1] = '|';
            //track design
            track[5][width - 17] = '|';
            track[5][width - 13] = '|';
            track[5][width - 9] = '|';
            track[7][width - 17] = '|';
            track[7][width - 13] = '|';
            track[7][width - 5] = ' ';
            track[7][width - 1] = ' ';
            track[5][8] = '|';
            track[5][12] = '|';
            track[5][16] = '|';
            track[5][20] = '|';
            track[5][24] = '|';
            track[7][12] = '|';
            track[7][16] = '|';
            track[7][20] = '|';
            track[7][24] = '|';
        }
        //Left and right tracks - vertical lines bottom part
        for (int i = 9; i < height - 3; i = i + 2) // Loop through between 3 & 12 / each 2 row of the track
        {
            track[i][0] = '|';
            track[i][4] = '|';
            track[i][width - 5] = '|';
            track[i][width - 9] = '|';
            //track design
            track[9][0] = ' ';
            track[9][4] = ' ';
            track[9][20] = '|';
            track[9][24] = '|';
            track[9][28] = '|';
            track[9][32] = '|';
            track[11][8] = '|';
            track[11][12] = '|';
            track[11][16] = '|';
            track[11][20] = '|';
            track[11][24] = '|';
        }
        //Left track - horizontal lines top part
        for (int i = 4; i < height - 8; i = i + 2) // Loop through between 4 & 12 / each 2 row of the track
        {
            track[i][4] = '+';
            track[i][5] = '-';
            track[i][6] = '-';
            track[i][7] = '-';
            track[i][8] = '+';
            //track design
            track[i][9] = '-';
            track[i][10] = '-';
            track[i][11] = '-';
            track[i][12] = '+';
            track[i][13] = '-';
            track[i][14] = '-';
            track[i][15] = '-';
            track[i][16] = '+';
            track[i][17] = '-';
            track[i][18] = '-';
            track[i][19] = '-';
            track[i][20] = '+';
            track[i][21] = '-';
            track[i][22] = '-';
            track[i][23] = '-';
            track[i][24] = '+';
            track[i][25] = '-';
            track[i][26] = '-';
            track[i][27] = '-';
            track[i][28] = '+';
            track[i][29] = '-';
            track[i][30] = '-';
            track[i][31] = '-';
            track[i][32] = '+';
            track[i][33] = '-';
            track[i][34] = '-';
            track[i][35] = '-';
            track[i][36] = '+';
            track[i][37] = '-';
            track[i][38] = '-';
            track[i][39] = '-';
            track[4][9] = ' ';
            track[4][10] = ' ';
            track[4][11] = ' ';
            track[4][25] = ' ';
            track[4][26] = ' ';
            track[4][27] = ' ';
            track[6][25] = ' ';
            track[6][26] = ' ';
            track[6][27] = ' ';
            track[8][25] = ' ';
            track[8][26] = ' ';
            track[8][27] = ' ';
            track[8][17] = ' ';
            track[8][18] = ' ';
            track[8][19] = ' ';
        }
        //Left track - horizontal lines bottom part
        for (int i = 10; i < height - 3; i = i + 2) // Loop through between 4 & 12 / each 2 row of the track
        {
            track[i][0] = '+';
            track[i][1] = '-';
            track[i][2] = '-';
            track[i][3] = '-';
            track[i][4] = '+';
            //track design
            track[i][5] = '-';
            track[i][6] = '-';
            track[i][7] = '-';
            track[i][8] = '+';
            track[i][9] = '-';
            track[i][10] = '-';
            track[i][11] = '-';
            track[i][12] = '+';
            track[i][13] = '-';
            track[i][14] = '-';
            track[i][15] = '-';
            track[i][16] = '+';
            track[i][17] = '-';
            track[i][18] = '-';
            track[i][19] = '-';
            track[i][20] = '+';
            track[i][21] = '-';
            track[i][22] = '-';
            track[i][23] = '-';
            track[i][24] = '+';
            track[10][28] = '+';
            track[10][29] = '-';
            track[10][30] = '-';
            track[10][31] = '-';
            track[10][32] = '+';
            track[10][33] = '-';
            track[10][34] = '-';
            track[10][35] = '-';
        }
        //Right track - horizontal lines top part
        for (int i = 4; i < height - 10; i = i + 2) // Loop through between 4 & 12 / each 2 row of the track
        {
            track[i][width - 5] = '+';
            track[i][width - 4] = '-';
            track[i][width - 3] = '-';
            track[i][width - 2] = '-';
            track[i][width - 1] = '+';
        }
        //Right track - horizontal lines bottom part
        for (int i = 8; i < height - 3; i = i + 2) // Loop through between 4 & 12 / each 2 row of the track
        {
            track[i][width - 9] = '+';
            track[i][width - 8] = '-';
            track[i][width - 7] = '-';
            track[i][width - 6] = '-';
            track[i][width - 5] = '+';
        }

        //Bottom track
        for (int i = height - 3; i < height; i = i + 2) // Loop through between 12 & 15 / each 2 row of the track
        {
            for (int j = 0; j < width - 5; j = j + 4) // Loop through each 3 column of the track
            {
                track[i][j] = '+';
                track[i][j + 1] = '-';
                track[i][j + 2] = '-';
                track[i][j + 3] = '-';
            }
            track[i][width - 5] = '+';
        }

        for (int j = 0; j < width - 4; j = j + 4) // Loop through each 3 column of the track
            track[height - 2][j] = '|';

        //Assign racer 1 symbol
        assignRacerSymbol(track, xwing_char, xwing.position, height, width);
        //Assign racer 2 symbol
        assignRacerSymbol(track, tiefighter_char, tiefighter.position, height, width);
        //Assign racer 3 symbol
        assignRacerSymbol(track, soullessone_char, soullessone.position, height, width);

        //Display the track
        for (int i = 0; i < height; i++) // Loop through each row of the track
        {
            for (int j = 0; j < width; j++) // Loop through each column of the track
                cout << track[i][j];
            cout << endl;
        }
        cout << endl;
    }

    void playRound(int round) {
        xwing.position = 0;
        tiefighter.position = 0;
        soullessone.position = 0;
        turnOfRace = 1;

        cout << "\nRound " << round << endl;
        displayTrack();

        while (true) {
            int optionc;
            cout << "\n1. Move\n2. Use Item\n3. Get Item\n";
            cout << "Choose an action: ";
            cin >> optionc;

            if (optionc == 1) {
                playerMove();
            } else if (optionc == 2) {
                useItem();
            } else if (optionc == 3) {
                getItem();
            } else {
                cout << "Invalid option. Try again." << endl;
                continue;
            }

            if (isRaceOver()) {
                break;
            }

            aiMove();
            displayTrack();
            turnOfRace++;
        }
    }

private:
    Racer xwing, tiefighter, soullessone;
    int raceRounds, turnOfRace, option, players, xw, yw, zw;
    float bet;
    string racer1;
    int boostAmount, gunAmount, swapAmount;

    void playerMove() {
        if (racer1 == "X" || racer1 == "x") {
            xwing.move();
        } else if (racer1 == "Y" || racer1 == "y") {
            tiefighter.move();
        } else if (racer1 == "Z" || racer1 == "z") {
            soullessone.move();
        }
    }

    void useItem() {
        string item;
        cout << "\nEnter item (boost/gun/swap): ";
        cout << "\nBoost" << setw(10) << boostAmount;
        cout << "\nGun" << setw(10) << gunAmount;
        cout << "\nswap" << setw(10) << swapAmount;
        cin >> item;

        if (item == "boost" && boostAmount > 0) {
            boostAmount--;
            if (racer1 == "X" || racer1 == "x") {
                xwing.useBoost();
            } else if (racer1 == "Y" || racer1 == "y") {
                tiefighter.useBoost();
            } else if (racer1 == "Z" || racer1 == "z") {
                soullessone.useBoost();
            }
        } else if (item == "gun" && gunAmount > 0) {
            gunAmount--;
            string attack;
            cout << "\nWho do you want to use it on?(X,Y,Z)";
            cin >> attack;
            if (attack == "X" || attack == "x"){
                xwing.usegun();
            }
            else if (attack == "y" || attack == "Y"){
            tiefighter.usegun();
            }
            else if (attack == "z" || attack == "Z"){
            soullessone.usegun();
            }
            else{
                cout << "\ninvalid option";
            }
        
        } else if (item == "swap" && swapAmount > 0) {
            swapAmount--;
            int rng = rand() % 101;
            if (racer1 == "x" || racer1 == "X"){
    if (rng <= 50){
        xwing.useswap(xwing.position, tiefighter.position);
        cout << "\nxwing have swap with tiefighter";
    } else if (rng > 50){
        xwing.useswap(xwing.position, soullessone.position);
        cout << "\nxwing have swap with soullessone";
    }
}
else if (racer1 == "y" || racer1 == "Y"){
    if (rng <= 50){
        tiefighter.useswap(tiefighter.position, xwing.position);
        cout << "\ntiefighter have swap with xwing";
    } else if (rng > 50){
        tiefighter.useswap(tiefighter.position, soullessone.position);
        cout << "\ntiefighter have swap with soullesone";
    }
}
else if (racer1 == "z" || racer1 == "Z"){
    if (rng <= 50){
        soullessone.useswap(soullessone.position, tiefighter.position);
        cout << "\nsoullesone have swap with tiefighter";
    } else if (rng > 50){
        soullessone.useswap(soullessone.position, xwing.position);
        cout << "\nsoullesone have swap with xwing";
    }
}

        } else {
            cout << "Invalid item or not enough items. Try again." << endl;
        }
    }
    void getItem() {
        cout << "\nWaste one turn to get items. Confirm? (yes/no): ";
        string confirm;
        cin >> confirm;

        if (confirm == "yes") {
            int rng = rand() % 101;
            if (rng <= 50) {
                boostAmount++;
                cout << "\nYou got a booster!";
            } else if (rng <= 90 && rng > 50) {
                gunAmount++;
                cout << "\nYou got a gun!";
            } else {
                swapAmount++;
                cout << "\nYou got a swap!";
            }
        }
    }

    void aiMove() {
        if (racer1 != "X" && racer1 != "x") {
            xwing.move();
        }
        if (racer1 != "Y" && racer1 != "y") {
            tiefighter.move();
        }
        if (racer1 != "Z" && racer1 != "z") {
            soullessone.move();
        }
    }

    bool isRaceOver() {
        if (xwing.position >= 49) {
            cout << "X Wing wins the race for this round!\n" << endl;
            xw++;
            return true;
        }
        if (tiefighter.position >= 49) {
            cout << "Tie Fighter wins the race for this round!\n" << endl;
            yw++;
            return true;
        }
        if (soullessone.position >= 49) {
            cout << "Soulless One wins the race for this round!\n" << endl;
            zw++;
            return true;
        }
        return false;
    }

    void displayResults() {
        cout << "Game Over" << endl;
        cout << "\nThe score is:\nX Wing: " << xw << "\nTie Fighter: " << yw << "\nSoulless One: " << zw << endl;
        bool betWon = false;

        if (players == 1) {
            if (((racer1 == "X" || racer1 == "x") && ((xw > yw) || (xw > zw))) ||
                ((racer1 == "Y" || racer1 == "y") && ((yw > xw) || (yw > zw))) ||
                ((racer1 == "Z" || racer1 == "z") && ((zw > yw) || (zw > xw)))) {
                cout << "You won the bet. Your reward is: RM " << bet * 1.5 << endl;
            } else {
                cout << "\nYou lost the bet!" << endl;
            }
        } else if (players == 2) {
            if (((racer1 == "X" || racer1 == "x") && ((xw > yw) && (xw > zw))) ||
                ((racer1 == "Y" || racer1 == "y") && ((yw > xw) && (yw > zw))) ||
                ((racer1 == "Z" || racer1 == "z") && ((zw > yw) && (zw > xw)))) {
                betWon = true;
                cout << "\nYou won the bet. Your reward is: RM" << bet * 2 << endl;
            } else {
                cout << "\nYou lost the bet!" << endl;
            }
        }
        cout << "\nItems" << setw(20) << "Items ability" << endl;
        cout << "\nBoost" << setw(20) << "Increase step by two" << endl;
        cout << "\nGun" << setw(20) << "Slow down opponent of your choice by two steps" << endl;
        cout << "\nSwap" << setw(20) << "Swap with a random racer's position" << endl;
    }

    void assignRacerSymbol(char track[][45], char symbol, int position, int height, int width) {
        switch (position)
        {
        //Go up
        case 0:
            track[height - 2][1] = symbol;
            break;
        case 1:
            track[height - 4][1] = symbol;
            break;
        case 2:
            track[height - 6][1] = symbol;
            break;
        //Go right
        case 3:
            track[height - 6][5] = symbol;
            break;
        case 4:
            track[height - 6][9] = symbol;
            break;
        case 5:
            track[height - 6][13] = symbol;
            break;
        case 6:
            track[height - 6][17] = symbol;
            break;
        case 7:
            track[height - 6][21] = symbol;
            break;
        //Go up
        case 8:
            track[height - 8][21] = symbol;
            break;
        case 9:
            track[height - 10][21] = symbol;
            break;
        case 10:
            track[height - 12][21] = symbol;
            break;
        //Go left
        case 11:
            track[height - 12][17] = symbol;
            break;
        case 12:
            track[height - 12][width - 32] = symbol;
            break;
        //Go down
        case 13:
            track[height - 10][width - 32] = symbol;
            break;
        //Go left
        case 14:
            track[height - 10][width - 36] = symbol;
            break;
        case 15:
            track[height - 10][width - 40] = symbol;
            break;
        //Go up
        case 16:
            track[height - 12][width - 40] = symbol;
            break;
        case 17:
            track[height - 14][width - 40] = symbol;
            break;
        case 18:
            track[1][width - 40] = symbol;
            break;
        //Go right
        case 19:
            track[1][width - 36] = symbol;
            break;
        case 20:
            track[1][width - 32] = symbol;
            break;
        case 21:
            track[1][width - 28] = symbol;
            break;
        case 22:
            track[1][width - 24] = symbol;
            break;
        case 23:
            track[1][width - 20] = symbol;
            break;
        case 24:
            track[1][width - 16] = symbol;
            break;
        case 25:
            track[1][width - 12] = symbol;
            break;
        case 26:
            track[1][width - 8] = symbol;
            break;
        case 27:
            track[1][width - 4] = symbol;
            break;
        //Go down
        case 28:
            track[height - 14][width - 4] = symbol;
            break;
        case 29:
            track[height - 12][width - 4] = symbol;
            break;
        //Go left
        case 30:
            track[height - 12][width - 8] = symbol;
            break;
        case 31:
            track[height - 12][width - 12] = symbol;
            break;
        case 32:
            track[height - 12][width - 16] = symbol;
            break;
        //Go down
        case 33:
            track[height - 10][width - 16] = symbol;
            break;
        case 34:
            track[height - 8][width - 16] = symbol;
            break;
        //Go right
        case 35:
            track[height - 8][width - 12] = symbol;
            break;
        case 36:
            track[height - 8][width - 8] = symbol;
            break;
        //Go down
        case 37:
            track[height - 6][width - 8] = symbol;
            break;
        case 38:
            track[height - 4][width - 8] = symbol;
            break;
        case 39:
            track[height - 2][width - 8] = symbol;
            break;
        //Go left
        case 40:
            track[height - 2][width - 12] = symbol;
            break;
        case 41:
            track[height - 2][width - 16] = symbol;
            break;
        case 42:
            track[height - 2][width - 20] = symbol;
            break;
        case 43:
            track[height - 2][width - 24] = symbol;
            break;
        case 44:
            track[height - 2][width - 28] = symbol;
            break;
        case 45:
            track[height - 2][width - 32] = symbol;
            break;
        case 46:
            track[height - 2][width - 36] = symbol;
            break;
        case 47:
            track[height - 2][width - 40] = symbol;
            break;
        case 48:
            track[height - 2][width - 44] = symbol;
            break;
        //From 49, prevent output display error
        case 49:
            track[height - 2][width - 44] = symbol;
            break;
        case 50:
            track[height - 2][width - 44] = symbol;
            break;
        case 51:
            track[height - 2][width - 44] = symbol;
            break;
        case 52:
            track[height - 2][width - 44] = symbol;
            break;
        }
    }
};

int main() {
    Game game;
    game.mainMenu();
    return 0;
}
