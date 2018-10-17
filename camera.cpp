#include "camera.h"
#include "creatures.h"
#include "rocket.h"
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
            s.render(program,coords.x-region.x,coords.y-region.y, coords.z, coords.a);
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
        basic.setMatrix4fv("projection",glm::value_ptr(glm::ortho(0.0f, (float)width,(float)height, 0.0f, -1.0f, 1.0f)));
    }
    void RenderController::render(PositionComponent& p, SpriteComponent& s)
    {
        camera.render(basic,p,s);
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
    void RenderController::renderAll(const std::vector<Creature*>& lst)
    {
        renderEntities(lst);
        camera.renderCenter(basic);
    }
    glm::vec4 RenderController::getRegion()
    {
        return camera.getRegion();
    }
    void RenderController::update()
    {
        camera.adjust();
    }


