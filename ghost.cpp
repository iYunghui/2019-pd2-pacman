#include <ghost.h>

Ghost::Ghost(int **map) {
    Ghostmap = map;
    moving = true;
}
int Ghost::move(int ghostx, int ghosty, int direction, int nextdirection) {
    int x = (ghosty-75)/15;
    int y = (ghostx-30)/15;
    if(nextdirection==1 && (x-1)>=0 && Ghostmap[x-1][y]!=3 && Ghostmap[x-1][y]!=4) {
        x = x-1;
        direction = nextdirection;
    }
    else if(nextdirection==2 && (y+1)<=26 && Ghostmap[x][y+1]!=3 && Ghostmap[x][y+1]!=4){
        y = y+1;
        direction = nextdirection;
    }
    else if(nextdirection==2 && x==13 && y==26){
        y = 0;
        direction = nextdirection;
    }
    else if(nextdirection==3 && (x+1)<=28 && Ghostmap[x+1][y]!=3 && Ghostmap[x+1][y]!=4){
        x = x+1;
        direction = nextdirection;
    }
    else if(nextdirection==4 && (y-1)>=0 && Ghostmap[x][y-1]!=3 && Ghostmap[x][y-1]!=4){
        y = y-1;
        direction = nextdirection;
    }
    else if(nextdirection==4 && x==13 && y==0){
        y = 26;
        direction = nextdirection;
    }
    else if(direction==1 && (x-1)>=0 && Ghostmap[x-1][y]!=3 && Ghostmap[x-1][y]!=4) {
        x = x-1;
    }
    else if(direction==2 && (y+1)<=26 && Ghostmap[x][y+1]!=3 && Ghostmap[x][y+1]!=4){
        y = y+1;
    }
    else if(direction==3 && (x+1)<=28 && Ghostmap[x+1][y]!=3 && Ghostmap[x+1][y]!=4){
        x = x+1;
    }
    else if(direction==4 && (y-1)>=0 && Ghostmap[x][y-1]!=3 && Ghostmap[x][y-1]!=4){
        y = y-1;
    }

    posx = y*15+30;
    posy = x*15+75;

    if(posx!=ghostx || posy!=ghosty)
        moving = true;
    else
        moving = false;
    return direction;
}

int Ghost::getPosx() {
    return posx;
}

int Ghost::getPosy() {
    return posy;
}

int Ghost::getMoving() {
    return moving;
}
