#ifndef GAME_H
#define GAME_H

class Game
{

public:
    Game();
    bool running=false;
    void save();
    void load();
    void sleep();
    void awake();
    void fresh();
};

extern Game* GAME;

#endif // GAME_H
