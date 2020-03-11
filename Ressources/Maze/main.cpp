/**
* from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
*
* C++ implementation by C. Ducottet
**/

#include <iostream>
#include "maze.h"

using namespace std;

int main()
{
    Maze maze(10,6);
    maze.generate();
    maze.display();
    return 0;
}


/* Example of generated maze:

    +--+--+--+--+--+--+--+--+--+--+
    |        |     |  |     |     |
    +--+--+  +  +  +  +--+  +--+  +
    |     |  |  |  |  |        |  |
    +  +--+  +--+  +  +--+--+  +  +
    |           |     |  |        |
    +  +  +--+  +  +--+  +  +--+  +
    |  |  |  |  |     |        |  |
    +  +--+  +  +--+  +  +--+  +--+
    |  |  |              |        |
    +--+  +--+  +--+  +  +--+  +--+
    |           |     |  |        |
    +--+--+--+--+--+--+--+--+--+--+

*/
