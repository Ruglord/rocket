#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED
#include "render.h"
#include <SDL.h>
#include <SDLhelper.h>
#include <vanilla.h>

enum EntityID
{
    UNDEFINED,
    ROCKET,
    SHARK,
    SCHOOLOFFISH

};

extern const double gravity;
class Thing;
struct Component
{

};
class SpriteComponent : public Component
{
protected:
    Sprite* sprite = nullptr;
    double angle = 0;
public:
    void setSprite(Sprite& s);
    virtual Sprite& getSprite() const;
    virtual double getAngle() const;
    virtual void changeAngle(double newAngle);
    virtual void render( RenderProgram& program,double x, double y, double w, double h); // where to render
};
struct PositionComponent : public Component
{
    protected:
    glm::vec4 boundingRect;
    public:
    void setRect(glm::vec4 rect);
    virtual void changeCoords(double x, double y);
    glm::vec4 getRect() const;
    glm::vec2 getCenter() const;
};
struct HealthComponent : public Component
{    float damaged = -1;
    double health;
    virtual void updateDamaged();
    virtual void takeDamage(double damage);
    virtual double getHealth();
};

class Thing //anything with coordinates and a sprite
{
protected:
public:
        std::unique_ptr<SpriteComponent> sprite;
    std::unique_ptr<PositionComponent> position;
    Thing();
     PositionComponent& getPosition();
     SpriteComponent&  getSprite();
};

class Entity : public IDed//anything with health
{
protected:


public:
    std::unique_ptr<HealthComponent> health;
    std::unique_ptr<SpriteComponent> sprite;
    std::unique_ptr<PositionComponent> position;
    Entity(int ID);
   virtual void update();
   double getHealth();
};

#endif // OBJECTS_H_INCLUDED
