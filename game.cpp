#include "game.h"
#include "render.h"
#include "image.h"
void MouseManager::getMouse(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (findNumber(e.button.button) == -1)
            addNumber(e.button.button);
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        removeNumber(e.button.button);
    }

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
    screenWidth = display.w;
    screenHeight = display.h;
}
void Game::init()
{
    deltaTime = 0;
    currentTime = SDL_GetTicks();
    setDimensions();
    player = new Rocket(0,0);
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
    if (!paused)
    {
        std::vector<Creature*> creatures = world.getNearestCreatures(std::max(screenHeight,screenWidth), *player);
        for (int i = 0; i < creatures.size();i ++)
        {
            Creature* current = creatures[i];
            current->update();
            renderer->render(*current);
        }
        player->update(input,e);
        renderer->render(*player);
        renderer->update();
    }
    if (e.type == SDL_KEYDOWN)
    {
        SDL_Keycode latest = input.keyManager.getLatest();
        SDL_Keycode current = e.key.keysym.sym;
       if ( current == SDLK_ESCAPE &&  latest != SDLK_ESCAPE)
        {
            if (!paused)
            {
                interface.current = &interface.quit;
            }
            else
            {
                interface.current = nullptr;
            }
        }
        else if (!paused)
        {
            SDL_Keycode pressed =  (current)*(latest != current) + (latest == current)*-1;
            Window* window = nullptr;
            switch (pressed)
            {
            case SDLK_TAB:
                window = &interface.log;
                break;
            }
            if (window != nullptr)
            {
                if (interface.current != window)
                {
                    interface.current = window;
                }
                else
                {
                    interface.current = nullptr;
                }
            }

        }
    }

    input.update(e);
    interface.update();
    interface.render();
    double current = SDL_GetTicks();
    deltaTime = (current - currentTime)/Game::perMilSecond;
    currentTime = current;
}
Creature* Game::findCreaturePosition(double x, double y)
{
    std::vector<Creature*> creatures = world.getCreatures();
    //std::cout << x<<" "<<y << std::endl;
    int size = creatures.size();
    for (int i = 0; i < size; i ++)
    {
        Creature* current = creatures[i];
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
