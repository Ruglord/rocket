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
void loadSprites(int stanW, int stanH)
{
    rocket.init(stanW,stanH,"sprites/rocket.png", true);
    box.init(stanW, stanH, "sprites/square.png", true);
    fish.init(stanW,stanH,"sprites/fish.png",true);
    sharkSprite.init(stanW,stanH,"sprites/shark.png",true);
    traitIcon.init(stanW,stanH,"sprites/traitIcon.png",true);
    speedUpSprite.init(stanW,stanH,"sprites/fire.png",true);

    frame.init(stanW,stanH, "sprites/frame.png",false,{16,16},{16,16});

    alef.init("alef.ttf",stanW, stanH);

}
