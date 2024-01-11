#include "PlayerBehaviour.h"

#include <iostream>

PlayerBehaviour::PlayerBehaviour(std::string&& name)
    : playerName(std::move(name))
{}

void PlayerBehaviour::ReceiveCard(CardBehaviour& card)
{
    cardsOnHand.push_back(&card);
}

// CardBehaviour* PlayerBehaviour::PlayCard(int cardOnHandID)
// {
//     // TODO TEST THIS
//     
//     // get card from this ID
//     // cache it on a variable
//     CardBehaviour* selectedCard = cardsOnHand[cardOnHandID];
//     
//     // remove this card from the hand
//     cardsOnHand.erase(
//         std::remove(
//             cardsOnHand.begin(),cardsOnHand.end(), selectedCard),cardsOnHand.end());
//     
//     // return the card cached on the variable
//     return selectedCard;
// }

std::vector<CardBehaviour*>* PlayerBehaviour::GetCards()
{
    return &cardsOnHand;
}

std::string* PlayerBehaviour::GetName()
{
    return &playerName;
}


