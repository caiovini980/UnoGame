#pragma once
#include "../ManagerBase.h"

class PlayerManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;
};
