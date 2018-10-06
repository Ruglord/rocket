#include <render.h>
#include "image.h"

Sprite rocket;
Sprite box;
Sprite fish;
Sprite shark;
void loadSprites(int stanW, int stanH)
{
    rocket.init(stanW,stanH,"sprites/rocket.png", true);
    box.init(stanW, stanH, "sprites/square.png", true);
    fish.init(stanW,stanH,"sprites/fish.png",true);
    shark.init(stanW,stanH,"sprites/shark.png",true);
}
