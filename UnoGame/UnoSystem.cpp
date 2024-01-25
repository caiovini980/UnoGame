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
    _gameStateManager->ChangeGameStateTo(GameStates::InMenu);
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
    _gameStateManager->ChangeGameStateTo(GameStates::InSetup);
    
    std::vector<std::string> names;
    GetPlayersInfo(names);

    std::vector<PlayerBehaviour> players = _playerManager->CreatePlayers(std::move(names));
    SetupBoard(players);
    
    names.clear();
    
    // GAME LOOP
    _gameStateManager->ChangeGameStateTo(GameStates::InGame);
    _isGameOver = false;

    bool shoutedUNO = false;
    int amountToDraw = 0;
    
    while (!_isGameOver)
    {
        // screen setup
        _visualizationManager->ClearScreen();
        _turnManager->ShowPlayOrder();

        // variables
        PlayerBehaviour& playerOfTheRound = _turnManager->GetNextPlayer();
        CardBehaviour cardOnTopOfTossDeck = _cardManager->GetTopOfTossDeck();
        const std::string QuestionCardIndex = "Select a card: ";
        const bool mustShoutUnoThisRound = _rulesManager->CheckUNOShoutRule(playerOfTheRound.GetCards());

        // check PLUS rule
        if (amountToDraw > 0 && cardOnTopOfTossDeck.GetCardData().type == CardTypes::PlusTwo)
        {
            CheckWhenHaveAPlusCardOnTopOfTossDeck(amountToDraw, playerOfTheRound, cardOnTopOfTossDeck);
        }
        
        std::cout << "\nThe next player to play is: " << *playerOfTheRound.GetName() << "\n";
        _visualizationManager->ShowBoard(cardOnTopOfTossDeck, playerOfTheRound.GetCards(), mustShoutUnoThisRound);
        
        // get input
        const int cardIndex = _visualizationManager->AskForInput<int>(QuestionCardIndex);
        if (!_inputManager->IsValid(cardIndex, playerOfTheRound, mustShoutUnoThisRound))
        {
            std::cout << "Invalid input... Please select a valid one!\n";
            _visualizationManager->WaitForInput();
            continue;
        }

        // check input
        if (cardIndex == _inputManager->GetDrawCardInput())
        {
            PlayerDrawCard(playerOfTheRound);
            continue;
        }
            
        if (cardIndex == _inputManager->GetShoutUNOInput())
        {
            shoutedUNO = true;
            continue;
        }
        
        CardBehaviour cardPlayed = playerOfTheRound.GetSelectedCard(cardIndex);
        if (!FollowBasicUNORules(cardOnTopOfTossDeck, cardPlayed)) continue;
        
        playerOfTheRound.RemoveCardFromHandByIndex(cardIndex);
        _cardManager->AddCardToTopTossDeck(cardPlayed);
        _turnManager->ExecuteTurn(1);
        
        if (cardPlayed.GetCardData().type != CardTypes::Number)
        {
            ExecuteSpecialAction(cardPlayed, amountToDraw);
        }

        // check UNO shout rule
        if (mustShoutUnoThisRound && !shoutedUNO)
        {
            const int amountToDrawUnoRule = _rulesManager->GetAmountOfCardsToDrawWhenViolatesShoutUnoRule();
            const std::string warningText = "\nMust shout 'UNO' when with 2 cards on hand. Bought 2 cards!\n";
            
            _visualizationManager->ShowWarningText(warningText);
            BuyDesiredAmountOfCards(amountToDrawUnoRule, playerOfTheRound);
        }

        // check if played plus card when needed
        if (amountToDraw != 0 && cardPlayed.GetCardData().type != PlusTwo /* or +4, etc */)
        {
            const std::string warningText = "You didn't add to the plus sum.\n";
            _visualizationManager->ShowWarningText(warningText);
            std::cout << "Must buy "<< amountToDraw << " cards!\n";
        
            BuyDesiredAmountOfCards(amountToDraw, playerOfTheRound);
            amountToDraw = 0;
        }

        shoutedUNO = false;
        _visualizationManager->WaitForInput();

        if(_rulesManager->CheckGameOver(playerOfTheRound.GetCards()))
        {
            _isGameOver = true;
            _visualizationManager->ClearScreen();
            _visualizationManager->ShowWinner(*playerOfTheRound.GetName());
            _visualizationManager->WaitForInput();
        }
    }

    std::cout << "Returning to main menu. ";
    _visualizationManager->WaitForInput();
    StartMenu();
}

void UnoSystem::ExecuteSpecialAction(const CardBehaviour& cardPlayed, int& outAmountToDraw)
{
    if (cardPlayed.GetCardData().type == CardTypes::Reverse)
    {
        _turnManager->RevertPlayOrder();
    }
        
    // add +2
    else if (cardPlayed.GetCardData().type == CardTypes::PlusTwo)
    {
        outAmountToDraw += 2;
    }

    // add +4, +10, etc.

    // block
    else if (cardPlayed.GetCardData().type == CardTypes::Block)
    {
        _turnManager->ExecuteTurn(1); 
    }
}

void UnoSystem::PlayerDrawCard(PlayerBehaviour& nextPlayer)
{
    const CardBehaviour newCard = _cardManager->PopNextCardFromDrawDeck();
    nextPlayer.ReceiveCard(newCard);
}

void UnoSystem::CheckWhenHaveAPlusCardOnTopOfTossDeck(int& amountToDraw, PlayerBehaviour& playerOfTheRound,
    const CardBehaviour& cardOnTopOfTossDeck)
{
    if (!_rulesManager->CheckPlusRule(cardOnTopOfTossDeck, playerOfTheRound.GetCards()))
    {
        const std::string buyWarningText = "You don't have a plus card to add to toss.\n";
        _visualizationManager->ShowWarningText(buyWarningText);
        std::cout << "Must buy "<< amountToDraw << " cards!\n";
        
        BuyDesiredAmountOfCards(amountToDraw, playerOfTheRound);
        amountToDraw = 0;
    }
}

void UnoSystem::BuyDesiredAmountOfCards(int amountToDraw, PlayerBehaviour& playerOfTheRound)
{
    for (int i = 0; i < amountToDraw; i++)
    {
        PlayerDrawCard(playerOfTheRound);
    }
}

bool UnoSystem::FollowBasicUNORules(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed)
{
    if (_rulesManager->CheckCardColor(cardPlayed, cardOnTopOfTossDeck))
    {
        return true;
    }
    
    if (_rulesManager->CheckCardNumber(cardPlayed, cardOnTopOfTossDeck) &&
        _rulesManager->CheckCardType(cardPlayed, cardOnTopOfTossDeck))
    {
        return true;  
    }
    
    std::cout << "Invalid play... Colors must match!\n";
    _visualizationManager->WaitForInput();
    return false;
}

void UnoSystem::SetupBoard(std::vector<PlayerBehaviour>& players) const
{
    _visualizationManager->ClearScreen();
    _cardManager->ShuffleCards();
    
    const int initialHandSize = _cardManager->GetInitialHandSize();
    for (int i = 0; i < static_cast<int>(players.size()); i++)
    {
        for (int j = 0; j < initialHandSize; j++)
        {
            const CardBehaviour card = _cardManager->PopNextCardFromDrawDeck();
            players[i].ReceiveCard(card);
        }
    }

    _turnManager->SetInitialPlayOrder(players);
    _turnManager->ShowPlayOrder();
}

void UnoSystem::GetPlayersInfo(std::vector<std::string>& outNames) const
{
    _visualizationManager->ClearScreen();
    
    const std::string QuestionNumberOfPlayers = "How many players are going to play? ";
    const int amountOfPlayers = _visualizationManager->AskForInput<int>(QuestionNumberOfPlayers);

    if (!_inputManager->IsValid(amountOfPlayers, _gameStateManager->GetCurrentState()))
    {
        std::cout << "The amount of players must be between 2 and 10.\n";
        _visualizationManager->WaitForInput();
        GetPlayersInfo(outNames);
        return;
    }

    outNames = {};
    outNames.reserve(amountOfPlayers);

    for (int i = 0; i < amountOfPlayers; i++)
    {
        std::string AskForAName = "Insert a name ";
        std::string name = _visualizationManager->AskForInput<std::string>(AskForAName);

        outNames.emplace_back(name);
    }
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
