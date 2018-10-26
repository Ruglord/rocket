#include "interface.h"
#include "game.h"
Button::Button()
{

}

void Button::pressed()
{

}

void Button::render(RenderProgram& program)
{
    font->write(program,"shade",label,0,0,1,{0,0,0});
}

void QuitButton::pressed()
{
    exit(EXIT_SUCCESS);
}

QuitButton::QuitButton()
{
    label = "Quit";
}

Window::Window()
{

}

void Window::render()
{
    background.get()->render(RenderController::basic,.05*Game::screenWidth,.05*Game::screenHeight,.9*Game::screenWidth, .9*Game::screenHeight);
}

Interface::Interface()
{

}

void Interface::render(RenderController& controller)
{

}
