#ifndef TABLE_HPP_INCLUDED
#define TABLE_HPP_INCLUDED
#include "widgets.hpp"
#include "graphics.hpp"
#include <vector>
#include <string>

using namespace std;
using namespace genv;

struct koord
{
    int x;
    int y;
};

class Table : public Widget
{
protected:
    unsigned int board[9][9];
    unsigned int board0[9][9];
    koord boardkoord[9][9][2];
    koord valasztott;
    bool hibas;
public:
    Table(int x, int y, int sx, int sy);
    ~Table();
    virtual void draw();
    virtual void handle(genv::event ev);
};

#endif // TABLE_HPP_INCLUDED
