#include "PlayerBehaviour.h"

#include <iostream>

PlayerBehaviour::PlayerBehaviour(std::string&& name)
    : playerName(std::move(name))
{
    std::cout << "Created player " << playerName << "\n";
}

void PlayerBehaviour::ReceiveCard(CardBehaviour card)
{
    cardsOnHand.emplace_back(card);
}

void PlayerBehaviour::RemoveCardFromHandByIndex(int cardIndex)
{
    cardsOnHand.erase(cardsOnHand.begin() + cardIndex);
}

CardBehaviour& PlayerBehaviour::GetSelectedCard(int cardOnHandID)
{
    return cardsOnHand[cardOnHandID];
}

const std::vector<CardBehaviour>& PlayerBehaviour::GetCards()
{
    return cardsOnHand;
}

std::string* PlayerBehaviour::GetName()
{
    return &playerName;
}


