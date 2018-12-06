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
            //std::cout << coords.x-region.x << std::endl;
            s.render(program,coords.x-region.x,coords.y-region.y, coords.z, coords.a);
            //box.renderInstanced(program,{{{0,0,64,64},0}});
    }
    void Camera::renderCenter(RenderProgram& program)
    {
        render(program,*(center->position.get()),*(center->sprite.get()));
    }
    glm::vec4 Camera::getRegion()
    {
        return region;
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

    glm::vec4 RenderController::getRegion()
    {
        return camera.getRegion();
    }
    void RenderController::update()
    {
        camera.adjust();
    }


