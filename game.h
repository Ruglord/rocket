#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "camera.h"
#include <glm.hpp>
class MouseManager : public NumberManager
{
public:
    void getMouse(SDL_Event& e);

};
struct InputController
{
    KeyManager keyManager;
    MouseManager mouseManager;
    void update(SDL_Event& e);
};
class Game
{
static int screenWidth;
   static int screenHeight;
   static RenderController* render;
   static InputController input;
public:
   static void ToWorldPosition(double x, double y); //converts the on-screen position to world position
   static void init();
   static glm::vec2 getDimentions();
};

#endif // GAME_H_INCLUDED
