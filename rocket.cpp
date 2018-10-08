 #include "rocket.h"
#include "image.h"
 const double Rocket::maxSpeed = 1;

 void InputComponent::update(KeyManager& manager, SDL_Event& e)
 {

 }
 void RocketInput::update(KeyManager& manager, SDL_Event& e, Rocket& r)
 {
        int x, y;
        SDL_GetMouseState(&x,&y);
        glm::vec2 rect = r.position.get()->getCenter();

        double angle = atan2(y-rect.y,rect.x-x);
        //std::cout << angle << std::endl;
        r.sprite.get()->changeAngle(angle);

    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
    {

        r.position.get()->moveTowards(x,y,r);
    }
 }
    Rocket::Rocket(double x, double y,CreatureWorld& world) : Creature(world, ROCKET)
    {

        position.get()->setRect(glm::vec4(x,y,96,64));
        position.get()->speed = 1;
              sprite.reset(new SpriteComponent);
         sprite.get()->setSprite(rocket);
         input.reset(new RocketInput);
    health.get()->health = 20;
    }
    void Rocket::changeSpeed(double horiz, double vert) //increases speed by horiz and vert
    {
        double incY = vertSpeed + vert;
        double incX = horizSpeed + horiz;
        double magnitude = sqrt(pow(incY,2) + pow(incX,2));
        bool tooBig = magnitude > maxSpeed;
        double denom = magnitude/(((sqrt(2.0),maxSpeed)))*tooBig + !tooBig*1; //if the speed is too big, this will adjust incX and incY to form a speed = to maxSpeed
        horizSpeed = incX/denom;
        vertSpeed = incY/denom;
    }
    void Rocket::update(KeyManager& manager, SDL_Event& e) //pressed = true if key was pressed false if released
    {
        input.get()->update(manager,e,*this);
       // changeSpeed(0,0);
    }
