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

const int screenWidth = 640;
const int screenHeight = 640;
int main(int argc, char *argv[])
{

bool quit = false;
SDL_Event e;
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
SDL_Window* window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,screenWidth, screenHeight,SDL_WINDOW_OPENGL);
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


Font alef("alef.ttf",screenWidth,screenHeight);

srand(time(NULL));

std::vector<glm::vec3> vec;
vec.push_back({0,0,0});
loadSprites(screenWidth,screenHeight);

KeyManager manager;

CreatureWorld world;
SchoolOfFish f(0,100, world);
Rocket r(160,0,world);
Camera c (screenWidth,screenHeight,&r);
world.addCreature(f);
world.addCreature(r);
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

        manager.getKeys(e);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    double height = r.getRect().y;
    glClearColor(0,(.7-height/10000),1-height/10000,0);

    glUseProgram(program);
    //rocket.render(0,00,64,64,0);
    //rocket.renderInstanced(vec,64,64);
  // s.renderInstanced(vec,64,64);
  //  glm::vec4 region = c.getRegion();
  //  background.setPortion(region.x/screenWidth, region.y/screenHeight,1,1);
   // background.render(0,0,screenWidth,screenHeight,0);
    r.update(manager);
    c.adjust();
    c.render(r);
    world.update(c);
    alef.write(wordProgram,"Health: " + convert(r.getHealth()),0,0,1,{0,0,0});
   // box.render(0,0,64,64,0);

    SDL_GL_SwapWindow(window);
//std::cout << SDL_GetTicks() << std::endl;
SDL_Delay(1);
}


}
