#include "GameStateManager.h"

void GameStateManager::Setup()
{
    std::cout << "Setting up Game State Manager\n";
}

void GameStateManager::Finish()
{
}

void GameStateManager::ChangeGameStateTo(const GameStates& target)
{
    _currentState = target;
}

GameStates GameStateManager::GetCurrentState() const
{
    return _currentState;
}
