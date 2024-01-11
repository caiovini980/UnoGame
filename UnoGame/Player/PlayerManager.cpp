#include "PlayerManager.h"

void PlayerManager::Setup()
{
    std::cout << "Setting up Player Manager\n";
}

void PlayerManager::Finish()
{
}

void PlayerManager::CreatePlayers(std::vector<std::string>&& playerNames)
{
    std::vector<std::string> names = std::move(playerNames);
    
    for (int i = 0; i < names.size(); i++)
    {
        PlayerBehaviour newPlayer{std::move(names[i])};
        players.push_back(&newPlayer);
        
        std::cout << "Created player " << *players[i]->GetName() << "\n";
    }
}

std::vector<PlayerBehaviour*>& PlayerManager::GetPlayers()
{
    return players;
}
