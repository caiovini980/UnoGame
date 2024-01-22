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
    
    return false;
}

bool InputManager::IsValid(int choice, PlayerBehaviour& player)
{
    // accept from -1 to n - 1 (number of cards on hand - 1)
    return (choice >= -1 && choice <= player.GetCards().size() - 1)
    || choice == _inputForDrawCard;
}

int InputManager::GetMaxInputForMenu() const { return _maxInputForMenu; }

