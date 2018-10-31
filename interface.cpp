#include "interface.h"
#include "game.h"
#include "image.h"
Button::Button(double x, double y, int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Button::pressed()
{

}

void Button::render(RenderProgram& program)
{
        sprite.get()->render(RenderController::basic,rect.x-10,rect.y,rect.w+20,rect.h+10);
        glm::vec2 dimen = font->write(program,"textColor",label,rect.x,rect.y+rect.h,1,{0,0,0});

}

void QuitButton::pressed()
{
    exit(EXIT_SUCCESS);
}

QuitButton::QuitButton(double x, double y) : Button(x,y,0,0)
{
    label = "Quit";
    font = &alef;
    sprite.reset(new SpriteComponent);
    sprite.get()->setSprite(frame);
    glm::vec2 dimen = font->getDimen(label,1);
    rect.w = dimen.x;
    rect.h = dimen.y;
}

Window::Window()
{

}

void Window::render()
{
    background.get()->render(RenderController::basic,.05*Game::screenWidth,.05*Game::screenHeight,.9*Game::screenWidth, .9*Game::screenHeight);
    int size = buttons.size();
    for (int i = 0; i < size; i ++)
    {
        buttons[i]->render(RenderController::wordProgram);
    }
}

Window::~Window()
{
    buttons.clear();
}

Interface::Interface()
{

}

void Interface::update()
{
    if (Game::input.mouseManager.findNumber(SDL_BUTTON_LEFT) != -1 && current != nullptr)
    {
        int x, y;
        SDL_GetMouseState(&x,&y);
        for (std::vector<Button*>::const_iterator it = current->buttons.begin(); it != current->buttons.end(); it ++)
        {
            Button* current = *it;
            if (PointInRect({x,y},current->rect))
                {
                    current->pressed();
                }
        }
    }
}

void Interface::init()
{
    quit.background.reset(new SpriteComponent);
    quit.background.get()->setSprite(frame);
    quit.position.reset(new PositionComponent);
    quit.buttons.push_back(new QuitButton(100,100));
}

void Interface::render()
{
    current->render();
}
