#include <iostream>

#include <SDL.h>
#include <glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <time.h>

#include <render.h>
#include <sparkles.h>
#include <FreeTypeHelper.h>

#include <SDLhelper.h>

#include "image.h"
#include "objects.h"
#include "creatures.h"
#include "rocket.h"
#include "camera.h"
#include "game.h"
int Game::screenWidth = 0;
int Game::screenHeight = 0;
RenderController* Game::renderer;
Rocket* Game::player;
CreatureWorld Game::world;
InputController Game::input;
int main(int argc, char *argv[])
{
    glm::vec4 a = {0,0,100,100};
    glm::vec4 b = {-100,-100,100,100};
   // std::cout << vecIntersect(a,b) << std::endl;
bool quit = false;
SDL_Event e;
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

Game::init();
glm::vec2 dimen = Game::getDimentions();

SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
SDL_Window* window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,dimen.x,dimen.y,SDL_WINDOW_OPENGL );
SDL_GL_CreateContext(window);
SDL_StopTextInput();
glewExperimental = true;
glewInit();
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable( GL_BLEND );
glEnable(GL_DEBUG_OUTPUT);
int vertexShader = loadShaders("shaders/vertex/vertexShader.h",GL_VERTEX_SHADER);
int fragmentShader = loadShaders("shaders/fragment/fragmentShader.h", GL_FRAGMENT_SHADER);
program = glCreateProgram();
glAttachShader(program,vertexShader);
glAttachShader(program,fragmentShader);
glLinkProgram(program);

GLuint wordProgram = glCreateProgram();
int wordFragment =loadShaders("shaders/fragment/wordFragment.h",GL_FRAGMENT_SHADER);
int wordVertex = loadShaders("shaders/vertex/wordVertex.h",GL_VERTEX_SHADER);
glAttachShader(wordProgram,wordVertex);
glAttachShader(wordProgram,wordFragment);
glLinkProgram(wordProgram);
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
glDeleteShader(wordFragment);
glDeleteShader(wordVertex);


Font alef("alef.ttf",dimen.x,dimen.y);

srand(time(NULL));

std::vector<glm::vec3> vec;
vec.push_back({0,0,0});
loadSprites(dimen.x,dimen.y);


SchoolOfFish f(0,-400);
CreatureWorld* world = &Game::world;
world->addCreature(f);


//rocket.mirror();
//box.mirror();
while(quit == false)
{
 //   std::cout << SDL_GetTicks() << std::endl;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
          quit = true;
        }
    }
    glClear(GL_COLOR_BUFFER_BIT);
    double height = 0;
    glClearColor(0,(.7-height/10000),1-height/10000,0);

    glUseProgram(program);
    //rocket.render(0,00,64,64,0);
    //rocket.renderInstanced(vec,64,64);
  // s.renderInstanced(vec,64,64);
  //  glm::vec4 region = c.getRegion();
  //  background.setPortion(region.x/screenWidth, region.y/screenHeight,1,1);
   // background.render(0,0,screenWidth,screenHeight,0);
    Game::everyTick(e);
//    alef.write(wordProgram,"Health: " + convert(r.health.get()->getHealth()),0,0,1,{0,0,0});
   // box.render(0,0,64,64,0);

    SDL_GL_SwapWindow(window);
//std::cout << SDL_GetTicks() << std::endl;
SDL_Delay(1);
}


}
