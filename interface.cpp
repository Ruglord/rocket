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

TraitButton::TraitButton(double x, double y, int w, int h, Trait* tr) : Button(x,y,w,h)
{
    sprite.reset(new SpriteComponent);
    sprite.get()->setSprite(frame);
    trait = tr;
}
void TraitButton::pressed()
{
    if (Game::player->traits[0].get() != trait)
    {
    Game::player->traits[0].reset(trait);
    }
}
void TraitButton::render(RenderProgram& program)
{
        sprite.get()->render(RenderController::basic,rect.x-10,rect.y,rect.w+20,rect.h+10);
}

Window::Window()
{

}

void Window::init()
{
    rect = {.05*Game::screenWidth,.05*Game::screenHeight,.9*Game::screenWidth, .9*Game::screenHeight};
}

void Window::render()
{
    background.get()->render(RenderController::basic,rect.x,rect.y,rect.w,rect.h);
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

void TraitsWindow::onOpen()
{
    int size = Game::traitList.size();
    int horizPadding = rect.w/25;
    int vertPadding = rect.h/40*(float)Game::screenWidth/Game::screenHeight;
    int buttonWidth = 32;
    int buttonHeight = 16;
    int perRow = 10;
    int spacing = (rect.w - horizPadding*2)/perRow - buttonWidth;
    int traitsWidth = rect.w/10;
    for (int i = 0 ; i < size; i ++)
    {
        if (i + 1 > buttons.size() || ((TraitButton*)(buttons[i]))->trait->id != Game::traitList[i]->id)
        {
            buttons.insert(buttons.begin() + std::min(i,(int)buttons.size()) ,new TraitButton(rect.x + horizPadding + ((i%perRow)*(spacing+buttonWidth))%traitsWidth,rect.y+ vertPadding + i/perRow*(buttonHeight+spacing),buttonWidth, buttonHeight,Game::traitList[i]));
        }
    }
}

Interface::Interface()
{

}

void Interface::switchWindow(Window* window)
{
    if (window != current)
    {
        if (window)
        {
            window->onOpen();
        }
        current = window;
    }
    else
    {
        current = nullptr;
    }

}

void Interface::update()
{
    if (Game::input.mouseManager.getJustClicked() == SDL_BUTTON_LEFT && current != nullptr)
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
    for (int i = 0; i < numberOfTraits; i ++)
    {
        icons[i].trait = Game::player->traits[i].get();
    }
}

void Interface::init()
{
    quit.init();
    quit.background.reset(new SpriteComponent);
    quit.background.get()->setSprite(frame);
    quit.position.reset(new PositionComponent);
    quit.buttons.push_back(new QuitButton(100,100));

    log.init();
    log.background.reset(new SpriteComponent);
    log.background.get()->setSprite(frame);
    log.position.reset(new PositionComponent);
}

void Interface::render()
{
    if (current)
    {
        current->render();
    }
    int spacing = 100;
    int width = 64;
    int iconWidth = 64*9/10;
    double y = Game::screenHeight*9/10;
    for (int i = 0; i < numberOfTraits; i ++)
    {
        double x = Game::screenWidth/2 - width/2-(width+spacing)*(numberOfTraits/2-i);
        icons[i].sprite->renderInstanced(RenderController::basic,{{{x,y,width,width}}});
        if (icons[i].trait)
        {
            icons[i].trait->icon.render(RenderController::basic,x+width/2-iconWidth/2,y+width/2-iconWidth/2,iconWidth,iconWidth);
        }
    }
}
