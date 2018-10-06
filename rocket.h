#ifndef ROCKET_H_INCLUDED
#define ROCKET_H_INCLUDED
#include "creatures.h"
class Rocket :public Creature
{
    double horizSpeed = 0;
    double vertSpeed = 0;
    static const double maxSpeed;
    static double baseSpeed;
public:
    Rocket(double x, double y, CreatureWorld& world);
    void input(SDL_Event& e);
    void update(KeyManager& manager);
    void changeSpeed(double horiz, double vert);
    void changeAngle(double newAngle);
};


#endif // ROCKET_H_INCLUDED
