#pragma once
#include <vector>

#include "CardBehaviour.h"

class PlayerBehaviour
{
public:
    void ReceiveCard(const CardBehaviour& card);
    void PlayCard(const CardBehaviour& card);
    void GetCards();
    
private:
    std::vector<CardBehaviour> cardsOnHand;
    
};
