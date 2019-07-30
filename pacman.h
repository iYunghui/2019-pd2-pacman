#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <moveobject.h>

class Pacman : public MoveObject
{

public:
    Pacman(int **map);
    int move(int pacx, int pacy, int direction, int nextdirection);
    int getPosx();
    int getPosy();
    int getMoving();
    int **Pacmap;

private:
    int posx, posy;
    bool moving;
};

#endif // PACMAN_H
