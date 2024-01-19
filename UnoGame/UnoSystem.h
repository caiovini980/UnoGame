#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Action/ActionManager.h"
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
    std::unique_ptr<ActionManager> _actionManager = std::make_unique<ActionManager>();
    std::unique_ptr<CardManager> _cardManager = std::make_unique<CardManager>();
    std::unique_ptr<InputManager> _inputManager = std::make_unique<InputManager>();
    std::unique_ptr<PlayerManager> _playerManager = std::make_unique<PlayerManager>();
    std::unique_ptr<RulesManager> _rulesManager = std::make_unique<RulesManager>();
    std::unique_ptr<TurnManager> _turnManager = std::make_unique<TurnManager>();
    std::unique_ptr<VisualizationManager> _visualizationManager = std::make_unique<VisualizationManager>();
    std::unique_ptr<GameStateManager> _gameStateManager = std::make_unique<GameStateManager>();
    
    void SetupManagers() const;

    void SetupBoard(std::vector<std::string>& names);
    
    void StartMenu();
    bool FollowBasicUNORules(const CardBehaviour& cardOnTopOfTossDeck, const CardBehaviour& cardPlayed);
    void ExecuteSpecialAction(const CardBehaviour& cardPlayed);
    void GetPlayersInfo(std::vector<std::string>& outNames) const;
    void StartGame();
    void ShowRules();
    void CloseGame();

    bool _isGameOver = false;
};
