#pragma once
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
};
