#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <map>
#include "rocket.h"
#include "camera.h"
#include "interface.h"
#include <glm.hpp>
class MouseManager : public NumberManager
{
    int justClicked = -1;
public:
    void getMouse(SDL_Event& e);
    int getJustClicked();


};
struct InputController
{
    KeyManager keyManager;
    MouseManager mouseManager;
    void update(SDL_Event& e);
};
class World;
class Game
{
    static const double perMilSecond; //how many times per millisecond something happens. Used in deltaTime calculation
    static double currentTime;
public:
    static World* world;
    static double deltaTime;
    static std::vector<Trait*> traitList;
    static std::map<EntityID,bool> scannedCreatures; //a list of all scannable creatures and whether or not they've been scanned yet.
    static Rocket* player;
    static int screenWidth;
    static int screenHeight;
    static RenderController* renderer;
    static InputController input;
    static CreatureWorld creatures;
    static Interface interface;
    static glm::vec2 ToWorldPosition(double x, double y); //converts the on-screen position to world position
    static glm::vec2 ToScreenPosition(double x, double y); //given a point in the world, convert it to a point on the screen
    static void init();
    static glm::vec2 getDimentions();
    static void everyTick(SDL_Event& e);
    static void setDimensions();
    static std::vector<Trait> knownTraits;
    static Creature* findCreaturePosition(double x, double y); //given coords x and y, finds a creature that intersects with that coordinate.
};


#endif // GAME_H_INCLUDED
