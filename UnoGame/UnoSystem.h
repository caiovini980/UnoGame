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

    void SetupBoard(std::vector<PlayerBehaviour>& players) const;
    
    void StartMenu();
    void ExecuteGameLoop();

    void CheckPreTurnRules(int& amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck);
    void ShowPlayerOfTheRoundAndBoard(PlayerBehaviour& playerOfTheRound, CardBehaviour cardOnTopOfTossDeck) const;
    void CheckShoutUNORule(bool shoutedUNO, PlayerBehaviour& playerOfTheRound, bool mustShoutUnoThisRound);
    void CheckPlusCardWhenNeeded(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardPlayed);
    void CheckGameOver(PlayerBehaviour& playerOfTheRound);
    void PlayCardAndChangeTurn(PlayerBehaviour& playerOfTheRound, int cardIndex, CardBehaviour cardPlayed) const;
    void CheckSpecialCard(int amountToDraw, CardBehaviour cardPlayed) const;
    void CheckPostTurnRules(bool shoutedUNO, int amountToDraw, PlayerBehaviour& playerOfTheRound, CardBehaviour cardPlayed);
    bool IsInputInvalid(PlayerBehaviour& playerOfTheRound, int cardIndex) const;
    bool IsInputSpecial(bool& shoutedUNO, PlayerBehaviour& playerOfTheRound, int cardIndex);
    void ClearScreenAndShowPlayOrder() const;
    void ExecutePlusTwoDiscard(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardOnTopOfTossDeck) const;
    void PlayerDrawCard(PlayerBehaviour& nextPlayer);
    void CheckWhenHaveAPlusCardOnTopOfTossDeck(int& amountToDraw, PlayerBehaviour& playerOfTheRound, const CardBehaviour& cardOnTopOfTossDeck);
    void BuyDesiredAmountOfCards(int amountToDraw, PlayerBehaviour& playerOfTheRound);
    bool FollowBasicUNORules(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed);
    void ExecuteSpecialAction(const CardBehaviour& cardPlayed, int& outAmountToDraw) const;
    void GetPlayersInfo(std::vector<std::string>& outNames) const;
    
    void StartGame();
    void ShowRules();
    void CloseGame();

    bool _isGameOver = false;
};
