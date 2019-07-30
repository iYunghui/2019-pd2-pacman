#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ghost.h>
#include <pacman.h>
#include <moveobject.h>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QPalette>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);
    void InitializeBoard();
    void SetPath(int x1, int y1, int x2, int y2);
    void SetGhostPath(int x1, int y1, int x2, int y2);
    void SetBall(int x1, int y1, int x2, int y2);
    void SetPowerBall(int x, int y);
    void Life();
    void Judge(); //遊戲輸贏判斷
    int **map;

public slots:
    void PacmanMove();
    void Ghost1Move();
    void Ghost2Move();
    void Ghost3Move();
    void Ghost4Move();
    void ChangeState();
    void startSlot();

private:
    Ui::MainWindow *ui;
    //Pacman *pacman;
    //Ghost *ghost1, *ghost2, *ghost3, *ghost4;
    MoveObject *pacman;
    MoveObject *ghost1, *ghost2, *ghost3, *ghost4;
    int pacx, pacy, direction, nextdirection;//1:up, 2:right, 3:down, 4:left
    int ghost1_x, ghost1_y, ghost1_dir, ghost1_nextdir;
    int ghost2_x, ghost2_y, ghost2_dir, ghost2_nextdir;
    int ghost3_x, ghost3_y, ghost3_dir, ghost3_nextdir;
    int ghost4_x, ghost4_y, ghost4_dir, ghost4_nextdir;
    int score, state, ghost1time, ghost2time, ghost3time, ghost4time;
    bool ghost1moving, ghost2moving, ghost3moving, ghost4moving;
    int paclife; //0:die 1:normal 2:can eat ghost
    int ghost1life, ghost2life, ghost3life, ghost4life; //0:die 1:normal 2:pac can eat ghost
    int powertime;
    QTimer *PacTime, *Ghost1Time, *Ghost2Time, *Ghost3Time, *Ghost4Time;
    QTimer *Timer;
    QLabel *Score;
    QPushButton *start;
};

#endif // MAINWINDOW_H
