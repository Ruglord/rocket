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
#include "scans.h"

std::map<EntityID, bool> Game::scannedCreatures;
std::vector<Trait*> Game::traitList;
RenderProgram RenderController::basic;
RenderProgram RenderController::scanning;
RenderProgram RenderController::wordProgram;
double Game::currentTime = 0;
double Game::deltaTime = 0;
Interface Game::interface;
const double Game::perMilSecond = 5;
int Game::screenWidth = 0;
int Game::screenHeight = 0;
RenderController* Game::renderer;
Rocket* Game::player;
CreatureWorld Game::world;
InputController Game::input;
int main(int argc, char *argv[])
{
bool quit = false;
SDL_Event e;
SDL_Init(SDL_INIT_VIDEO);
SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

//GLuint p = glCreateProgram();
Game::setDimensions();
glm::vec2 dimen = Game::getDimentions();

SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
SDL_Window* window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,dimen.x,dimen.y,SDL_WINDOW_OPENGL );
SDL_GL_CreateContext(window);
GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
glEnable( GL_BLEND );
loadSprites(dimen.x,dimen.y);
Game::init();
SDL_StopTextInput();

initScans();

GLuint wordProgram = glCreateProgram();
int wordFragment =loadShaders("shaders/fragment/wordFragment.h",GL_FRAGMENT_SHADER);
int wordVertex = loadShaders("shaders/vertex/wordVertex.h",GL_VERTEX_SHADER);
glAttachShader(wordProgram,wordVertex);
glAttachShader(wordProgram,wordFragment);
glLinkProgram(wordProgram);


glDeleteShader(wordFragment);
glDeleteShader(wordVertex);

RenderProgram testProgram("shaders/vertex/vertexShader.h","shaders/fragment/fragmentShader.h");
        testProgram.setMatrix4fv("projection",glm::value_ptr(glm::ortho(0.0f, (float)dimen.x,(float)dimen.y, 0.0f, -1.0f, 1.0f)));

srand(time(NULL));


Shark shark(-100,0);
CreatureWorld* world = &Game::world;
world->addCreature(shark);

Sprite background;
background.init(dimen.x,dimen.y,"sprites/cloudBackground.png",false);


//rocket.mirror();
//box.mirror();
//double angle = 0;
int fps;
while(quit == false)
{
 //   std::cout << SDL_GetTicks() << std::endl;
 fps = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);
    double height = 0;
    glClearColor(0,(.7-height/10000),1-height/10000,1);
  //  box.render(testProgram,0,0,640,640,0);
    Game::everyTick(e);
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
          quit = true;
        }
    }
    //box.render(program,0,0,64,64,angle);
   // angle += .001;
    SDL_GL_SwapWindow(window);
//std::cout << SDL_GetTicks() << std::endl;
    //alef.write(wordProgram,"FPS: " + convert(fps),0,0,1,{0,0,0});
   // std::cout << SDL_GetTicks() - fps<< std::endl;
SDL_Delay(1);
}


}
