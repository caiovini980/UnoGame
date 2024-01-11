#pragma once
#include <string>
#include <vector>

#include "CardBehaviour.h"

class PlayerBehaviour
{
public:
    PlayerBehaviour(std::string&& name);
    ~PlayerBehaviour() = default;
    
    void ReceiveCard(const CardBehaviour& card);
    void PlayCard(const CardBehaviour& card);
    void GetCards();
    std::string* GetName();
    
private:
    std::vector<CardBehaviour> cardsOnHand;
    std::string playerName;
};
