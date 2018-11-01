#include "creatures.h"
#include "image.h"
#include "game.h"
void AIComponent::AI(Creature& e) {


}

void ScanComponent::setScanning(bool value) //if value is true, start the scanning
{
    scanning = value;
}
void ScanComponent::update(SpriteComponent* sprite)
{
    if (scanning && scanTime > 0 )
    {
        sprite->request = &RenderController::scanning;
        sprite->request->setVec3fv("shade",{abs(sin(SDL_GetTicks()/100.0)),abs(sin(SDL_GetTicks()/1000.0)),abs(sin(SDL_GetTicks()))});
        scanning = false;
        scanTime -= Game::deltaTime;
    }
}

Creature::Creature(int ID) : IDed(ID)
{
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
void CreatureSprite::incrementAngle(double target, double speed) //add target angle to the current angle. Speed is the rate at which the angle should be added
{
    double distance = target-angle;
    if (abs(target-angle) < abs(target+2*M_PI-angle))
    {
        distance = target-angle;
    }
    else
    {
        distance = target+2*M_PI-angle;
    }
        changeAngle(angle+distance*std::min(speed,1.0));
}

void CreaturePosition::move(double x, double y, Creature& c)//moves creature in the direction x, y;
{
    moveTowards(boundingRect.x + x, boundingRect.y + y,c);
}

double CreaturePosition::getSpeed()
{
    double total = 0;
    for (std::list<std::pair<double,int>>::iterator i= speedMods.begin(); i  != speedMods.end(); i ++)
    {
        total += std::get<0>(*i);

    }
    return speed + total;
}

void CreaturePosition::setSpeed(double sp)
{
    speed = sp;
}

void CreaturePosition::moveTowards(double x, double y, Creature& c) //moves the creatures towards a point.
{
    glm::vec4 hit = boundingRect;
    double radians = atan2(y-hit.y, x-hit.x );
   // std::cout << radians << std::endl;
   double currentSpeed = getSpeed();
    double horizSpeed = currentSpeed*cos(radians);
    if (abs(x - hit.x) < abs(horizSpeed))
    {
        horizSpeed = x-hit.x;
    }
    double vertSpeed = currentSpeed*sin(radians);
    if (abs(y - hit.y) < abs(vertSpeed))
    {
        vertSpeed = y-hit.y;
    }
    changeCoords(hit.x + horizSpeed*Game::deltaTime, hit.y + vertSpeed*Game::deltaTime);

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
        if (vecIntersect(bigBox,curCenter) && current != &c)
        {
            lst.push_back(current);
        }
    }
    if (&c != Game::player)
    {
        glm::vec4 curCenter=Game::player->position.get()->getRect();
        if (vecIntersect(bigBox,curCenter))
        {
            lst.push_back(Game::player);
        }
    }
    return lst;
}
std::vector<Creature*> CreatureWorld::getCreatures()
{
    return creatures;
}

void CreatureWorld::update(Camera& c)
{
   /* int size = creatures.size();
    for (int i = 0 ; i <size; i ++)
    {
        creatures[i]->getAI().AI(*creatures[i]);
        c.render(*creatures[i]->position.get(),*creatures[i]->sprite.get());
    }*/
}

CreatureWorld::~CreatureWorld()
{
    creatures.clear();
    nearestCreatures.clear();
}


SchoolOfFish::SchoolOfFish(double x, double y) : Creature( SCHOOLOFFISH)
{
    sprite.reset(new SchoolOfFishSprite);
    sprite.get()->setSprite(fish);
    AI.reset(new SchoolOfFishAI);
    position.get()->setRect(glm::vec4(x,y,92,69));
    position.get()->setSpeed(.5);
    health.get()->health = 10;
}

void SchoolOfFishSprite::render(RenderProgram& program,double x, double y, double w, double h)
{
     Sprite* s = &(getSprite());
    std::vector<SpriteParameter> points;
    for (int i = 0; i < 16; i ++)
    {
        int sign = ((i%2 == 0)*(-2) + 1);
        points.push_back({{x + (sign*(i%4)*w/3),y + h/4*sin((x/5 + i*M_PI/4)/10),w/12,h/12}});
    }
    s->renderInstanced(program,points);
 // s->render(program,x,y,w/2,h/2,0);
}

Shark::Shark( double x, double y) : Creature(SHARK)
{
  sprite.reset(new CreatureSprite);
    sprite.get()->setSprite(sharkSprite);
    AI.reset(new SharkAI);
    position.get()->setRect(glm::vec4(x,y,256,128));
    position.get()->setSpeed(.5);
    health.get()->health = 20;
    scan.reset(new ScanComponent);
    scan.get()->scanTime = 2000;
}

void SharkAI::AI(Creature& shark)
{

      glm::vec4 vec = shark.position.get()->getRect();
    std::vector<Creature*> lst = (Game::world.getNearestCreatures(100,shark));
    int size = lst.size();
    glm::vec2 target(vec.x +vec.z+ shark.position.get()->getSpeed(),vec.y);
    for (int i = 0; i < size; i ++)
    {
        if (lst[i]->getID()== ROCKET)
        {
            glm::vec4 hitbox = lst[i]->position.get()->getRect();
             //   if (!vecIntersect(vec,hitbox))
                    target = glm::vec2(hitbox.x,hitbox.y);

                break;
        }
    }
    shark.position.get()->moveTowards(target.x, target.y,shark);
    ((CreatureSprite*)(shark.sprite.get()))->incrementAngle(atan2(target.y-(vec.y),target.x-(vec.x+vec.z*.75)),.01);
    //std::cout << loop << " " << distance << std::endl;
 //   changeAngle(current + .01*(distance*bigger + loop*!bigger));
}
