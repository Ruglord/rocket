#include "creatures.h"
#include "image.h"
void AIComponent::AI(Creature& e) {


}

Creature::Creature(CreatureWorld& World, int ID) : IDed(ID)
{
    world = &World;
            position.reset(new CreaturePosition);
        sprite.reset(new CreatureSprite);
        health.reset(new HealthComponent);
        AI.reset(new AIComponent);
}

 AIComponent& Creature::getAI()
{
    return *(AI.get());
}

void CreatureSprite::changeAngle(double newAngle)
{
    bool outOfRange = (newAngle > M_PI || newAngle < -M_PI);
    double radians = newAngle - 2*M_PI*outOfRange*(2*(newAngle > M_PI)-1);
    SpriteComponent::changeAngle(radians);
    if (radians> M_PI/2 || radians < -M_PI/2 )
    {
        sprite->flip();
    }
}

void CreaturePosition::move(double x, double y, Creature& c)//moves creature in the direction x, y;
{

    moveTowards(boundingRect.x + x, boundingRect.y + y,c);
}

void CreaturePosition::moveTowards(double x, double y, Creature& c) //moves the creatures towards a point.
{
    glm::vec4 hit = boundingRect;
    double radians = atan2(y-hit.y, x-hit.x );
    double horizSpeed = speed*cos(radians);
    if (x - hit.x < horizSpeed)
    {
        horizSpeed = x-hit.x;
    }
    double vertSpeed = speed*sin(radians);
    if (y - hit.y < vertSpeed)
    {
        vertSpeed = y-hit.y;
    }
    changeCoords(hit.x + horizSpeed, hit.y + vertSpeed);
}

CreatureWorld::CreatureWorld()
{

}
void CreatureWorld::setCenter(Rocket& r)
{
    center = &r;
}
void CreatureWorld::addCreature(Creature& c)
{
    creatures.push_back(&c);
}

std::vector<Creature*> CreatureWorld::getNearestCreatures(double radius, Creature& c)
{
    std::vector<Creature*> lst;
    int size = creatures.size();
    glm::vec4 hitBox = c.position.get()->getRect();
    glm::vec4 bigBox(hitBox.x - radius, hitBox.y - radius, radius*2+hitBox.z, radius*2 + hitBox.a);
    for (int i = 0; i < size;i ++)
    {
        Creature* current = creatures[i];
        glm::vec4 curCenter = current->position.get()->getRect();
        if (vecIntersect(bigBox,curCenter))
        {
            lst.push_back(current);
        }
    }
    return lst;
}

void CreatureWorld::update(Camera& c)
{
    int size = creatures.size();
    for (int i = 0 ; i <size; i ++)
    {
        creatures[i]->getAI().AI(*creatures[i]);
        c.render(*creatures[i]->position.get(),*creatures[i]->sprite.get());
    }
}


SchoolOfFish::SchoolOfFish(double x, double y, CreatureWorld& World) : Creature(World, SCHOOLOFFISH)
{
    sprite.reset(new SchoolOfFishSprite);
    sprite.get()->setSprite(fish);
    AI.reset(new SchoolOfFishAI);
    position.get()->setRect(glm::vec4(x,y,32,16));
    position.get()->speed = .5;
    health.get()->health = 10;
}

void SchoolOfFishSprite::render(double x, double y, double w, double h)
{
     Sprite* s = &(getSprite());
    std::vector<glm::vec3> points;
    for (int i = 0; i < 16; i ++)
    {
        int sign = ((i%2 == 0)*(-2) + 1);
        points.push_back(glm::vec3(x + (sign*(i%4)*20),y + 50*sin((x/5 + i*M_PI/4)/10),0));
    }
    s->renderInstanced(program,points,w/2.0, h/2.0);
}

/*Shark::Shark( double x, double y, CreatureWorld& World) : Creature(x,y,256,128,shark,20,World, SHARK)
{

}

void Shark::AI()
{
      glm::vec4 vec = getHitbox();
    std::vector<Creature*> lst = (world->getNearestCreatures(100,*this));
    int size = lst.size();
    glm::vec2 target(vec.x + speed,0);
    for (int i = 0; i < size; i ++)
    {
        if (lst[i]->getID()== ROCKET)
        {
            glm::vec4 hitbox = lst[i]->getHitbox();
                if (!vecIntersect(vec,hitbox))
                {
                target = glm::vec2(hitbox.x,hitbox.y);
                }
                else
                {
                     lst[i]->takeDamage(10);
                    target = glm::vec2(vec.x,vec.y);
                    return;
                }
                break;
        }
    }

    move(target.x, target.y);
    double radians = (atan2(vec.y - target.y , target.x - vec.x));
    double current = getAngle();
    double distance = radians - current;
    double loop = distance + ((radians<current)*2-1)*2*M_PI;
    bool bigger = (abs(distance) < abs(loop));
    //std::cout << loop << " " << distance << std::endl;
    changeAngle(current + .01*(distance*bigger + loop*!bigger));
}*/
