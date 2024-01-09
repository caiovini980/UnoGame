#pragma once
#include "../ManagerBase.h"
#include "../GameStates.h"

class InputManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    bool IsValid(int choice, const GameStates& state);
};
