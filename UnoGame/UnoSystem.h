#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Card/CardManager.h"
#include "Input/InputManager.h"
#include "Player/PlayerManager.h"
#include "Rules/RulesManager.h"
#include "Turn/TurnManager.h"
#include "Visualization/VisualizationManager.h"
#include "GameState/GameStateManager.h"

class UnoSystem
{
public:
    UnoSystem();
    ~UnoSystem() = default;

private:
    std::unique_ptr<CardManager> _cardManager = std::make_unique<CardManager>();
    std::unique_ptr<InputManager> _inputManager = std::make_unique<InputManager>();
    std::unique_ptr<PlayerManager> _playerManager = std::make_unique<PlayerManager>();
    std::unique_ptr<RulesManager> _rulesManager = std::make_unique<RulesManager>();
    std::unique_ptr<TurnManager> _turnManager = std::make_unique<TurnManager>();
    std::unique_ptr<VisualizationManager> _visualizationManager = std::make_unique<VisualizationManager>();
    std::unique_ptr<GameStateManager> _gameStateManager = std::make_unique<GameStateManager>();
    
    void SetupManagers() const;
    bool IsMenuInputValid(int choice) const;
    void HandleValidMenuInput(int choice);
    void HandleInvalidMenuInput() const;
    void ShowMenu();

    void SetupBoard(std::vector<PlayerBehaviour>& players) const;
    void HandleInvalidAmountOfPlayers() const;
    void GetPlayersNames(std::vector<std::string>& outNames, int amountOfPlayers) const;
    int GetAmountOfPlayers() const;
    bool IsAmountOfPlayersValid(int amountOfPlayers) const;

    void StartMenu();
    void InitializePlayersAndSetupBoard() const;
    void ExecuteGameLoop();
    void CheckPlusCards(int& amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck);
    void CheckPreTurnRules(int& amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck);
    void ShowPlayerOfTheRoundAndBoard(PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck) const;
    void HandleShoutUNORuleViolation(PlayerBehaviour& playerOfTheRound);
    void CheckShoutUNORule(bool shoutedUNO, PlayerBehaviour& playerOfTheRound, bool mustShoutUnoThisRound);
    void HandlePlusCardAdditionViolation(int& amountToDraw, PlayerBehaviour& playerOfTheRound);
    void CheckPlusCardWhenNeeded(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardPlayed);
    void ExecuteGameOver(PlayerBehaviour& playerOfTheRound);
    void CheckGameOver(PlayerBehaviour& playerOfTheRound);
    void PlayCardAndChangeTurn(PlayerBehaviour& playerOfTheRound, int cardIndex, CardBehaviour cardPlayed) const;
    void CheckSpecialCard(int amountToDraw, CardBehaviour cardPlayed) const;
    void CheckPostTurnRules(bool shoutedUNO, int amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardPlayed);
    bool IsInputInvalid(PlayerBehaviour& playerOfTheRound, int cardIndex) const;
    bool CheckDrawInput(PlayerBehaviour& playerOfTheRound, int cardIndex);
    bool CheckUNOShoutInput(int cardIndex) const;
    bool IsInputSpecial(bool& shoutedUNO, PlayerBehaviour& playerOfTheRound, int cardIndex);
    void ClearScreenAndShowPlayOrder() const;
    void ExecutePlusTwoDiscard(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardOnTopOfTossDeck) const;
    void ExecuteReverseCard() const;
    void ExecutePlusTwoCard(int& outAmountToDraw) const;
    void ExecuteBlockCard() const;
    void PlayerDrawCard(PlayerBehaviour& nextPlayer);
    void CheckWhenHaveAPlusCardOnTopOfTossDeck(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardOnTopOfTossDeck);
    void BuyDesiredAmountOfCards(int amountToDraw, PlayerBehaviour& playerOfTheRound);
    bool HaveTheSameColor(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const;
    bool HaveTheSameNumberAndType(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const;
    void HandleInvalidPlay() const;
    bool FollowBasicUNORules(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const;
    void GivePlayersInitialCards(std::vector<PlayerBehaviour>& players) const;
    void ExecuteSpecialAction(const CardBehaviour& cardPlayed, int& outAmountToDraw) const;
    void GetPlayersInfo(std::vector<std::string>& outNames) const;
    
    void StartGame();
    int GetPlayerInput() const;
    void ShowRules();
    void CloseGame();

    bool _isGameOver = false;
};
