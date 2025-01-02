//////////////////
/// \author JackeyLea
/// \date 2025.01.02
/// \note 游戏流程控制
//////////////////

#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include <QThread>

class GameFlow : public QThread
{
public:
    GameFlow();

protected:
    void run();
};

#endif // GAMEFLOW_H
