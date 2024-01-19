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
