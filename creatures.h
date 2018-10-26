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
struct ScanComponent : public Component
{
    bool scanning = false;
    void update(SpriteComponent* sprite);
    void setScanning(bool value); //if value is true, start the scanning


};
struct CreatureSprite : public SpriteComponent
{
    void changeAngle(double newAngle);
    void incrementAngle(double target, double speed);

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
    std::vector<Thing> attachments;
public:
    std::unique_ptr<HealthComponent> health;
    std::unique_ptr<SpriteComponent> sprite;
    std::unique_ptr<CreaturePosition> position;
    std::unique_ptr<AIComponent> AI;
    std::unique_ptr<ScanComponent> scan;
    Creature(int ID);
    AIComponent& getAI();
   virtual  void update()
    {
        health.get()->updateDamaged();
        glm::vec4 rect = position.get()->getRect();
        AI.get()->AI(*this);
        scan.get()->update(sprite.get());
        //sprite.get()->render(rect.x,rect.y,rect.w,rect.a);
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
    std::vector<Creature*> getCreatures();
    void update(Camera& c);
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
