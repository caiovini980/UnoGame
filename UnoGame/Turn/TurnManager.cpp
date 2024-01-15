#include "TurnManager.h"

void TurnManager::Setup()
{
    std::cout << "Setting up Turn Manager\n";
}

void TurnManager::Finish()
{
}

void TurnManager::SetInitialPlayOrder(const std::vector<PlayerBehaviour>& players)
{
    _playOrder = players;
    
    // set a random order for the players to play
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(_playOrder), std::end(_playOrder), rng);
}

void TurnManager::RevertPlayOrder()
{
    std::reverse(_playOrder.begin(), _playOrder.end());
}

PlayerBehaviour& TurnManager::GetNextPlayer()
{
    return _playOrder[_playIndex + 1];
}

void TurnManager::ShowPlayOrder()
{
    std::cout << "\nPlay order is: ";
    
    for (int i = 0; i < _playOrder.size(); i++)
    {
        std::cout << *_playOrder[i].GetName() << ", ";
    }
}
