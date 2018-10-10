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
    player = new Rocket(0,0);
    renderer = new RenderController(screenWidth,screenHeight,*player);
}
glm::vec2 Game::getDimentions()
{
    return {screenWidth,screenHeight};
}
void Game::everyTick(SDL_Event& e)
{
    std::vector<Creature*> creatures = world.getNearestCreatures(std::max(screenHeight,screenWidth), *player);
    for (int i = 0; i < creatures.size();i ++)
    {
        Creature* current = creatures[i];
        current->update();
        renderer->render(*(current->position.get()),*(current->sprite.get()));
    }
    input.update(e);
    player->update(input,e);
    renderer->render(*(player->position.get()),*(player->sprite.get()));
    renderer->update();
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
