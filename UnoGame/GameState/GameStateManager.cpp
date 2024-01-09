#include "GameStateManager.h"

void GameStateManager::Setup()
{
    std::cout << "Setting up Game State Manager\n";
}

void GameStateManager::Finish()
{
}

GameStates GameStateManager::GetCurrentState() const
{
    return _currentState;
}
