#include "InputManager.h"

void InputManager::Setup()
{
    std::cout << "Setting up Input Manager\n";
}

void InputManager::Finish()
{
}

bool InputManager::IsValid(int choice, const GameStates& state)
{
    if (!std::isdigit(choice))
    {
        return false;
    }

    // check input for menu
    if (state == InMenu)
    {
            
    }
    // check input for gameplay
    if (state == InGame)
    {
            
    }
    
    return true;
}

