#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

class MoveObject
{
public:
    MoveObject();
    virtual int move(int x, int y, int direction, int nextdirection)=0;
    virtual int getPosx()=0;
    virtual int getPosy()=0;
    virtual int getMoving()=0;
    int x, y, direction, nextdirection;
};

#endif // MOVEOBJECT_H
