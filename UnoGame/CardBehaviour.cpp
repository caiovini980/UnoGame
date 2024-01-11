#include "CardBehaviour.h"

CardBehaviour::CardBehaviour(CardColors color, CardTypes type, int number, int amountToAdd)
{
    _data.color = color;
    _data.type = type;
    _data.number = number;
    _data.amountToDrawNext = amountToAdd;
}

CardData CardBehaviour::GetCardData() const
{
    return _data;
}
