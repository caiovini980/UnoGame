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

bool InputManager::IsValid(int choice, PlayerBehaviour& player, bool canShoutUno) const
{
    // accept from -1 to n - 1 (number of cards on hand - 1)
    const int amountOfCardsOnPlayerHand = static_cast<int>(player.GetCards().size());

    if (canShoutUno)
    {
        return (choice >= 0 && choice <= amountOfCardsOnPlayerHand - 1)
                || choice == _inputForDrawCard
                || choice == _inputForUnoShout;
    }

    return (choice >= 0 && choice <= amountOfCardsOnPlayerHand - 1)
    || choice == _inputForDrawCard;
}

int InputManager::GetMaxInputForMenu() const { return _maxInputForMenu; }

int InputManager::GetDrawCardInput() const{ return _inputForDrawCard; }

int InputManager::GetShoutUNOInput() const { return _inputForUnoShout; }

