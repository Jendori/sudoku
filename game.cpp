#include "widgets.hpp"
#include "graphics.hpp"
#include "game.hpp"
#include <string>
#include <sstream>
#include <vector>
using namespace genv;


Game::Game(int x, int y, int sx, int sy): Widget(x,y,sx,sy)
{

    t = new Table(10,10,270,270);
    widgets.push_back(t);

}


void Game::event_loop(std::vector<Widget*> widgets)
{


  event ev;
    int focus = 0;
    while(gin >> ev && ev.keycode!=key_escape)
    {
        if (ev.type == ev_mouse && ev.button==btn_left)
        {
            for (size_t i=0; i<widgets.size(); i++)
            {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                    focus=i;
            }
        }
        widgets[focus]->handle(ev);
      //  widgets[focus]->highlight();
        if(focus>=1)
        {
          //  widgets[focus-1]->nohighlight();
        }
        if((unsigned) focus!=widgets.size()-1)
        {
           // widgets[widgets.size()-1]->nohighlight();
        }

        if(ev.type==ev_key && ev.keycode==key_tab)
        {
            focus++;
            if((unsigned) focus==widgets.size())
            {
                focus=0;

            }
        }
        for (Widget * w : widgets)
        {
            w->draw();
        }
        gout << refresh;
    }
}



void Game::draw()
{
    gout.open(500,500);
    gout<<color(150,150,150)<<move_to(0,0)<<box(500,500);
    for(Widget * wg : widgets)
    {
        wg->draw();
    }
    event_loop(widgets);
gout<<refresh;
}

void Game::handle(event ev)
{

}






