#include "graphics.hpp"
#include "widgets.hpp"
#include "table.hpp"
#include <iomanip>
#include <vector>
#include <iostream>

using namespace genv;
using namespace std;

Table::Table(int x, int y, int sx, int sy) : Widget(x,y,sx,sy)
{
   int mezok[9][9]=
   {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
        {
            board[i][j]=mezok[j][i];
            board0[i][j]=mezok[j][i];
        }
    }

    valasztott.x=10;
    valasztott.y=10;
    hibas=false;
    complete=false;
}

void Table::draw()
{
    gout<<move_to(_x,_y)<<color(149,222,227)<<box(_size_x,_size_y);
    for(int i=0; i<9; ++i)
    {
        for(int j=0; j<9; ++j)
        {
            gout<<move_to(_x+1+(i)*_size_x/9, _y+1+(j)*_size_y/9)<<color(255,255,255)<<box(_size_x/9-2, _size_y/9-2);
            if(board[i][j]!=0)
            {
                if(board0[i][j]==board[i][j]){gout<<color(0,0,0);}
                if(board0[i][j]!=board[i][j]){gout<<color(0,180,210);}
                gout<<move_to(_x+(i)*_size_x/9+10, _y+(j+1)*_size_y/9-10)<<text(std::to_string(board[i][j]));
            }
            boardkoord[i][j][0].x = _x+1+(i)*_size_x/9;
            boardkoord[i][j][0].y = _y+1+(j)*_size_y/9;
            boardkoord[i][j][1].x = (_x+1+(i)*_size_x/9) + (_size_x/9-2);
            boardkoord[i][j][1].y = (_y+1+(j)*_size_y/9) + (_size_y/9-2);
        }
    }
    gout<<move_to(_x,400)<<color(0,0,0)<<text("Ha meg akarod valtoztatni egy mezo erteket, akkor");
    gout<<move_to(_x,415)<<color(0,0,0)<<text("kattints ra es a billentyuzeten nyomd meg az adott szamot!");
    gout<<move_to(_x,430)<<color(0,0,0)<<text("Ha uresse akarod tenni a mezot, nyomd meg a 0-t");
}

void Table::handle(genv::event ev)
{
    if (ev.type==ev_mouse && is_selected(ev.pos_x, ev.pos_y) && ev.button==btn_left)
    {
        for(int i=0; i<9; ++i)
        {
            for(int j=0; j<9; ++j)
            {
                if(ev.pos_x>boardkoord[i][j][0].x && ev.pos_x<boardkoord[i][j][1].x && ev.pos_y>boardkoord[i][j][0].y && ev.pos_y<boardkoord[i][j][1].y)
                {
                    valasztott.x=i;
                    valasztott.y=j;
                }
            }
        }
    }
    if (ev.type==ev_key && board0[valasztott.x][valasztott.y]==0)
    {
        if(ev.keycode==48){board[valasztott.x][valasztott.y]=0;}
        if(ev.keycode==49){board[valasztott.x][valasztott.y]=1;}
        if(ev.keycode==50){board[valasztott.x][valasztott.y]=2;}
        if(ev.keycode==51){board[valasztott.x][valasztott.y]=3;}
        if(ev.keycode==52){board[valasztott.x][valasztott.y]=4;}
        if(ev.keycode==53){board[valasztott.x][valasztott.y]=5;}
        if(ev.keycode==54){board[valasztott.x][valasztott.y]=6;}
        if(ev.keycode==55){board[valasztott.x][valasztott.y]=7;}
        if(ev.keycode==56){board[valasztott.x][valasztott.y]=8;}
        if(ev.keycode==57){board[valasztott.x][valasztott.y]=9;}
    }

    int hibadb1=0;
    for(int k=0; k<9; ++k)
    {
        for(int i=0; i<9; ++i)
        {
            for(int j=i+1; j<9; ++j)
            {
                if(board[k][i]==board[k][j] && board[k][i]!=0)
                {
                    hibadb1++;
                    hibas=true;
                }
            }
        }
    }
    int db=0;
    int hibadb2=0;
    for(int k=0; k<9; ++k)
    {
        for(int i=0; i<9; ++i)
        {
            for(int j=i+1; j<9; ++j)
            {
                if(board[i][k]==board[j][k] && board[i][k]!=0)
                {
                    hibadb2++;
                    hibas=true;
                }
            }
            if(board[k][i]==0){db++;}
        }
    }
    if (db==0 && !hibas){complete=true;}
    if (hibadb1==0 && hibadb2==0){hibas=false;}
    if (hibas)
    {
        gout<<move_to(_x,350)<<color(0,0,0)<<text("Hibás");
    }
    if (complete)
    {
        gout<<move_to(_x, 365)<<color(0,0,0)<<text("Kesz van");
    }
    hibadb1=0;
    hibadb2=0;
}
