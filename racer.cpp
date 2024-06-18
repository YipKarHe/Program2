#include "Racer.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int generateRandomSteps(int minSteps, int maxSteps) {
    return rand() % (maxSteps - minSteps + 1) + minSteps;
}

Racer::Racer(string n, int minSpeed, int maxSpeed) : name(n), speedMin(minSpeed), speedMax(maxSpeed), position(0) {}

void Racer::move() {
    int steps = generateRandomSteps(speedMin, speedMax);
    position += steps;
    cout << name << " moved " << steps << " steps" << endl;
}

void Racer::useBoost() {
    int steps = generateRandomSteps(speedMin, speedMax);
    position += steps + 2;
    cout << name << " used boost and moved " << steps + 2 << " steps" << endl;
}

void Racer::usegun() {
    int steps = generateRandomSteps(speedMin, speedMax);
    position += steps - 2;
    cout << name << " used gun and slowed down by " << steps - 2 << " steps" << endl;
}

void Racer::useswap(int& position1, int& position2) {
    swap(position1, position2);
    cout << "Racers swapped positions" << endl;
}
