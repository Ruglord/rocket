#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm.hpp>
#include "objects.h"
class Rocket;
class Camera
{
    glm::vec4 region;
    Rocket* center;
public:
    Camera(int width, int height, Rocket* r);
    Camera();
    void init(int width, int height, Rocket* r);
    void adjust();
    void render(Thing& t);
    glm::vec4 getRegion();


};

class RenderController
{
    Camera camera;
    void renderEntities(std::vector<Entity*>& lst);
public:
    RenderController(int width, int height, Rocket& r);
    void render();
};

#endif // CAMERA_H_INCLUDED
