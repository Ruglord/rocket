#include <render.h>
#include "image.h"

Sprite rocket;
Sprite box;
Sprite fish;
Sprite sharkSprite;
Sprite traitIcon;
Sprite speedUpSprite;

Sprite9 frame;

Font alef;

ChunkSprite dirt;

void loadSprites(int stanW, int stanH)
{
    rocket.init("sprites/rocket.png", true);
    box.init("sprites/square.png", true);
    fish.init("sprites/fish.png",true);
    sharkSprite.init("sprites/shark.png",true);
    traitIcon.init("sprites/traitIcon.png",true);
    speedUpSprite.init("sprites/fire.png",true);

    frame.init("sprites/frame.png",false,{16,16},{16,16});

    alef.init("alef.ttf",stanW, stanH);
    dirt.init("sprites/dirt.jpg",false);
}
