#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ghost.h>
#include <pacman.h>
#include <moveobject.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(620,580);
    PacTime = new QTimer(this);
    Ghost1Time = new QTimer(this);
    Ghost2Time = new QTimer(this);
    Ghost3Time = new QTimer(this);
    Ghost4Time = new QTimer(this);
    Timer = new QTimer(this);

    map = new int *[29];
    for(int i=0; i<29; ++i)
        map[i] = new int[27];

    for(int i=0; i<29; ++i)
        for(int j=0; j<27; ++j)
            map[i][j]=4;

    Score = new QLabel("分數: 000", this);
    Score->setGeometry(500,50,80,80);
    QPalette color;
    color.setColor(QPalette::WindowText, Qt::white);
    Score->setPalette(color);

    start = new QPushButton("開始",this);
    start->setGeometry(490,130,90,60);

    InitializeBoard();

    pacman = new Pacman(map);
    ghost1 = new Ghost(map);
    ghost2 = new Ghost(map);
    ghost3 = new Ghost(map);
    ghost4 = new Ghost(map);

    connect(PacTime, SIGNAL(timeout()), this, SLOT(PacmanMove()));
    connect(Ghost1Time, SIGNAL(timeout()), this, SLOT(Ghost1Move()));
    connect(Ghost2Time, SIGNAL(timeout()), this, SLOT(Ghost2Move()));
    connect(Ghost3Time, SIGNAL(timeout()), this, SLOT(Ghost3Move()));
    connect(Ghost4Time, SIGNAL(timeout()), this, SLOT(Ghost4Move()));
    connect(Timer, SIGNAL(timeout()), this, SLOT(ChangeState()));
    connect(start, SIGNAL(clicked()), this, SLOT(startSlot()));
}

MainWindow::~MainWindow() {
    for(int i=0; i<29; ++i)
        for(int j=0; j<27; ++j)
            delete map[i];
    delete []map;
    delete PacTime;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.drawPixmap(QRect(0,0,620,580),QPixmap(":/images/background.png"));
    painter.drawPixmap(QRect(10,50,450,480),QPixmap(":/images/map.png"));

    for(int i=0; i<29; ++i)
        for(int j=0; j<27; ++j) {
            if(map[i][j]==1)
                painter.drawPixmap(QRect(j*15+30,i*15+75,12,12),QPixmap(":/images/pellet.png"));
            else if(map[i][j]==2)
                painter.drawPixmap(QRect(j*15+30-10,i*15+75-10,30,30),QPixmap(":/images/pellet.png"));
        }

    switch(state) {
    case 0:
        if(direction == 1)
            painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacup1.png"));
        else if(direction == 2)
            painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacright1.png"));
        else if(direction == 3)
            painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacdown1.png"));
        else if(direction == 4)
                painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacleft1.png"));

        if(ghost1_dir==1 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_up1.png"));
        else if(ghost1_dir==2 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_right1.png"));
        else if(ghost1_dir==3 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_down1.png"));
        else if(ghost1_dir==4 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_left1.png"));
        else if(ghost1life==2 && powertime<=20)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghostsblue1.png"));
        else if(ghost1life==2)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghostwhite1.png"));

        if(ghost2_dir == 1 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_up1.png"));
        else if(ghost2_dir == 2 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_right1.png"));
        else if(ghost2_dir == 3 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_down1.png"));
        else if(ghost2_dir == 4 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_left1.png"));
        else if(ghost2life==2 && powertime<=20)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghostsblue1.png"));
        else if(ghost2life==2)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghostwhite1.png"));

        if(ghost3_dir == 1 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_up1.png"));
        else if(ghost3_dir == 2 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_right1.png"));
        else if(ghost3_dir == 3 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_down1.png"));
        else if(ghost3_dir == 4 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_left1.png"));
        else if(ghost3life==2 && powertime<=20)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghostsblue1.png"));
        else if(ghost3life==2)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghostwhite1.png"));

        if(ghost4_dir == 1 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_up1.png"));
        else if(ghost4_dir == 2 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_right1.png"));
        else if(ghost4_dir == 3 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_down1.png"));
        else if(ghost4_dir == 4 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_left1.png"));
        else if(ghost4life==2 && powertime<=20)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghostsblue1.png"));
        else if(ghost4life==2)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghostwhite1.png"));
        break;
    case 1:
        if(direction == 1)
            painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacup2.png"));
        else if(direction == 2)
            painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacright2.png"));
        else if(direction == 3)
            painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacdown2.png"));
        else if(direction == 4)
            painter.drawPixmap(QRect(pacx-2,pacy-5,20,20),QPixmap(":/images/pacleft2.png"));

        if(ghost1_dir == 1 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_up2.png"));
        else if(ghost1_dir == 2 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_right2.png"));
        else if(ghost1_dir == 3 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_down2.png"));
        else if(ghost1_dir == 4 && ghost1life==1)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghost1_left2.png"));
        else if(ghost1life==2)
            painter.drawPixmap(QRect(ghost1_x-3,ghost1_y-5,23,23),QPixmap(":/images/ghostsblue2.png"));

        if(ghost2_dir == 1 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_up2.png"));
        else if(ghost2_dir == 2 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_right2.png"));
        else if(ghost2_dir == 3 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_down2.png"));
        else if(ghost2_dir == 4 && ghost2life==1)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghost2_left2.png"));
        else if(ghost2life==2)
            painter.drawPixmap(QRect(ghost2_x-3,ghost2_y-5,23,23),QPixmap(":/images/ghostsblue2.png"));

        if(ghost3_dir == 1 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_up2.png"));
        else if(ghost3_dir == 2 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_right2.png"));
        else if(ghost3_dir == 3 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_down2.png"));
        else if(ghost3_dir == 4 && ghost3life==1)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghost3_left2.png"));
        else if(ghost3life==2)
            painter.drawPixmap(QRect(ghost3_x-3,ghost3_y-5,23,23),QPixmap(":/images/ghostsblue2.png"));

        if(ghost4_dir == 1 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_up2.png"));
        else if(ghost4_dir == 2 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_right2.png"));
        else if(ghost4_dir == 3 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_down2.png"));
        else if(ghost4_dir == 4 && ghost4life==1)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghost4_left2.png"));
        else if(ghost4life==2)
            painter.drawPixmap(QRect(ghost4_x-3,ghost4_y-5,23,23),QPixmap(":/images/ghostsblue2.png"));
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_E)
        nextdirection = 1;
    else if(event->key()==Qt::Key_F)
        nextdirection = 2;
    else if(event->key()==Qt::Key_D)
        nextdirection = 3;
    else if(event->key()==Qt::Key_S)
        nextdirection = 4;
}

void MainWindow::PacmanMove() {
    direction = pacman->move(pacx, pacy, direction, nextdirection);
    pacx = pacman->getPosx();
    pacy = pacman->getPosy();
    int x = (pacy-75)/15;
    int y = (pacx-30)/15;

    if(paclife == 2)
        powertime++;
    if(powertime == 30) {
        if(paclife==2)     paclife = 1;
        if(ghost1life==2)  ghost1life = 1;
        if(ghost2life==2)  ghost2life = 1;
        if(ghost3life==2)  ghost3life = 1;
        if(ghost4life==2)  ghost4life = 1;
    }

    if(map[x][y]==1) {
        map[x][y] = 0;
        score++;
    }
    else if(map[x][y]==2) {
        map[x][y] = 0;
        paclife = 2;
        if(ghost1life!=0)  ghost1life = 2;
        if(ghost2life!=0)  ghost2life = 2;
        if(ghost3life!=0)  ghost3life = 2;
        if(ghost4life!=0)  ghost4life = 2;
        score++;
        powertime = 0;
    }

    Life();
    Judge();
}

void MainWindow::Ghost1Move() {
    if(ghost1life==0 && ghost1time==4) {
        ghost1_x = 225;
        ghost1_y = 270;
        ghost1time = -30;
    }
    if(ghost1time!=4) {
        if(ghost1time>=0)
            ghost1_y -= 15;
        ghost1time++;
        if(ghost1time==3 && ghost1life==0)
            ghost1life = 1;
    }
    if(ghost1time==4 && ghost1life!=0) {
        if(!ghost1moving) {
            ghost1_dir = (rand()%4)+1;
        }
        else {
            if(ghost1_x<pacx) {
                ghost1_nextdir=2;
            }
            else if(ghost1_y>pacy) {
                ghost1_nextdir = 1;
            }
            else if(ghost1_y<pacy) {
                ghost1_nextdir = 3;
            }
            else if(ghost1_x>pacx) {
                ghost1_nextdir=4;
            }
        }

        ghost1_dir = ghost1->move(ghost1_x, ghost1_y, ghost1_dir, ghost1_nextdir);
        ghost1moving = ghost1->getMoving();
        ghost1_x = ghost1->getPosx();
        ghost1_y = ghost1->getPosy();
        Life();
    }
}

void MainWindow::Ghost2Move() {
    if(ghost2life==0 && ghost2time==15) {
        ghost2_x = 195;
        ghost2_y = 270;
        ghost2time = -20;
    }
    if(ghost2time<15) {
        if(ghost2time>=9 && ghost2time<=10)
            ghost2_x += 15;
        if(ghost2time>=11 && ghost2time<=13)
            ghost2_y -= 15;
        ghost2time++;
        if(ghost2time==15 && ghost2life==0)
            ghost2life = 1;
    }
    if(ghost2time==15 && ghost2life!=0) {
        if(!ghost2moving) {
            ghost2_dir = (rand()%4)+1;
        }
        else {
            if(ghost2_y>pacy) {
                ghost2_nextdir = 1;
            }
            else if(ghost2_y<pacy) {
                ghost2_nextdir = 3;
            }
            else if(ghost2_x<pacx) {
                ghost2_nextdir=2;
            }
            else if(ghost2_x>pacx) {
                ghost2_nextdir=4;
            }
        }

        ghost2_dir = ghost2->move(ghost2_x, ghost2_y, ghost2_dir, ghost2_nextdir);
        ghost2moving = ghost2->getMoving();
        ghost2_x = ghost2->getPosx();
        ghost2_y = ghost2->getPosy();
        Life();
    }
}

void MainWindow::Ghost3Move() {
    if(ghost3life==0 && ghost3time==30) {
        ghost3_x = 255;
        ghost3_y = 270;
        ghost3time = -10;
    }
    if(ghost3time<30) {
        if(ghost3time>=24 && ghost3time<=25)
            ghost3_x -= 15;
        if(ghost3time>=26 && ghost3time<=28)
            ghost3_y -= 15;
        ghost3time++;
        if(ghost3time==30 && ghost3life==0)
            ghost3life = 1;
    }
    if(ghost3time==30 && ghost3life!=0) {
        if(!ghost3moving) {
            ghost3_dir = (rand()%4)+1;
        }
        else {
            if(ghost3_x>pacx) {
                ghost3_nextdir=4;
            }
            else if(ghost3_y>pacy) {
                ghost3_nextdir = 1;
            }
            else if(ghost3_x<pacx) {
                ghost3_nextdir=2;
            }
            else if(ghost3_y<pacy) {
                ghost3_nextdir = 3;
            }
        }

        ghost3_dir = ghost3->move(ghost3_x, ghost3_y, ghost3_dir, ghost3_nextdir);
        ghost3moving = ghost3->getMoving();
        ghost3_x = ghost3->getPosx();
        ghost3_y = ghost3->getPosy();
        Life();
    }
}

void MainWindow::Ghost4Move() {
    if(ghost4life == 0)
        ghost4time++;
    if(ghost4time == 15) {
        ghost4_x = 225;
        ghost4_y = 225;
        ghost4life = 1;
        ghost4time = -30;
    }
    if(ghost4life!=0) {
        if(!ghost4moving) {
            ghost4_dir = (rand()%4)+1;
        }
        else {
            if(ghost4_y<pacy) {
                ghost4_nextdir = 3;
            }
            else if(ghost4_y>pacy) {
                ghost4_nextdir = 1;
            }
            else if(ghost4_x>pacx) {
                ghost4_nextdir=4;
            }
            else if(ghost4_x<pacx) {
                ghost4_nextdir=2;
            }
        }

       ghost4_dir = ghost4->move(ghost4_x, ghost4_y, ghost4_dir, ghost4_nextdir);
       ghost4moving = ghost4->getMoving();
       ghost4_x = ghost4->getPosx();
       ghost4_y = ghost4->getPosy();
       Life();
    }
}

void MainWindow::Life() {
    if(paclife==1 && ghost1life==1 && pacx==ghost1_x && pacy==ghost1_y)
        paclife = 0;
    else if(paclife==1 && ghost2life==1 && pacx==ghost2_x && pacy==ghost2_y)
        paclife = 0;
    else if(paclife==1 && ghost3life==1 && pacx==ghost3_x && pacy==ghost3_y)
        paclife = 0;
    else if(paclife==1 && ghost4life==1 && pacx==ghost4_x && pacy==ghost4_y)
        paclife = 0;
    else if(paclife==2 && ghost1life==2 && pacx==ghost1_x && pacy==ghost1_y) {
        ghost1life = 0;
        score+=50;
    }
    else if(paclife==2 && ghost2life==2 && pacx==ghost2_x && pacy==ghost2_y) {
        ghost2life = 0;
        score+=50;
    }
    else if(paclife==2 && ghost3life==2 && pacx==ghost3_x && pacy==ghost3_y) {
        ghost3life = 0;
        score+=50;
    }
    else if(paclife==2 && ghost4life==2 && pacx==ghost4_x && pacy==ghost4_y) {
        ghost4life = 0;
        score+=50;
    }

    QString s = QString("分數: %1").arg(score,3,10,QChar('0'));
    Score->setText(s);
}

void MainWindow::ChangeState() {
    state = (state==1)?0:1;
    this->repaint();
}

void MainWindow::startSlot() {
    start->setText("重新開始");

    InitializeBoard();
    PacTime->start(350);
    Ghost1Time->start(400);
    Ghost2Time->start(400);
    Ghost3Time->start(400);
    Ghost4Time->start(400);
    Timer->start(200);
    this->repaint();
}

void MainWindow::InitializeBoard() {
    score = state = 0;

    pacx = 225;        pacy = 405;
    ghost1_x = 225;    ghost1_y = 270;
    ghost2_x = 195;    ghost2_y = 270;
    ghost3_x = 255;    ghost3_y = 270;
    ghost4_x = 225;    ghost4_y = 225;

    direction = nextdirection = 4;
    ghost1_dir = ghost1_nextdir = 1;
    ghost2_dir = ghost2_nextdir = 1;
    ghost3_dir = ghost3_nextdir = 1;
    ghost4_dir = ghost4_nextdir = 4;

    paclife = ghost1life = ghost2life = ghost3life = ghost4life = 1;
    ghost1time = ghost2time = ghost3time = powertime = 0;
    ghost4time = -30;

    SetPath(210,180,210,225);
    SetPath(255,180,255,225);
    SetPath(150,225,300,225);
    SetPath( 30,270,105,270);
    SetPath(345,270,420,270);
    SetPath(150,315,300,315);

    SetGhostPath(195,270,255,270);
    SetGhostPath(225,240,225,270);

    SetBall( 30, 75, 30,180);
    SetBall(105, 75,105,450);
    SetBall(210, 75,210,135);
    SetBall(255, 75,255,135);
    SetBall(345, 75,345,450);
    SetBall(420, 75,420,180);
    SetBall( 30, 75,210, 75);
    SetBall(255, 75,420, 75);
    SetBall( 30,135,420,135);
    SetBall(150,135,150,180);
    SetBall(150,135,150,180);
    SetBall(300,135,300,180);
    SetBall( 30,180,105,180);
    SetBall(150,180,210,180);
    SetBall(255,180,300,180);
    SetBall(360,180,420,180);
    SetBall(150,225,150,360);
    SetBall(300,225,300,360);
    SetBall(105,270,150,270);
    SetBall(300,270,345,270);
    SetBall( 30,360,210,360);
    SetBall(255,360,420,360);
    SetBall( 30,360, 30,405);
    SetBall(210,360,210,405);
    SetBall(255,360,255,405);
    SetBall(420,360,420,405);
    SetBall( 30,405, 60,405);
    SetBall(105,405,345,405);
    SetBall(390,405,420,405);
    SetBall( 60,405, 60,450);
    SetBall(150,405,150,450);
    SetBall(300,405,300,450);
    SetBall(390,405,390,450);
    SetBall( 30,450,105,450);
    SetBall(150,450,210,450);
    SetBall(255,450,300,450);
    SetBall(345,450,420,450);
    SetBall( 30,450, 30,495);
    SetBall(210,450,210,495);
    SetBall(255,450,255,495);
    SetBall(420,450,420,495);
    SetBall( 30,495,420,495);

    SetPowerBall( 30,135);
    SetPowerBall(420,135);
    SetPowerBall( 30,405);
    SetPowerBall(420,405);
}

void MainWindow::SetPath(int x1, int y1, int x2, int y2) {
    for(int i=x1; i<=x2; i+=15)
        for(int j=y1; j<=y2; j+=15)
            map[(j-75)/15][(i-30)/15] = 0;
}

void MainWindow::SetGhostPath(int x1, int y1, int x2, int y2) {
    for(int i=x1; i<=x2; i+=15)
        for(int j=y1; j<=y2; j+=15)
            map[(j-75)/15][(i-30)/15] = 3;
}

void MainWindow::SetBall(int x1, int y1, int x2, int y2) {
    for(int i=x1; i<=x2; i+=15)
        for(int j=y1; j<=y2; j+=15)
            map[(j-75)/15][(i-30)/15] = 1;
}

void MainWindow::SetPowerBall(int x, int y) {
    map[(y-75)/15][(x-30)/15] = 2;
}

void MainWindow::Judge() {
    if(paclife == 0) {
        PacTime->stop();
        Ghost1Time->stop();
        Ghost2Time->stop();
        Ghost3Time->stop();
        Ghost4Time->stop();
        Timer->stop();
        QMessageBox::information(this, "結果", "Game Over!", QMessageBox::Yes);
    }
    else {
        int flag = 0;
        for(int i=0; i<29; ++i)
            for(int j=0; j<27; ++j)
                if(map[i][j]==1 || map[i][j]==2)
                    flag = 1;
        if(!flag) {
            PacTime->stop();
            Ghost1Time->stop();
            Ghost2Time->stop();
            Ghost3Time->stop();
            Ghost4Time->stop();
            Timer->stop();
            QMessageBox::information(this, "結果", "Game Win!", QMessageBox::Yes);
        }
    }
}
