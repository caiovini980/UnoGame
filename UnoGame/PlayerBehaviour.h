#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "CardBehaviour.h"

class PlayerBehaviour
{
public:
    PlayerBehaviour(std::string&& name);
    ~PlayerBehaviour() = default;

    // PlayerBehaviour(PlayerBehaviour& other)
    // {
    //     std::cout << "Copying PlayerBehaviour\n";
    // }
    
    
    void ReceiveCard(CardBehaviour card);
    void RemoveCardFromHandByIndex(int cardIndex);
    CardBehaviour& GetSelectedCard(int cardOnHandID);
    
    const std::vector<CardBehaviour>& GetCards();
    std::string* GetName();
    
private:
    std::vector<CardBehaviour> cardsOnHand;
    std::string playerName;
};
