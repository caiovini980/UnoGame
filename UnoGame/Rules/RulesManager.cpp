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
