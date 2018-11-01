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
    Rect rect;
    std::unique_ptr<SpriteComponent> sprite;
    std::unique_ptr<PositionComponent> position;
    std::string label = "";
    Font* font;
    Button(double x, double y, int w, int h);
    virtual void pressed();
    virtual void render(RenderProgram& program);
};

struct QuitButton : public Button
{
    bool hover = false;
    void pressed();
    QuitButton(double x, double y);
};

struct Window
{
    std::unique_ptr<SpriteComponent> background;
    std::unique_ptr<PositionComponent> position;
    std::vector<Button*> buttons;
    Window();
    void render();
    ~Window();
};

struct Quit : public Window
{
    QuitButton quit;

};

struct Interface
{
    Window* current = nullptr;
    Window quit;
    Window log;
    Interface();
    void render();
    void init();
    void update();
};

#endif // INTERFACE_H_INCLUDED
