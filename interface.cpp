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

void Button::render()
{
        sprite.get()->render(RenderController::basic,rect.x-10,rect.y,rect.w+20,rect.h+10);
        if (label != "")
        {
                    glm::vec2 dimen = font->write(RenderController::wordProgram,"textColor",label,rect.x,rect.y+rect.h,1,{0,0,0});
        }

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
   for (int i = 0; i < numberOfTraits; i ++)
   {
    Trait** current = &Interface::icons[i].get()->trait;
       if (*current == nullptr) //find the next blank spot and add the trait in
       {
           *current = trait;
           break;
       }
       else if (*current == trait) //if the player already has the trait, exit the function
       {
           return;
       }
   }

}
void TraitButton::render()
{
        sprite.get()->render(RenderController::basic,rect.x-10,rect.y,rect.w+20,rect.h+10);
}

Window::Window()
{

}

void Window::init()
{
    rect.x = .05*Game::screenWidth;
    rect.y = .05*Game::screenHeight;
    rect.w = .9*Game::screenWidth;
    rect.h =  .9*Game::screenHeight;
}

void Window::render()
{
    background.get()->render(RenderController::basic,rect.x,rect.y,rect.w,rect.h);
    int size = buttons.size();
    for (int i = 0; i < size; i ++)
    {
        buttons[i]->render();
    }
    for (int i = 0; i < subWindows.size(); i ++)
    {
        subWindows[i]->render();
    }
}

Window::~Window()
{
    buttons.clear();
}
void TraitsWindow::init()
{
    Window::init();
    vertPadding = rect.h/40*(float)Game::screenWidth/Game::screenHeight;
     horizPadding = rect.w/25;
     buttonWidth = 32;
    buttonHeight = 16;
     perRow = 10;
    spacing = (rect.w - horizPadding*2)/perRow - buttonWidth;
     traitsWidth = rect.w/16; //width taken up by the traits section

     traitsBar = new Window();
     traitsBar->rect = {rect.x,rect.y,traitsWidth,rect.h};

     selectedTraits = new Window();
     selectedTraits->rect = {rect.x+traitsWidth, rect.y, rect.w-traitsWidth,rect.h};

     traitsBar->background.reset(new SpriteComponent);
     traitsBar->background.get()->setSprite(frame);

     selectedTraits->background.reset(new SpriteComponent);
     selectedTraits->background.get()->setSprite(frame);
    subWindows.push_back(traitsBar);
     subWindows.push_back(selectedTraits);

     for (int i = 0; i < numberOfTraits; i ++)
     {
        Rect* curr= &(Interface::icons[i].get()->rect);
          curr->x= rect.x + traitsWidth/2 + rect.w/2-TraitIcon::iconWidth/2+(i-numberOfTraits/2)*(spacing+TraitIcon::iconWidth);
          curr->y = rect.y+rect.h/2;
         selectedTraits->buttons.push_back(Interface::icons[i].get());
     }

}

void TraitsWindow::onOpen()
{
    int size = Game::traitList.size();
    int otherSize = traitsBar->buttons.size();
    for (int i = 0 ; i < size; i ++)
    {
        if (i + 1 > traitsBar->buttons.size() || ((TraitButton*)(traitsBar->buttons[i]))->trait->id != Game::traitList[i]->id)
        {
            traitsBar->buttons.insert(traitsBar->buttons.begin() + std::min(i,(int)traitsBar->buttons.size()) ,new TraitButton(rect.x + horizPadding + ((i%perRow)*(spacing+buttonWidth))%traitsWidth,rect.y+ vertPadding + i/perRow*(buttonHeight+spacing),buttonWidth, buttonHeight,Game::traitList[i]));
        }

    }
}

void TraitsWindow::render()
{
    Window::render();
    //background.get()->render(RenderController::basic,rect.x,rect.y,rect.w,rect.h);

       // double iconCenter = rect.x + traitsWidth/2 + rect.w/2;
    //Interface::renderTraitIcons(iconCenter,rect.y+rect.h/2,1);

}

TraitIcon::TraitIcon(double x, double y) : Button(x,y,iconWidth,iconWidth)
{
        sprite.reset(new SpriteComponent);
         sprite.get()->setSprite(traitIcon);
}

void TraitIcon::render(double x, double y, double scale)
{
        Rect blit = {x,y,rect.w*scale,rect.h*scale};
        sprite.get()->render(RenderController::basic,blit.x,blit.y,blit.w,blit.h);
        if (trait)
        {
            trait->icon.render(RenderController::basic,blit.x+blit.w/2-iconWidth/2,blit.y+blit.h/2-iconWidth/2,iconWidth,iconWidth);
        }
}

void TraitIcon::render()
{
    render(rect.x,rect.y,1);
}

void TraitIcon::pressed()
{
    trait = nullptr;
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
            Button* curButton = *it;
            if (PointInRect({x,y},curButton->rect))
                {
                    curButton->pressed();
                }
        }
         for (std::vector<Window*>::const_iterator win = current->subWindows.begin(); win != current->subWindows.end(); win ++)
        {
            for (std::vector<Button*>::const_iterator it = (*win)->buttons.begin(); it != (*win)->buttons.end(); it ++)
            {
                Button* current = *it;
                if (PointInRect({x,y},current->rect))
                    {
                        current->pressed();
                    }
            }
        }
    }

}

void Interface::init()
{
    icons[0].reset(new TraitIcon(0,0));
    icons[1].reset(new TraitIcon(0,0));
    icons[2].reset(new TraitIcon(0,0));

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

void Interface::renderTraitIcons(double x, double y, double scale) //x and y are the CENTER of where the trait icons are at
{
    double spacing = 100;
    for (int i = 0; i < numberOfTraits; i ++)
    {
        icons[i]->render(x-TraitIcon::iconWidth/2+(i-numberOfTraits/2)*(spacing+TraitIcon::iconWidth),y,1);
    }
}

void Interface::render()
{
    if (current)
    {
        current->render();
    }
    else
    {
        renderTraitIcons(Game::screenWidth/2, Game::screenHeight*9/10,1);
    }
}
