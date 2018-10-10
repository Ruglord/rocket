#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include "objects.h"
#include <glm.hpp>
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
    void render(PositionComponent& p, SpriteComponent& s);
    void renderCenter();
    glm::vec4 getRegion();


};
class Creature;
class RenderController
{
    Camera camera;
    void renderEntities(const std::vector<Creature*>& lst);
public:
    RenderController(int width, int height, Rocket& r);
    void renderAll(const std::vector<Creature*>& lst);
    void render(PositionComponent& p, SpriteComponent& s);
    glm::vec4 getRegion();
    void update();
};

#endif // CAMERA_H_INCLUDED
