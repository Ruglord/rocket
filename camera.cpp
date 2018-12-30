#include "camera.h"
#include "creatures.h"
#include "rocket.h"
#include "image.h"
    Camera::Camera(int w, int h, Rocket* r)
    {
       init(w,h,r);
    }
    Camera::Camera()
    {

    }
    void Camera::init(int w, int h, Rocket* r)
    {
        center = r;
        glm::vec4 coords = center->position.get()->getRect();
        region = {coords.x + coords.z/2 - w/2, coords.y + coords.a/2 - h/2, w,h};
    }
    void Camera::adjust()
    {
        glm::vec4 coords = center->position.get()->getRect();
        region.x =coords.x + coords.z/2 - region.z/2;
        region.y = coords.y + coords.a/2 - region.a/2;
    }
    void Camera::render(RenderProgram& program,PositionComponent& p, SpriteComponent& s)
    {
            glm::vec4 coords = p.getRect();
            glm::vec2 translated = translate({coords.x,coords.y});
            //std::cout << coords.x-region.x << std::endl;
            s.render(program,translated.x,translated.y, coords.z, coords.a);
            //box.renderInstanced(program,{{{0,0,64,64},0}});
    }
    void Camera::drawRect(RenderProgram& program, const glm::vec3 color, const glm::vec4& rect, double angle)
    {
        glm::vec2 corner = translate({rect.x,rect.y});
        glm::vec4 translated = {corner.x,corner.y, rect.z, rect.a};
        drawRectangle(program,color,translated,angle);
    }

    void Camera::renderCenter(RenderProgram& program)
    {
        render(program,*(center->position.get()),*(center->sprite.get()));
    }
    glm::vec4 Camera::getRegion()
    {
        return region;
    }
    glm::vec2 Camera::translate(const glm::vec2& point)
    {
        return {point.x - region.x, point.y - region.y};
    }
    RenderController::RenderController(std::string vertex, std::string fragment,int width, int height, Rocket& r)
    {
        camera.init(width,height,&r);
        basic.init(vertex,fragment);
        scanning.init(vertex,"shaders/fragment/paintShader.h");
        glm::mat4 mat = glm::ortho(0.0f, (float)width,(float)height, 0.0f, -1.0f, 1.0f);
        scanning.setMatrix4fv("projection",glm::value_ptr(mat));
        basic.setMatrix4fv("projection",glm::value_ptr(mat));
        wordProgram.init("shaders/vertex/wordVertex.h","shaders/fragment/wordFragment.h");
        wordProgram.setMatrix4fv("projection",glm::value_ptr(glm::ortho(0.0f, (float)width,0.0f,(float)height)));

        lineProgram.init("shaders/vertex/simpleVertex.h","shaders/fragment/simpleFragment.h");
        lineProgram.setMatrix4fv("projection",glm::value_ptr(mat));
    }
    void RenderController::render(Creature& creature)
    {
        render(*(creature.sprite.get()),*(creature.position.get()));
    }
    void RenderController::render(SpriteComponent& sprite, PositionComponent& position)
    {
        if (sprite.request == nullptr)
        {
            sprite.request = &basic;
        }
        camera.render(*sprite.request,position,sprite);
        sprite.request = &basic;
    }
    void RenderController::renderEntities(const std::vector<Creature*>& lst)
    {
        int size = lst.size();
        for (int i = 0; i < size; i ++)
        {
            Creature* current = lst[i];
            current->sprite.get()->getSprite().setTint({.5,.5,.5});
            camera.render(basic,*current->position.get(),*current->sprite.get());
        }
    }
    void RenderController::drawRectangle(const glm::vec3& color, const glm::vec4& rect, double angle)
    {
        camera.drawRect(lineProgram,color,rect,angle);
    }

    glm::vec4 RenderController::getRegion()
    {
        return camera.getRegion();
    }
    void RenderController::update()
    {
        camera.adjust();
    }
    glm::vec2 RenderController::translate(const glm::vec2& point)
    {
        return camera.translate(point);
    }



