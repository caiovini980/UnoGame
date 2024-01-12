#pragma once
#include <vector>

#include "../ManagerBase.h"
#include "../PlayerBehaviour.h"

class PlayerManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;
    
    const std::vector<PlayerBehaviour>& CreatePlayers(std::vector<std::string>& playerNames);

private:
    std::vector<PlayerBehaviour> players;
};
