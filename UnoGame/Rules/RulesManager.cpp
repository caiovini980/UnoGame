#include "RulesManager.h"

void RulesManager::Setup()
{
    std::cout << "Setting up Rules Manager\n";
}

void RulesManager::Finish()
{
}

bool RulesManager::CheckCardColor(const CardBehaviour& cardPlayed, const CardBehaviour& cardOnTop)
{
    return cardPlayed.GetCardData().color == cardOnTop.GetCardData().color;
}

bool RulesManager::CheckCardType(const CardBehaviour& cardPlayed, const CardBehaviour& cardOnTop)
{
    return cardPlayed.GetCardData().type == cardOnTop.GetCardData().type;
}

bool RulesManager::CheckCardNumber(const CardBehaviour& cardPlayed, const CardBehaviour& cardOnTop)
{
    return cardPlayed.GetCardData().number == cardOnTop.GetCardData().number;
}

bool RulesManager::CheckUNOShoutRule(const std::vector<CardBehaviour>& playerCards)
{
    return static_cast<int>(playerCards.size()) == _amountOfCardsForUnoShoutRule;
}

bool RulesManager::CheckPlusRule(const CardBehaviour& cardOnTop, const std::vector<CardBehaviour>& playerCards)
{
    bool havePlusCard = false;
    const CardTypes cardOnTopType = cardOnTop.GetCardData().type;
    
    for (const CardBehaviour& card : playerCards)
    {
        if (card.GetCardData().type == CardTypes::PlusTwo)
        {
            havePlusCard = true;
        }
    }

    return havePlusCard && (cardOnTopType == CardTypes::PlusTwo);
}

bool RulesManager::CheckPlusDiscardRule(const CardBehaviour& cardOnTop)
{
    return cardOnTop.GetCardData().type == CardTypes::PlusTwoDiscard;
}

bool RulesManager::CheckGameOver(const std::vector<CardBehaviour>& playerCards)
{
    return static_cast<int>(playerCards.size()) == 0;
}

int RulesManager::GetAmountOfCardsToDrawWhenViolatesShoutUnoRule() const
{
    return _amountOfCardsToDrawIfDontShoutUno;
}
