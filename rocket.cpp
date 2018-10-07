 #include "rocket.h"
#include "image.h"
 const double Rocket::maxSpeed = 1;
    double Rocket::baseSpeed = .015;
    Rocket::Rocket(double x, double y,CreatureWorld& world) : Creature(world, ROCKET)
    {

        position.get()->setRect(glm::vec4(x,y,96,64));
        sprite.get()->changeAngle(M_PI/2);
         sprite.get()->setSprite(rocket);
    health.get()->health = 20;
    }
    void Rocket::input(SDL_Event& e)
    {
        if (e.type == SDLK_DOWN)
        {
            if (e.key.keysym.sym == SDLK_SPACE)
            {

            }
        }
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
    void Rocket::update(KeyManager& manager) //pressed = true if key was pressed false if released
    {
    /*        double a = sprite.get()->getAngle();
            if (manager.findNumber(SDLK_SPACE) != -1)
            {
                changeSpeed(cos(a)*baseSpeed,-sin(a)*baseSpeed);
            }
            int right = manager.findNumber(SDLK_d);
            int left = manager.findNumber(SDLK_a);
            if ( right != -1 || left != -1)
            {
                bool direction = right > left;
                //std::cout << right << " " << left << std::endl;
                sprite.get()->changeAngle(a + !direction*.01 - direction*.01);
            }

        glm::vec4 coords = position.get()->getRect();
      //  std::cout << coords.y + coords.a << std::endl;
        //changeSpeed(0,gravity*(coords.y + coords.a< 640));
       // vertSpeed += gravity;
        position.get()->move(coords.x,coords.y, *this);*/
       // changeSpeed(0,0);
    }
