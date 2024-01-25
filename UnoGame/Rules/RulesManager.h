#pragma once
#include <vector>

#include "../ManagerBase.h"
#include "../CardBehaviour.h"

class RulesManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    bool CheckCardColor(const CardBehaviour& cardPlayed, const CardBehaviour& cardOnTop);
    bool CheckCardType(const CardBehaviour& cardPlayed, const CardBehaviour& cardOnTop);
    bool CheckCardNumber(const CardBehaviour& cardPlayed, const CardBehaviour& cardOnTop);
    bool CheckUNOShoutRule(const std::vector<CardBehaviour>& playerCards);
    bool CheckPlusRule(const CardBehaviour& cardOnTop, const std::vector<CardBehaviour>& playerCards);

    int GetAmountOfCardsToDrawWhenViolatesShoutUnoRule() const;

private:
    int _amountOfCardsForUnoShoutRule = 2;
    int _amountOfCardsToDrawIfDontShoutUno = 2;
};
