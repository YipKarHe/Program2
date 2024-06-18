#ifndef RACER_H
#define RACER_H

#include <string>
using namespace std;

class Racer {
public:
    string name;
    int speedMin, speedMax, position;

    Racer(string n, int minSpeed, int maxSpeed);
    void move();
    void useBoost();
    void usegun();
    void useswap(int& position1, int& position2);
};

int generateRandomSteps(int minSteps, int maxSteps);

#endif // RACER_H
