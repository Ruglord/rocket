#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class World //represents the actual environment
{
    std::vector<glm::vec2> landscape;
public:
    World();
    void render();
    std::vector<glm::vec2>* getPoints(double x, double y);

};

#endif // WORLD_H_INCLUDED
