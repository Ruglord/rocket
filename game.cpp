#include "game.h"
void MouseManager::getMouse(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (findNumber(e.button.button) == -1)
            addNumber(e.button.button);
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        int index = findNumber(e.button.button);
        if (index != -1)
        {
            numbers.erase(numbers.begin() + findNumber(SDL_MOUSEBUTTONUP));
        }
    }

}

void InputController::update(SDL_Event& e)
{
    keyManager.getKeys(e);
    mouseManager.getMouse(e);
}
void Game::init()
{
    SDL_DisplayMode display;
    SDL_GetCurrentDisplayMode(0,&display);
    screenWidth = display.w;
    screenHeight = display.h;
}
glm::vec2 Game::getDimentions()
{
    return {screenWidth,screenHeight};
}
void Game::ToWorldPosition(double x, double y)
{

}
