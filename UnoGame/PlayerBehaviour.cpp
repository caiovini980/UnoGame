#include "PlayerBehaviour.h"

PlayerBehaviour::PlayerBehaviour(std::string&& name)
    : playerName(std::move(name))
{}

void PlayerBehaviour::ReceiveCard(CardBehaviour* card)
{
    cardsOnHand.push_back(card);
}

void PlayerBehaviour::PlayCard(int cardOnHandID)
{
    // cardsOnHand.
}

std::vector<CardBehaviour*>* PlayerBehaviour::GetCards()
{
    return &cardsOnHand;
}

std::string* PlayerBehaviour::GetName()
{
    return &playerName;
}


