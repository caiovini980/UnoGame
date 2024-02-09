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

    bool _isGameOver = false;
    
    // VOID METHODS
    // 0 Params
    void StartGame();
    void ShowRules();
    void CloseGame();
    void ShowMenu();
    void StartMenu();
    void ExecuteGameLoop();

    void HandleInvalidMenuInput() const;
    void SetupManagers() const;
    void ClearScreenAndShowPlayOrder() const;
    void ExecuteReverseCard() const;
    void HandleInvalidPlay() const;
    void ExecuteBlockCard() const;
    void HandleInvalidAmountOfPlayers() const;
    void InitializePlayersAndSetupBoard() const;

    // 1 Param
    void HandleShoutUNORuleViolation(PlayerBehaviour& playerOfTheRound);
    void ExecuteGameOver(PlayerBehaviour& playerOfTheRound);
    void CheckGameOver(PlayerBehaviour& playerOfTheRound);
    void PlayerDrawCard(PlayerBehaviour& nextPlayer);
    void HandleValidMenuInput(int choice);

    void SetupBoard(std::vector<PlayerBehaviour>& players) const;
    void ExecutePlusTwoCard(int& outAmountToDraw) const;
    void GivePlayersInitialCards(std::vector<PlayerBehaviour>& players) const;
    void GetPlayersInfo(std::vector<std::string>& outNames) const;

    // 2 Params
    void HandlePlusCardAdditionViolation(int& amountToDraw, PlayerBehaviour& playerOfTheRound);
    void BuyDesiredAmountOfCards(int amountToDraw, PlayerBehaviour& playerOfTheRound);

    void GetPlayersNames(std::vector<std::string>& outNames, int amountOfPlayers) const;
    void ShowPlayerOfTheRoundAndBoard(PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck) const;
    void CheckSpecialCard(int amountToDraw, CardBehaviour cardPlayed) const;
    void ExecuteSpecialAction(const CardBehaviour& cardPlayed, int& outAmountToDraw) const;

    // 3 Params
    void CheckWhenHaveAPlusCardOnTopOfTossDeck(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardOnTopOfTossDeck);
    void CheckPlusCardWhenNeeded(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardPlayed);
    void CheckShoutUNORule(bool shoutedUNO, PlayerBehaviour& playerOfTheRound, bool mustShoutUnoThisRound);
    void CheckPlusCards(int& amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck);
    void CheckPreTurnRules(int& amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck);

    void PlayCardAndChangeTurn(PlayerBehaviour& playerOfTheRound, int cardIndex, CardBehaviour cardPlayed) const;
    void ExecutePlusTwoDiscard(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardOnTopOfTossDeck) const;

    void PlayerDrawCardFromTossDeck(PlayerBehaviour& playerOfTheRound) const;

    // 4 Params
    void CheckPostTurnRules(bool shoutedUNO, int amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardPlayed);

    // INT METHODS
    int GetAmountOfPlayers() const;
    int GetPlayerInput() const;

    // BOOL METHODS
    // 1 Param
    bool IsMenuInputValid(int choice) const;
    bool IsAmountOfPlayersValid(int amountOfPlayers) const;
    bool CheckUNOShoutInput(int cardIndex) const;

    // 2 Params
    bool CheckDrawInput(PlayerBehaviour& playerOfTheRound, int cardIndex);
    bool IsInputInvalid(PlayerBehaviour& playerOfTheRound, int cardIndex) const;
    bool FollowBasicUNORules(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const;
    bool HaveTheSameColor(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const;
    bool HaveTheSameNumberAndType(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed) const;

    // 3 Params
    bool IsInputSpecial(bool& shoutedUNO, PlayerBehaviour& playerOfTheRound, int cardIndex);

};
