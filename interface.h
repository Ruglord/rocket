#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <memory.h>

#include "FreeTypeHelper.h"

#include "objects.h"
#include "camera.h"

struct WindowComponent
{

};

struct Button : public WindowComponent
{
    std::unique_ptr<SpriteComponent> background;
    std::unique_ptr<PositionComponent> position;
    std::string label = "";
    Font* font;
    Button();
    virtual void pressed();
    virtual void render(RenderProgram& program);
};

struct QuitButton : public Button
{
    bool hover = false;
    void pressed();
    QuitButton();
};

struct Window
{
    std::unique_ptr<SpriteComponent> background;
    std::unique_ptr<PositionComponent> position;
    Window();
    void render();
};

struct Quit : public Window
{
    QuitButton quit;

};

struct Interface
{
    Window* current = nullptr;
    Interface();
    void render(RenderController& controller);
};

#endif // INTERFACE_H_INCLUDED
