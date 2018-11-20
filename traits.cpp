#include "traits.h"
#include "rocket.h"
#include "image.h"

Effect::Effect( double dur)
{
    duration = dur;
}
speedUpEffect::speedUpEffect() : Effect(1000)
{

}
void speedUpEffect::effect()
{
    if (owner->position.get())
    owner->position.get()->speedMods.push_back(2);
}
speedUp::speedUp() : Trait(SPEEDUP,speedUpSprite)
{
}
void speedUp::ability(Rocket& r)
{
    r.effects.push_back(&effect);
    effect.start(&r);
}
