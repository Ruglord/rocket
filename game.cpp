#include "game.h"
#include "world.h"
#include "render.h"
#include "image.h"
void MouseManager::getMouse(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (findNumber(e.button.button) == -1)
        {
            justClicked = e.button.button;
            addNumber(e.button.button);
        }
        else
        {
            justClicked = -1;
        }
    }
    else
    {
        justClicked = -1;
        if (e.type == SDL_MOUSEBUTTONUP)
        {
            removeNumber(e.button.button);
        }

    }
}
int MouseManager::getJustClicked()
{
    return justClicked;
}

void InputController::update(SDL_Event& e)
{
    keyManager.getKeys(e);
    mouseManager.getMouse(e);
}
void Game::setDimensions()
{
        SDL_DisplayMode display;
    SDL_GetCurrentDisplayMode(0,&display);
    screenWidth = 640;//display.w;
    screenHeight = 640;//display.h;
}
void Game::init()
{
    deltaTime = 0;
    currentTime = SDL_GetTicks();
    setDimensions();
    world = new World();
    player = new Rocket(0,-20);
    renderer = new RenderController("shaders/vertex/vertexShader.h","shaders/fragment/fragmentShader.h",screenWidth,screenHeight,*player);
    interface.init();

}
glm::vec2 Game::getDimentions()
{
    return {screenWidth,screenHeight};
}
void Game::everyTick(SDL_Event& e)
{
    bool paused = interface.current == &interface.quit;
    input.update(e);
    if (!paused)
    {
        std::vector<Creature*> things = creatures.getNearestCreatures(std::max(screenHeight,screenWidth), *player);
        for (int i = 0; i < things.size();i ++)
        {
            Creature* current = things[i];
            current->update();
            renderer->render(*current);
        }
        player->update(input,e);
        world->render();
        renderer->update();
        renderer->render(*player);
        glm::vec4 r = player->position.get()->getRect();
      //  drawRectangle(RenderController::lineProgram,{1,1,1},{Game::screenWidth/2 - r.z/2,Game::screenHeight/2 - r.a/2, r.z,r.a},player->sprite.get()->getAngle());
    }
        SDL_Keycode pressed =  input.keyManager.getJustPressed();
       if (pressed == SDLK_ESCAPE)
        {
                interface.switchWindow(&interface.quit);
        }
        else if (!paused)
        {
            Window* window = nullptr;
            switch (pressed)
            {
            case SDLK_TAB:
                window = &interface.log;
                break;
            }
            if (window != nullptr)
            {
                interface.switchWindow(window);
            }

        }

    interface.update();
    interface.render();
    double current = SDL_GetTicks();
    deltaTime = (current - currentTime)/Game::perMilSecond;
    currentTime = current;
}
Creature* Game::findCreaturePosition(double x, double y)
{
    std::vector<Creature*> things = creatures.getCreatures();
    //std::cout << x<<" "<<y << std::endl;
    int size = things.size();
    for (int i = 0; i < size; i ++)
    {
        Creature* current = things[i];
        if (pointInVec(current->position.get()->getRect(),x,y))
        {
            return current;
        }
    }
  //  std::cout << "Not Found" << std::endl;
    return nullptr;
}
glm::vec2 Game::ToWorldPosition(double x, double y)//given a point on the screen, convert it to a point on the world
{
    glm::vec4 region = renderer->getRegion();
    return {region.x +x, region.y + y};

}

glm::vec2 Game::ToScreenPosition(double x, double y) //given a point in the world, convert it to a point on the screen
{
        glm::vec4 region = renderer->getRegion();
    return {x-region.x , y-region.y};
}
