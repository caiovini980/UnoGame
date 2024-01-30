#pragma once
#include "../ManagerBase.h"
#include "../GameStates.h"

class GameStateManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    void ChangeGameStateTo(const GameStates& target);

    GameStates GetCurrentState() const;

private:
    GameStates _currentState = InMenu;
};
