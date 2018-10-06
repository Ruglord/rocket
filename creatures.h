#ifndef CREATURES_H_INCLUDED
#define CREATURES_H_INCLUDED
#include <vector>
#include "objects.h"
#include "camera.h"

class CreatureWorld;
struct AIComponent : public Component
{
    virtual void AI( Entity& e) ;

};
struct CreatureSprite : public SpriteComponent
{
    void changeAngle(double newAngle);
};
class Creature;
struct CreaturePosition : public PositionComponent
{
    void move(double x, double y, Thing& c);
};
class Creature : public Entity
{
protected:
    CreatureWorld* world = nullptr;
    std::vector<Thing> attachments;
    std::unique_ptr<AIComponent> AI;
public:
    Creature(CreatureWorld& World, int ID);
    AIComponent& getAI();
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
    void move(double x, double y);
};

struct SchoolOfFishSprite : public CreatureSprite
{
    virtual void render(double x, double y, double w, double h);
};

struct SchoolOfFishAI : public AIComponent
{
    virtual void AI(Entity& school)
    {
        school.getPosition().move(.1,0, school);
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
