 #include "rocket.h"
#include "image.h"
#include "game.h"
 const double Rocket::maxSpeed = 1;

 void InputComponent::update(InputController& manager, SDL_Event& e)
 {

 }



 void RocketInput::update(InputController& manager, SDL_Event& e, Rocket& r)
 {
        int x, y;
        SDL_GetMouseState(&x,&y);
        glm::vec2 pos = Game::ToWorldPosition(x,y);
        glm::vec2 rect = r.position.get()->getCenter();

        double angle = atan2(-pos.y+rect.y,-pos.x+rect.x) + M_PI;
        r.sprite.get()->changeAngle(angle);
    if (manager.mouseManager.findNumber(SDL_BUTTON_RIGHT) != -1)
    {
        r.position.get()->moveTowards(pos.x,pos.y,r);
        //std::cout << pos.x << std::endl;
    }
    if (manager.mouseManager.findNumber(SDL_BUTTON_LEFT) != -1)
    {
        Creature* found =Game::findCreaturePosition(pos.x,pos.y);
        if ( found != nullptr)
        {
            found->scan.get()->setScanning(true);
        }
    }
 }
    Rocket::Rocket(double x, double y) : Creature( ROCKET)
    {

        position.get()->setRect(glm::vec4(x,y,64,32));
        position.get()->setSpeed(1.5);
        sprite.reset(new SpriteComponent);
         sprite.get()->setSprite(rocket);
         input.reset(new RocketInput);
    health.get()->health = 20;
    scan.reset(new ScanComponent);
    traits[0] = new speedUp;
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
    void Rocket::update(InputController& manager, SDL_Event& e) //pressed = true if key was pressed false if released
    {
        input.get()->update(manager,e,*this);
     //   traits[0]->ability(*this);
       // changeSpeed(0,0);
       //sprite.get()->changeAngle(SDL_GetTicks()%(6));
    }
