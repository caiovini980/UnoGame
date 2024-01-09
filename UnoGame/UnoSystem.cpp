#include "UnoSystem.h"


UnoSystem::UnoSystem()
{
    SetupManagers();
    StartMenu();
}

void UnoSystem::SetupManagers() const
{
    _actionManager->Setup();
    _cardManager->Setup();
    _gameStateManager->Setup();
    _inputManager->Setup();
    _playerManager->Setup();
    _rulesManager->Setup();
    _turnManager->Setup();
    _visualizationManager->Setup();
}

void UnoSystem::StartMenu()
{
    _visualizationManager->ClearScreen();
    std::cout << "Welcome to the UNO game!\nPlease select an option:\n\n";
    std::cout << "1 - Start Game\n";
    std::cout << "2 - Rules\n";
    std::cout << "3 - Close Game\n\n";
    
    int choice;
    std::cin >> choice;
    
    if(_inputManager->IsValid(choice, _gameStateManager->GetCurrentState()))
    {
        
    }
}
