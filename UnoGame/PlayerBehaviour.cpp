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
    // std::cout << "amount of cards on " << playerName << "'s hand: " << cardsOnHand.size() << "\n"; 
}

const std::vector<CardBehaviour>& PlayerBehaviour::GetCards()
{
    return cardsOnHand;
}

std::string* PlayerBehaviour::GetName()
{
    return &playerName;
}


