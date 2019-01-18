#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include "objects.h"
#include "world.h"
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
    void render(Chunk& chunk);
    void renderCenter(RenderProgram& program);
    glm::vec4 getRegion();
    glm::vec2 translate(const glm::vec2& point);
    void drawRect(RenderProgram& program, const glm::vec3 color, const glm::vec4& rect, double angle);

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
    void render(Chunk& chunk);
    void drawRectangle(const glm::vec3& color, const glm::vec4& rect, double angle);
    glm::vec4 getRegion();
    glm::vec2 translate(const glm::vec2& point);
    void update();
};

#endif // CAMERA_H_INCLUDED
