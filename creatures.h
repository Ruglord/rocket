#ifndef CREATURES_H_INCLUDED
#define CREATURES_H_INCLUDED
#include <vector>
#include "objects.h"
#include "camera.h"

class CreatureWorld;
class Creature;
struct AIComponent : public Component
{
    virtual void AI( Creature& e) ;

};
struct CreatureSprite : public SpriteComponent
{
    void changeAngle(double newAngle);
};
struct CreaturePosition : public PositionComponent
{
    double speed = 0;
    void move(double x, double y,Creature& c);//moves creature in the direction x, y;
    void moveTowards(double x, double y, Creature& c); //moves the creatures towards a point.
};
class Creature : public IDed
{
protected:
    CreatureWorld* world = nullptr;
    std::vector<Thing> attachments;

public:
    std::unique_ptr<HealthComponent> health;
    std::unique_ptr<SpriteComponent> sprite;
    std::unique_ptr<CreaturePosition> position;
    std::unique_ptr<AIComponent> AI;
    Creature(CreatureWorld& World, int ID);
    AIComponent& getAI();
    void update()
    {
        health.get()->updateDamaged();
        glm::vec4 rect = position.get()->getRect();
        sprite.get()->render(rect.x,rect.y,rect.w,rect.a);
    }
};

class Rocket;
class CreatureWorld
{
    std::vector<Creature*> creatures;
    std::vector<Creature> nearestCreatures;
    Rocket* center = nullptr;
public:

    CreatureWorld();
    void setCenter(Rocket& r);
    void addCreature(Creature& c);
    std::vector<Creature*> getNearestCreatures(double radius, Creature& c);
    void update(Camera& c);
};

struct SchoolOfFishSprite : public CreatureSprite
{
    virtual void render(double x, double y, double w, double h);
};

struct SchoolOfFishAI : public AIComponent
{
    virtual void AI(Creature& school)
    {
        school.position.get()->move(.5,0,school);
    }
};

class SchoolOfFish : public Creature
{
public:
    SchoolOfFish(double x, double y, CreatureWorld& World);
};


/*class Shark : public Creature
{
public:
    Shark(double x, double y, CreatureWorld& World);
    void AI();
};*/
#endif // CREATURES_H_INCLUDED
