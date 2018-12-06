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
    virtual void render();
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
    void render();
};

struct Window
{
    Rect rect = {0,0,0,0};
    std::unique_ptr<SpriteComponent> background;
    std::unique_ptr<PositionComponent> position;
    std::vector<Button*> buttons;
    std::vector<Window*> subWindows;
    virtual void init();
    Window();
    virtual void render();
    virtual void onOpen()
    {

    }
    ~Window();
};

struct TraitIcon : public Button//indicates which 3 traits are currently selected.
{
   static constexpr float iconWidth = 64*9/10; //width of the traits
    Trait* trait = nullptr;
    void render(double x, double y, double scale);
    void render();
    TraitIcon(double x, double y);
    void pressed();
};

struct TraitsWindow : public Window
{
    int vertPadding = 0; //padding for the window
    int horizPadding = 0;
    int buttonWidth = 0; //width of the traitbuttons, not the traitIcons
    int buttonHeight = 0;
    int perRow = 0;
    int spacing = 0;
    int traitsWidth = 0; //width taken up by the traits section
    void onOpen();
    Window* traitsBar; //shows all the unlocked traits
    Window* selectedTraits;
    void render();
    void init();
};

struct Interface
{
    static std::shared_ptr<TraitIcon> icons[numberOfTraits];
    static Window* current;
    static Window quit;
    static TraitsWindow log;
    Interface();
    static void render();
    static void init();
    static void update();
    static void renderTraitIcons(double x, double y, double scale);
    static void switchWindow(Window* window);
};

#endif // INTERFACE_H_INCLUDED
