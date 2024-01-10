#pragma once
#include <map>
#include <vector>

#include "../ManagerBase.h"
#include "../PlayerBehaviour.h"

class PlayerManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;
    
    void CreatePlayers(const std::vector<std::string>& playerNames);

private:
    std::vector<PlayerBehaviour> players;
};
