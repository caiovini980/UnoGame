﻿#pragma once
#include <vector>

#include "../ManagerBase.h"
#include "../PlayerBehaviour.h"

class PlayerManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;
    
    void CreatePlayers(std::vector<std::string>&& playerNames);
    std::vector<PlayerBehaviour*>& GetPlayers();

private:
    std::vector<PlayerBehaviour*> players;
};
