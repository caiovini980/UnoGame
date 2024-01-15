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
    // check input for menu
    if (state == InMenu)
    {
        // accept from 1 to 3
        if (choice > 0 && choice <= _maxInputForMenu)
        {
            return true;
        }
    }

    if (state == InSetup)
    {
        // accept from 2 to 10
        if (choice > 1 && choice <= _maxInputForAmountOfPlayers)
        {
            return true;
        }
    }
    
    // check input for gameplay
    if (state == InGame)
    {
        // accept from -1 to n - 1 (number of cards on hand - 1)
        return true;
    }
    
    return false;
}

int InputManager::GetMaxInputForMenu() const { return _maxInputForMenu; }

