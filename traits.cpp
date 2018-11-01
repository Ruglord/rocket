#include "traits.h"
#include "rocket.h"

void speedUp::ability(Rocket& r)
{
    r.position.get()->speedMods.push_back(.001);
}
