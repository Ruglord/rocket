#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <memory.h>

#include "FreeTypeHelper.h"

#include "objects.h"
#include "camera.h"
#include "traits.h"
#include "image.h"
#include "rocket.h"

struct WindowComponent
{

};

struct Button : public WindowComponent
{
    bool hover = false;
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
    void pressed();
    QuitButton(double x, double y);
};

struct TraitButton : public Button
{
    Trait* trait = nullptr;
    TraitButton(double x, double y, int w, int h,Trait* tr);
    void pressed();
    void render(RenderProgram& program);
};

struct Window
{
    Rect rect;
    std::unique_ptr<SpriteComponent> background;
    std::unique_ptr<PositionComponent> position;
    std::vector<Button*> buttons;
    void init();
    Window();
    void render();
    virtual void onOpen()
    {

    }
    ~Window();
};


struct TraitsWindow : public Window
{
    void onOpen();
};

struct TraitIcon //indicates which 3 traits are currently selected.
{
    Trait* trait = nullptr;
    Sprite* sprite = &traitIcon;
};

struct Interface
{
    TraitIcon icons[numberOfTraits];
    Window* current = nullptr;
    Window quit;
    TraitsWindow log;
    Interface();
    void render();
    void init();
    void update();
    void switchWindow(Window* window);
};

#endif // INTERFACE_H_INCLUDED
