#include <pacman.h>

Pacman::Pacman(int **map) {
    Pacmap = map;
}

int Pacman::move(int pacx, int pacy, int direction, int nextdirection) {
    int x = (pacy-75)/15;
    int y = (pacx-30)/15;
    if(nextdirection==1 && (x-1)>=0 && Pacmap[x-1][y]!=3 && Pacmap[x-1][y]!=4) {
        x = x-1;
        direction = nextdirection;
    }
    else if(nextdirection==2 && (y+1)<=26 && Pacmap[x][y+1]!=3 && Pacmap[x][y+1]!=4){
        y = y+1;
        direction = nextdirection;
    }
    else if(nextdirection==2 && x==13 && y==26){
        y = 0;
        direction = nextdirection;
    }
    else if(nextdirection==3 && (x+1)<=28 && Pacmap[x+1][y]!=3 && Pacmap[x+1][y]!=4){
        x = x+1;
        direction = nextdirection;
    }
    else if(nextdirection==4 && (y-1)>=0 && Pacmap[x][y-1]!=3 && Pacmap[x][y-1]!=4){
        y = y-1;
        direction = nextdirection;
    }
    else if(nextdirection==4 && x==13 && y==0){
        y = 26;
        direction = nextdirection;
    }
    else if(direction==1 && (x-1)>=0 && Pacmap[x-1][y]!=3 && Pacmap[x-1][y]!=4) {
        x = x-1;
    }
    else if(direction==2 && (y+1)<=26 && Pacmap[x][y+1]!=3 && Pacmap[x][y+1]!=4){
        y = y+1;
    }
    else if(direction==3 && (x+1)<=28 && Pacmap[x+1][y]!=3 && Pacmap[x+1][y]!=4){
        x = x+1;
    }
    else if(direction==4 && (y-1)>=0 && Pacmap[x][y-1]!=3 && Pacmap[x][y-1]!=4){
        y = y-1;
    }

    posx = y*15+30;
    posy = x*15+75;
    return direction;
}

int Pacman::getPosx() {
    return posx;
}

int Pacman::getPosy() {
    return posy;
}

int Pacman::getMoving() {
    return moving;
}
