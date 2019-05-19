#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include "widgets.hpp"
#include "graphics.hpp"
#include "table.hpp"
#include <vector>
#include <string>

using namespace std;
using namespace genv;

//class Widget;

class Game: public Widget
{
protected:
    std::vector <Widget*> widgets;
    Table* t;

public:
    Game(int x, int y, int sx, int sy);
    ~Game();
    virtual void draw();
    void event_loop(std::vector<Widget*> widgets);
    virtual void handle(genv::event ev);
};

#endif // GAME_HPP_INCLUDED
