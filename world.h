#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "render.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "render.h"

class Chunk;
class World //represents the actual environment
{
    std::vector<Chunk> landscape;
public:
    World();
    void render();
    Chunk& getPoints(double x, double y);

};

class ChunkSprite;

struct Chunk //represents a "chunk of land". This will be used for rendering purposes
{
    ChunkSprite* texture = nullptr; //the texture of this chunk
    glm::vec4 area = {0,0,0,0}; //the coordinates and dimensions of the chunk. This is basically a rect that represents the center of the chunk without any
                                //protrusions
    std::vector<glm::vec2> points; //these 4 vectors represent the heights of the protrusions from the main area.
    int w=0, h = 0; //the width and height of the tiles.
    RenderProgram* request = nullptr;
    Chunk(const glm::vec4& rect, const std::vector<glm::vec2>& TOP, ChunkSprite& sprite);
    void render();
};

class ChunkSprite : public Sprite
{

public:
    ChunkSprite()
    {

    }
    ChunkSprite(std::string source, bool transparent);
    void render(RenderProgram& program,int w, int h,const std::vector<glm::vec2>& points, const glm::vec4& rect, const glm::vec2& displacement );
};

#endif // WORLD_H_INCLUDED
