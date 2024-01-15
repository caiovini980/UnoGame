﻿#pragma once
#include <vector>
#include <random>

#include "../ManagerBase.h"
#include "../PlayerBehaviour.h"


class TurnManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;
    void SetInitialPlayOrder(const std::vector<PlayerBehaviour>& players);
    void RevertPlayOrder();
    void ShowPlayOrder(); // TEST
    
    PlayerBehaviour& GetNextPlayer();
    
private:
    std::vector<PlayerBehaviour> _playOrder;

    void JumpNextPlayer();

    int _playIndex = 0;
};
