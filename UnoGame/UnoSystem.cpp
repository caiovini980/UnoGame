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

    _visualizationManager->ClearScreen();
    if(_inputManager->IsValid(choice, _gameStateManager->GetCurrentState()))
    {
        constexpr int startGameOption = 1;
        constexpr int showRulesOption = 2;
        
        if (choice == startGameOption)
        {
            StartGame();
        }
        else if (choice == showRulesOption)
        {
            ShowRules();
        }
        else
        {
            CloseGame();
        }
    }
    else
    {
        std::cout << "Please enter a valid input.\n";
        _visualizationManager->WaitForInput();
        StartMenu();
    }
}

void UnoSystem::StartGame()
{
    std::cout << "Starting game...\n\n";

    // CREATE PLAYERS
    int amountOfPlayers;
    
    std::cout << "How many players are going to play? ";
    std::cin >> amountOfPlayers;

    // ORGANIZE BOARD

    // START GAME
    _gameStateManager->ChangeGameStateTo(GameStates::InGame);
}

void UnoSystem::ShowRules()
{
    std::cout << "--------------- R U L E S \n\n"
                 "- At the start of the game, 7 cards must be sorted for each player’s hands from the deck.\n"
                 "- The match must be played in rounds, going from a player to the other, in the sorted way.\n"
                 "- At each turn, a player must choose a card to be played on the table.\n"
                 "- It is only possible to play a card if the card matches the last card on the table.\n"
                 "- If the player does not have any cards to play, it must buy a card from the deck.\n"
                 "- Also, if the player is required to buy cards from +2 cards, "
                 "it must do it in their round and then skip it.\n"
                 "- When there are only 2 cards on the player’s hand, "
                 "there must be an option to the player yell 'UNO!' before using a card.\n"
                 "- When there is only 1 card on the player’s hand, "
                 "the played had yelled 'UNO!', and the played has used this card matching the rules, "
                 "then the player is the winner and the match ends.\n"
                 "- If the player has not yelled 'UNO!', it must buy 2 new cards from the deck and skip the turn.\n"
                 "- If the deck ends, the cards tossed into the table must be shuffled and re-added to the deck.\n\n"
                 "--------------- R U L E S\n\n";

    _visualizationManager->WaitForInput();
    StartMenu();
}

void UnoSystem::CloseGame()
{
    std::cout << "Closing game...\n";
    exit(0);
}
