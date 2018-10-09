
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "objects.h"
#include "image.h"

const double gravity = .01;
    PositionComponent& Thing::getPosition()
    {
        return *position;
    }
    void PositionComponent::changeCoords(double x, double y)
    {
        boundingRect.x = x;
        boundingRect.y = y;
    }
    void PositionComponent::setRect(glm::vec4 rect)
    {
        boundingRect = rect;
    }
    glm::vec4 PositionComponent::getRect() const
    {
        return boundingRect;
    }
    glm::vec2 PositionComponent::getCenter() const
    {
        return glm::vec2(boundingRect.x +boundingRect.z/2,boundingRect.y + boundingRect.a/2);
    }
    Sprite& SpriteComponent::getSprite() const
    {
        return *sprite;
    }
    void SpriteComponent::setSprite(Sprite& s)
    {
        sprite = (&s);
    }
    double SpriteComponent::getAngle() const
    {
        return angle;
    }
    void SpriteComponent::changeAngle(double newAngle)
    {
        angle = newAngle;
    }
    void SpriteComponent::render(double x, double y,double w, double h)
    {
        sprite->render(program,x,y,w,h,angle);
    }
    Thing::Thing()
    {

    }
    SpriteComponent& Thing::getSprite()
    {
        return *(sprite.get());
    }
    Entity::Entity(int ID) : IDed(ID)
    {

    }
    void Entity::update()
    {
        health.get()->updateDamaged();
        glm::vec4 rect = position.get()->getRect();
        std::cout << rect.x << " " << rect.y << std::endl;
        sprite.get()->render(rect.x,rect.y,rect.w,rect.a);

    }
    double Entity::getHealth()
    {
        return health.get()->health;
    }
    double HealthComponent::getHealth()
    {
        return health;
    }
    void HealthComponent::takeDamage(double damage)
    {
        if (damaged == -1)
        {
            health -= damage;
            damaged = SDL_GetTicks();
        }
    }
    void HealthComponent::updateDamaged()
    {
        if (damaged != -1)
        {
            if (SDL_GetTicks() - damaged >= 100) //if it has been a certain amount of time since taking damage, eliminate the invincibility
            {
                damaged = -1;
            }
        }
    }

