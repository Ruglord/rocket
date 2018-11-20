#ifndef ROCKET_H_INCLUDED
#define ROCKET_H_INCLUDED
#include "creatures.h"
#include "traits.h"

struct InputController;
struct InputComponent
{
   virtual void update(InputController& manager,SDL_Event& e);
};
struct RocketInput : public InputComponent
{
    void update(InputController& manager,SDL_Event& e, Rocket& r);
};
static const int numberOfTraits = 3;
class Rocket :public Creature
{
    double horizSpeed = 0;
    double vertSpeed = 0;
    static const double maxSpeed;
public:
    std::shared_ptr<Trait> traits[numberOfTraits];
    std::unique_ptr<RocketInput> input;
    Rocket(double x, double y);
    void update(InputController& manager, SDL_Event& e);
    void changeSpeed(double horiz, double vert);
    void changeAngle(double newAngle);
};


#endif // ROCKET_H_INCLUDED
