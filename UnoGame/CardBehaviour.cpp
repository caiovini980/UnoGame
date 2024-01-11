#include "CardBehaviour.h"

CardBehaviour::CardBehaviour(CardColors color, CardTypes type, int number, int amountToAdd)
    : _cardColor(color), _cardType(type), _cardNumber(number), _amountToDrawNext(amountToAdd)
{
    data.color = _cardColor;
    data.type = _cardType;
    data.number = _cardNumber;
    data.amountToDrawNext = _amountToDrawNext;
}

CardData CardBehaviour::GetCardData() const
{
    return data;
}
