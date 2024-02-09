#include "UnoSystem.h"

UnoSystem::UnoSystem()
{
    SetupManagers();
    StartMenu();
}

void UnoSystem::SetupManagers() const
{
    _cardManager->Setup();
    _gameStateManager->Setup();
    _inputManager->Setup();
    _playerManager->Setup();
    _rulesManager->Setup();
    _turnManager->Setup();
    _visualizationManager->Setup();
}

void UnoSystem::HandleValidMenuInput(int choice)
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

void UnoSystem::StartMenu()
{
    _gameStateManager->ChangeGameStateTo(GameStates::InMenu);
    _visualizationManager->ClearScreen();
    
    ShowMenu();
    
    int choice;
    std::cin >> choice;

    _visualizationManager->ClearScreen();
    if(IsMenuInputValid(choice))
    {
        HandleValidMenuInput(choice);
    }
    else
    {
        HandleInvalidMenuInput();
        StartMenu();
    }
}

void UnoSystem::InitializePlayersAndSetupBoard() const
{
    std::vector<std::string> names;
    GetPlayersInfo(names);

    std::vector<PlayerBehaviour> players = _playerManager->CreatePlayers(std::move(names));
    SetupBoard(players);
    
    names.clear();
}

void UnoSystem::StartGame()
{
    _gameStateManager->ChangeGameStateTo(GameStates::InSetup);
    
    InitializePlayersAndSetupBoard();
    ExecuteGameLoop();

    std::cout << "Returning to main menu. ";
    _visualizationManager->WaitForInput();
    StartMenu();
}

int UnoSystem::GetPlayerInput() const
{
    const std::string QuestionCardIndex = "Select a card: ";
    return _visualizationManager->AskForInput<int>(QuestionCardIndex);
}

void UnoSystem::ExecuteGameLoop()
{
    _gameStateManager->ChangeGameStateTo(GameStates::InGame);
    _isGameOver = false;

    bool shoutedUNO = false;
    int amountToDraw = 0;
    
    while (!_isGameOver)
    {
        PlayerBehaviour& playerOfTheRound = _turnManager->GetNextPlayer();
        CardBehaviour cardOnTopOfTossDeck = _cardManager->GetTopOfTossDeck();
        
        ClearScreenAndShowPlayOrder();
        CheckPreTurnRules(amountToDraw, playerOfTheRound, cardOnTopOfTossDeck);
        ShowPlayerOfTheRoundAndBoard(playerOfTheRound, cardOnTopOfTossDeck);
        
        const int cardIndex = GetPlayerInput();
        CardBehaviour cardPlayed = playerOfTheRound.GetSelectedCard(cardIndex);
        
        if (IsInputInvalid(playerOfTheRound, cardIndex)) continue;
        if (IsInputSpecial(shoutedUNO, playerOfTheRound, cardIndex)) continue;
        if (!FollowBasicUNORules(cardOnTopOfTossDeck, cardPlayed)) continue;
        
        PlayCardAndChangeTurn(playerOfTheRound, cardIndex, cardPlayed);
        CheckPostTurnRules(shoutedUNO, amountToDraw, playerOfTheRound, cardPlayed);

        shoutedUNO = false;
        _visualizationManager->WaitForInput();
        
        CheckGameOver(playerOfTheRound);
    }
}

void UnoSystem::CheckPlusCards(int& amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck)
{
    const CardTypes cardOnTopOfTossDeckType = cardOnTopOfTossDeck.GetCardData().type;
    if (cardOnTopOfTossDeckType == CardTypes::PlusTwo)
    {
        CheckWhenHaveAPlusCardOnTopOfTossDeck(amountToDraw, playerOfTheRound, cardOnTopOfTossDeck);
    }

    else if (cardOnTopOfTossDeckType == CardTypes::PlusTwoDiscard)
    {
        ExecutePlusTwoDiscard(amountToDraw, playerOfTheRound, cardOnTopOfTossDeck);
    }
}

void UnoSystem::CheckPreTurnRules(int& amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck)
{
    if (amountToDraw <= 0) { return; }
    
    CheckPlusCards(amountToDraw, playerOfTheRound, cardOnTopOfTossDeck);

    // Add more card rules here
}

void UnoSystem::ShowPlayerOfTheRoundAndBoard(PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck) const
{
    const bool mustShoutUnoThisRound = _rulesManager->CheckUNOShoutRule(playerOfTheRound.GetCards());
    std::cout << "\nPlayer of the round is: " << *playerOfTheRound.GetName() << "\n";
    _visualizationManager->ShowBoard(cardOnTopOfTossDeck, playerOfTheRound.GetCards(), mustShoutUnoThisRound);
}

void UnoSystem::HandleShoutUNORuleViolation(PlayerBehaviour& playerOfTheRound)
{
    const int amountToDrawUnoRule = _rulesManager->GetAmountOfCardsToDrawWhenViolatesShoutUnoRule();
    const std::string warningText = "\nMust shout 'UNO' when with 2 cards on hand. Bought 2 cards!\n";
            
    _visualizationManager->ShowWarningText(warningText);
    BuyDesiredAmountOfCards(amountToDrawUnoRule, playerOfTheRound);
}

void UnoSystem::CheckShoutUNORule(bool shoutedUNO, PlayerBehaviour& playerOfTheRound, const bool mustShoutUnoThisRound)
{
    if (mustShoutUnoThisRound && !shoutedUNO)
    {
        HandleShoutUNORuleViolation(playerOfTheRound);
    }
}

void UnoSystem::HandlePlusCardAdditionViolation(int& amountToDraw, PlayerBehaviour& playerOfTheRound)
{
    const std::string warningText = "You didn't add to the plus sum.\n";
    _visualizationManager->ShowWarningText(warningText);
    std::cout << "Must buy "<< amountToDraw << " cards!\n";
        
    BuyDesiredAmountOfCards(amountToDraw, playerOfTheRound);
}

void UnoSystem::CheckPlusCardWhenNeeded(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardPlayed)
{
    const CardTypes cardPlayedType = cardPlayed.GetCardData().type;
    if (amountToDraw != 0 && (cardPlayedType != PlusTwo && cardPlayedType != PlusTwoDiscard)) // TODO add boolean on CardBehaviour that handle the 'PlusTwo' identification
    {
        HandlePlusCardAdditionViolation(amountToDraw, playerOfTheRound);
        amountToDraw = 0;
    }
}

void UnoSystem::ExecuteGameOver(PlayerBehaviour& playerOfTheRound)
{
    _visualizationManager->ClearScreen();
    _visualizationManager->ShowWinner(*playerOfTheRound.GetName());
    _visualizationManager->WaitForInput();
}

void UnoSystem::CheckGameOver(PlayerBehaviour& playerOfTheRound)
{
    if(_rulesManager->CheckGameOver(playerOfTheRound.GetCards()))
    {
        _isGameOver = true;
        ExecuteGameOver(playerOfTheRound);
    }
}

void UnoSystem::PlayCardAndChangeTurn(PlayerBehaviour& playerOfTheRound, const int cardIndex, CardBehaviour cardPlayed) const
{
    playerOfTheRound.RemoveCardFromHandByIndex(cardIndex);
    _cardManager->AddCardToTopTossDeck(cardPlayed);
    _turnManager->ExecuteTurn(1);
}

void UnoSystem::CheckSpecialCard(int amountToDraw, CardBehaviour cardPlayed) const
{
    if (cardPlayed.GetCardData().type != CardTypes::Number)
    {
        ExecuteSpecialAction(cardPlayed, amountToDraw);
    }
}

void UnoSystem::CheckPostTurnRules(bool shoutedUNO, int amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardPlayed)
{
    const bool mustShoutUnoThisRound = _rulesManager->CheckUNOShoutRule(playerOfTheRound.GetCards());
    CheckSpecialCard(amountToDraw, cardPlayed);
    CheckShoutUNORule(shoutedUNO, playerOfTheRound, mustShoutUnoThisRound);
    CheckPlusCardWhenNeeded(amountToDraw, playerOfTheRound, cardPlayed);
}

void UnoSystem::HandleInvalidMenuInput() const
{
    std::cout << "Please enter a valid input.\n";
    _visualizationManager->WaitForInput();
}

void UnoSystem::ShowMenu()
{
    std::cout << "Welcome to the UNO game!\nPlease select an option:\n\n";
    std::cout << "1 - Start Game\n";
    std::cout << "2 - Rules\n";
    std::cout << "3 - Close Game\n\n";
}

bool UnoSystem::IsInputInvalid(PlayerBehaviour& playerOfTheRound, const int cardIndex) const
{
    const bool mustShoutUnoThisRound = _rulesManager->CheckUNOShoutRule(playerOfTheRound.GetCards());
    if (!_inputManager->IsValid(cardIndex, playerOfTheRound, mustShoutUnoThisRound))
    {
        std::cout << "Invalid input... Please select a valid one!\n";
        _visualizationManager->WaitForInput();
        return true;
    }
    return false;
}

bool UnoSystem::CheckDrawInput(PlayerBehaviour& playerOfTheRound, int cardIndex)
{
    if (cardIndex == _inputManager->GetDrawCardInput())
    {
        PlayerDrawCard(playerOfTheRound);
        return true;
    }
    
    return false;
}

bool UnoSystem::IsInputSpecial(bool& shoutedUNO, PlayerBehaviour& playerOfTheRound, const int cardIndex)
{
    if (CheckDrawInput(playerOfTheRound, cardIndex))
    {
        return true;
    }

    if (CheckUNOShoutInput(cardIndex))
    {
        shoutedUNO = true;
        return true;
    }
    
    return false;
}

void UnoSystem::ClearScreenAndShowPlayOrder() const
{
    _visualizationManager->ClearScreen();
    _turnManager->ShowPlayOrder();
}

void UnoSystem::ExecutePlusTwoDiscard(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardOnTopOfTossDeck) const
{
    if (!_rulesManager->CheckPlusDiscardRule(cardOnTopOfTossDeck))
    {
        return;
    }

    if (_cardManager->GetSizeOfTossDeck() < amountToDraw)
    {
        PlayerDrawCardFromTossDeck(playerOfTheRound);
        return;
    }

    for (int i = 0; i < amountToDraw; i++)
    {
        PlayerDrawCardFromTossDeck(playerOfTheRound);
    }

    amountToDraw = 0;
}

void UnoSystem::ExecuteReverseCard() const
{
    _turnManager->RevertPlayOrder();
}

void UnoSystem::ExecutePlusTwoCard(int& outAmountToDraw) const
{
    constexpr int amountToDrawTwo = 2;
    outAmountToDraw += amountToDrawTwo;
}

void UnoSystem::ExecuteBlockCard() const
{
    _turnManager->ExecuteTurn(1);
}

void UnoSystem::ExecuteSpecialAction(const CardBehaviour& cardPlayed, int& outAmountToDraw) const
{
    const CardTypes playedCardType = cardPlayed.GetCardData().type;

    if (playedCardType == CardTypes::Reverse)
    {
        ExecuteReverseCard();
    }
    
    else if (playedCardType == CardTypes::PlusTwo || playedCardType == CardTypes::PlusTwoDiscard)
    {
        ExecutePlusTwoCard(outAmountToDraw);
    }

    // add +4, +10, etc.

    else if (playedCardType == CardTypes::Block)
    {
        ExecuteBlockCard(); 
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

bool UnoSystem::HaveTheSameColor(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const
{
    return _rulesManager->CheckCardColor(cardPlayed, cardOnTopOfTossDeck);
}

bool UnoSystem::HaveTheSameNumberAndType(const CardBehaviour& cardOnTopOfTossDeck,
    const CardBehaviour& cardPlayed) const
{
    return _rulesManager->CheckCardNumber(cardPlayed, cardOnTopOfTossDeck) &&
        _rulesManager->CheckCardType(cardPlayed, cardOnTopOfTossDeck);
}

void UnoSystem::HandleInvalidPlay() const
{
    std::cout << "Invalid play... Colors must match!\n";
    _visualizationManager->WaitForInput();
}

bool UnoSystem::FollowBasicUNORules(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const
{
    if (HaveTheSameColor(cardOnTopOfTossDeck, cardPlayed) ||
        HaveTheSameNumberAndType(cardOnTopOfTossDeck, cardPlayed))
    {
        return true;
    }
    
    HandleInvalidPlay();
    return false;
}

void UnoSystem::GivePlayersInitialCards(std::vector<PlayerBehaviour>& players) const
{
    const int initialHandSize = _cardManager->GetInitialHandSize();
    for (int i = 0; i < static_cast<int>(players.size()); i++)
    {
        for (int j = 0; j < initialHandSize; j++)
        {
            const CardBehaviour card = _cardManager->PopNextCardFromDrawDeck();
            players[i].ReceiveCard(card);
        }
    }
}

void UnoSystem::SetupBoard(std::vector<PlayerBehaviour>& players) const
{
    _visualizationManager->ClearScreen();
    _cardManager->ShuffleCards();
    
    GivePlayersInitialCards(players);

    _turnManager->SetInitialPlayOrder(players);
    _turnManager->ShowPlayOrder();
}

void UnoSystem::HandleInvalidAmountOfPlayers() const
{
    std::cout << "The amount of players must be between 2 and 10.\n";
    _visualizationManager->WaitForInput();
}

void UnoSystem::GetPlayersNames(std::vector<std::string>& outNames, const int amountOfPlayers) const
{
    for (int i = 0; i < amountOfPlayers; i++)
    {
        std::string AskForAName = "Insert a name ";
        std::string name = _visualizationManager->AskForInput<std::string>(AskForAName);

        outNames.emplace_back(name);
    }
}

void UnoSystem::GetPlayersInfo(std::vector<std::string>& outNames) const
{
    _visualizationManager->ClearScreen();

    const int amountOfPlayers = GetAmountOfPlayers();
    if (!IsAmountOfPlayersValid(amountOfPlayers))
    {
        HandleInvalidAmountOfPlayers();
        GetPlayersInfo(outNames);
        return;
    }
    
    outNames.reserve(amountOfPlayers);
    GetPlayersNames(outNames, amountOfPlayers);
}


void UnoSystem::PlayerDrawCardFromTossDeck(PlayerBehaviour& playerOfTheRound) const
{
    playerOfTheRound.ReceiveCard(_cardManager->PopRandomCardFromTossDeck());
}

int UnoSystem::GetAmountOfPlayers() const
{
    const std::string QuestionNumberOfPlayers = "How many players are going to play? ";
    return _visualizationManager->AskForInput<int>(QuestionNumberOfPlayers);
}

bool UnoSystem::IsAmountOfPlayersValid(int amountOfPlayers) const
{
    return _inputManager->IsValid(amountOfPlayers, _gameStateManager->GetCurrentState());
}

bool UnoSystem::IsMenuInputValid(int choice) const
{
    return _inputManager->IsValid(choice, _gameStateManager->GetCurrentState());
}

bool UnoSystem::CheckUNOShoutInput(const int cardIndex) const
{
    return cardIndex == _inputManager->GetShoutUNOInput();
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