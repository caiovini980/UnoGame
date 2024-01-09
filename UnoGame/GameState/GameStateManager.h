#pragma once
#include "../ManagerBase.h"

class GameStateManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;
};
