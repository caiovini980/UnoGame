#include "PlayerManager.h"

void PlayerManager::Setup()
{
    std::cout << "Setting up Player Manager\n";
}

void PlayerManager::Finish()
{
}

const std::vector<PlayerBehaviour>& PlayerManager::CreatePlayers(std::vector<std::string>&& playerNames)
{
    players.reserve(playerNames.size());
    
    for (int i = 0; i < playerNames.size(); i++)
    {
        PlayerBehaviour newPlayer{std::move(playerNames[i])};
        players.emplace_back(newPlayer);
    }

    return players;
}
