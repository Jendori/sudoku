#include "game.hpp"
#include <vector>
#include <string>

using namespace std;
using namespace genv;

int main()
{
    Game *g=new Game(10,10,50,50);
    g->draw();
    return 0;
}
