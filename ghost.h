#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include <moveobject.h>

class Ghost : public MoveObject
{
public:
    Ghost(int **map);
    int move(int ghostx, int ghosty, int direction, int nextdirection);
    int getPosx();
    int getPosy();
    int getMoving();
    int **Ghostmap;

private:
    int posx, posy;
    bool moving;
};

#endif // GHOST_H

