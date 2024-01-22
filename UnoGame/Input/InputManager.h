#pragma once
#include "../ManagerBase.h"
#include "../GameStates.h"
#include "../PlayerBehaviour.h"

class InputManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    bool IsValid(int choice, const GameStates& state);
    bool IsValid(int choice, PlayerBehaviour& player);

    int GetMaxInputForMenu() const;

private:
    int _maxInputForMenu = 3;
    int _inputForDrawCard = -1;
    int _maxInputForAmountOfPlayers = 10;
};
