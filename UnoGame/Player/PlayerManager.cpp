#include "PlayerManager.h"

void PlayerManager::Setup()
{
    std::cout << "Setting up Player Manager\n";
}

void PlayerManager::Finish()
{
}

const std::vector<PlayerBehaviour>& PlayerManager::CreatePlayers(std::vector<std::string>& playerNames)
{
    for (int i = 0; i < playerNames.size(); i++)
    {
        PlayerBehaviour newPlayer{playerNames[i]};
        players.push_back(newPlayer);
    }

    return players;
}
