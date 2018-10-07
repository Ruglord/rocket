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
    void Camera::render(PositionComponent& p, SpriteComponent& s)
    {

            glm::vec4 coords = p.getRect();
    //        std::cout << coords.x-region.x << " " << coords.y-region.y  << std::endl;
            s.render(coords.x-region.x,coords.y-region.y, coords.z, coords.a);
    }
    glm::vec4 Camera::getRegion()
    {
        return region;
    }

    RenderController::RenderController(int width, int height, Rocket& r)
    {
        camera.init(width,height,&r);
    }
    void RenderController::renderEntities(std::vector<Entity*>& lst)
    {
        for (std::vector<Entity*>::iterator i = lst.begin(); i < lst.end(); i ++)
        {
            Entity* current = (*i);
            current->sprite.get()->getSprite().setTint({.5,.5,.5});
            camera.render(*current->position.get(),*current->sprite.get());
        }
    }


