#pragma once
#include "../ManagerBase.h"

class TurnManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;
};
