# pd2-pacman

![](https://i.imgur.com/R8BI6FS.png)

## Power Pellets

- If the ghost collide with the pac-man and pac-man has eaten power pellets
    - Pac-man eat the ghost and get the point
    - ghost die and bring back to life in a few seconds

## Pac-man

- Pac-man may keep going straight forward and player can use four keys to change its direction
- If Pac-man collide with the ghost, game over
    - You don't need to make pac-man life, it only have one life

## Ghost

- There are four ghosts in the corner of the gameboard
- Four ghosts should have four different algorithm to chase pac-man
    - you can take [this](https://en.wikipedia.org/wiki/Pac-Man#Enemy_behavior) as reference
- If the ghost collide with the pac-man, pac-man die and game over


## Polymorphism
- polymorphism technique on class `Pacman` and `Ghost`.
- Both of them implement method `move()`, and be called by pointer of base class.

## Code

- ghost.cpp：Ghost的移動規則
- main.cpp：顯示mainwindow
- mainwindow.cpp：遊戲初始化、設定和輸贏判斷
- moveobject.cpp：Polymorphism
- pacman.cpp：Pac-man的移動規則
