#pragma once
#include "../ManagerBase.h"
#include "../GameStates.h"

class GameStateManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    GameStates GetCurrentState() const;

private:
    GameStates _currentState = InMenu;
};
