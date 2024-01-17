#pragma once
#include <string>
#include <vector>

#include "CardBehaviour.h"

class PlayerBehaviour
{
public:
    PlayerBehaviour(std::string&& name);
    ~PlayerBehaviour() = default;
    
    void ReceiveCard(CardBehaviour card);
    CardBehaviour& GetSelectedCard(int cardOnHandID);
    
    const std::vector<CardBehaviour>& GetCards();
    std::string* GetName();
    
private:
    std::vector<CardBehaviour> cardsOnHand;
    std::string playerName;
};
