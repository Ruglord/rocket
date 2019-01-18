#include "world.h"
#include "game.h"
World::World()
{
    landscape.push_back(Chunk({-500,0,800,600},{{-500,0},{-100,-100},{300,500}}, dirt));
}
void World::render()
{
    int size = landscape.size();
    for (int i = 0; i < size; i ++)
    {
        Game::renderer->render(landscape[i]);
    }
}

Chunk& World::getPoints(double x, double y)
{
    return landscape[0];
}

Chunk::Chunk(const glm::vec4& rect,const std::vector<glm::vec2>& TOP, ChunkSprite& sprite)
{
    area = rect;
 request = &Game::renderer->basic;
   points = TOP;
   texture = &sprite;
    /*int max = std::max(std::max(topS,botS),std::max(rightS,leftS));
    for (int i = 0; i < max; ++i)
    {
        if (i < topS)
        {
            top.push_back(TOP[i]);
        }
        if (i < botS)
        {
            bot.push_back(BOT[i]);
        }
        if (i < rightS)
        {
            right.push_back(RIGHT[i]);
        }
        if (i < leftS)
        {
            left.push_back(LEFT[i]);
        }
    }*/
}


ChunkSprite::ChunkSprite(std::string source, bool transparent) : Sprite(source, transparent)
{

}

void ChunkSprite::render(RenderProgram& program, int w, int h,const std::vector<glm::vec2>& points, const glm::vec4& rect, const glm::vec2& displacement)
{
    //std::cout << modified.size() << std::endl;
    if (w == 0)
    {
        w = width;
    }
    if (h == 0)
    {
        h = height;
    }
    modified.clear();
    modIndices.clear();
    int size = points.size();
    const glm::vec4* area = &rect;
    int mod = 0; //mod is an iterator
    for (int i = 0; i < size; ++i)
    {
        const glm::vec2* current = &points[i];
        modified.push_back(current->x-displacement.x); //coordinates to be rendered to
        modified.push_back(current->y-displacement.y);
        modified.push_back(current->x/w); //texture coordinates
        modified.push_back(current->y/h);

        double x = std::min(std::max(current->x,area->x),area->x + area->z); //render coordinates of the point on the rectangle closest to current
        double y = std::min(std::max(current->y,area->y),area->y + area->a);
        bool onRect = current->x == x && current->y == y; //whether or not the point is on the rect.
        if (!onRect)
        {
            modified.push_back(x-displacement.x); //this is the information for the point closest to the current index that is on the rectangle
            modified.push_back(y-displacement.y);
            modified.push_back((x)/w);
            modified.push_back((y)/h);
            if (i < size -1)
            {
                modIndices.push_back(mod); //first, render the current index.
                modIndices.push_back(mod+2); //next, render the next one.
                modIndices.push_back(mod+1); //finally, render the index closest to the current index on the area rectangle.
            }
            if (i > 0 ) //It takes 2 triangles to render one protrusion. Here, we render the second one for the previous protrusion
            {
                modIndices.push_back(mod); //current index
                modIndices.push_back(mod+1); //then index on the rectangle
                modIndices.push_back(mod-1); //finally, the index on the rectangle closest to the previous index
            }
        }
        mod += 1 + !onRect;
    }
   /* for (int i = 0; i < modIndices.size(); i ++)
    {
        std::cout << modIndices[i] << std::endl;
    }*/
   // std::cout << modIndices[3] << " " << modIndices[4] << " " << modIndices[5] << std::endl;
  // std::cout << modIndices.size();
    renderInstanced(program,{{{0,0,2,2}}});
    for (int i = 0; i < 4; i ++) //render the base. The base is easily rendered because it's just a square. The only adjustment we need to make is make each
    {                            //tile the size of w and h.
        modified[4*i+2] = ((area->x+area->z*(i%2))/w);
        modified[4*i+3] = ((area->y+area->a*(i<2))/h);
    }

    renderInstanced(program,{{{area->x - displacement.x,area->y-displacement.y,area->z,area->a}}});
}
