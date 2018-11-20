#ifndef CREATURES_H_INCLUDED
#define CREATURES_H_INCLUDED
#include <vector>
#include <list>
#include "objects.h"
#include "camera.h"
class CreatureWorld;
class Creature;
class Trait;
struct AIComponent : public Component
{
    virtual void AI( Creature& e) ;

};

struct CreatureSprite : public SpriteComponent
{
    void changeAngle(double newAngle);
    void incrementAngle(double target, double speed);

};
struct CreaturePosition : public PositionComponent
{
    std::list<double> speedMods; //list of all the speed modifications
    void move(double x, double y,Creature& c);//moves creature in the direction x, y;
    void moveTowards(double x, double y, Creature& c); //moves the creatures towards a point.
    double getSpeed();
    void setSpeed(double sp);
private:
        double speed = 0;
};
class Effect;
class ScanComponent;
class Creature : public IDed
{
protected:
    std::vector<Thing> attachments;
public:
    ScanComponent* scan = nullptr; //pointer to a static scan Component
    std::list<Effect*> effects;
    std::unique_ptr<HealthComponent> health;
    std::unique_ptr<SpriteComponent> sprite;
    std::unique_ptr<CreaturePosition> position;
    std::unique_ptr<AIComponent> AI;
    Creature(int ID);
    AIComponent& getAI();
    virtual void update();
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
    std::vector<Creature*> getCreatures();
    void update(Camera& c);
    ~CreatureWorld();
};

struct SchoolOfFishSprite : public CreatureSprite
{
    int ticks;
    virtual void render(RenderProgram& program,double x, double y, double w, double h);
};

struct SchoolOfFishAI : public AIComponent
{
    virtual void AI(Creature& school)
    {
        school.position.get()->move(1,0,school);
    }
};

class SchoolOfFish : public Creature
{
public:
    SchoolOfFish(double x, double y);
};

class Crab : public Creature
{
public:
    //Crab(double x, double y);
};
struct SharkAI : public AIComponent
{
    virtual void AI(Creature& shark);
};
class Shark : public Creature
{
public:
    Shark(double x, double y);
};
#endif // CREATURES_H_INCLUDED
