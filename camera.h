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
    void render(RenderProgram& program, PositionComponent& p, SpriteComponent& s);
    void renderCenter(RenderProgram& program);
    glm::vec4 getRegion();


};
class Creature;
class RenderController
{

    Camera camera;
    void renderEntities(const std::vector<Creature*>& lst);
public:
    static RenderProgram basic;
    static RenderProgram scanning;
    static RenderProgram wordProgram;
    static RenderProgram lineProgram;
    RenderController(std::string vertex, std::string fragment,int width, int height, Rocket& r);
    void render(SpriteComponent& sprite, PositionComponent& position);
    void render(Creature& creature);
    glm::vec4 getRegion();
    void update();
};

#endif // CAMERA_H_INCLUDED
