#ifndef TRAITS_H_INCLUDED
#define TRAITS_H_INCLUDED

class Rocket;
struct Trait
{
    virtual void ability(Rocket& r)
    {

    }
};

struct speedUp : public Trait
{
    virtual void ability(Rocket& r);
};

#endif // TRAITS_H_INCLUDED
