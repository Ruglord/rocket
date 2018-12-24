#include "world.h"
#include "game.h"
World::World()
{
    landscape.push_back({-500,0});
    landscape.push_back({-100,-100});
    landscape.push_back({300,500});
}
void World::render()
{
    int size = landscape.size();
    for (int i = 0; i < size-1; i ++)
    {
        glm::vec2 trans1 = Game::renderer->translate(landscape[i]);
        glm::vec2 trans2 = Game::renderer->translate(landscape[i+1]);
        drawLine(Game::renderer->lineProgram,{1,1,1},{{trans1,trans2}});
    }
}

std::vector<glm::vec2>* World::getPoints(double x, double y)
{
    return &landscape;
}

