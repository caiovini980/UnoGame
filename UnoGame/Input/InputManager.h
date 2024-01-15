#pragma once
#include "../ManagerBase.h"
#include "../GameStates.h"

class InputManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    bool IsValid(int choice, const GameStates& state);

    int GetMaxInputForMenu() const;

private:
    int _maxInputForMenu = 3;
    int _maxInputForAmountOfPlayers = 10;
};
