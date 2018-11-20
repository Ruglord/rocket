#ifndef TRAITS_H_INCLUDED
#define TRAITS_H_INCLUDED
#include "creatures.h"
class Effect
{
protected:

    Creature* owner = nullptr;
public:
    double duration = 0;
    double startTime = 0;
    bool started = false;
    Effect( double dur);
    virtual void effect()
    {

    }
    void start(Creature* creature)
    {
        owner = creature;
        started = true;
        startTime = SDL_GetTicks();
    }
};
class speedUpEffect : public Effect
{
    public:
    speedUpEffect();
    void effect();
};
class Rocket;
enum TraitID
{
    UNDEFTRAIT,
    SPEEDUP
};
struct Trait
{
    TraitID id = UNDEFTRAIT;
    SpriteComponent icon;
    Trait(TraitID ID, Sprite& sprite)
    {
        id = ID;
        icon.setSprite(sprite);
    }
    virtual void ability(Rocket& r)
    {

    }
};

struct speedUp : public Trait
{
    speedUpEffect effect;
    speedUp();
    virtual void ability(Rocket& r);
};



#endif // TRAITS_H_INCLUDED
