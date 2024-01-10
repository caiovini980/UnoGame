#include "CardBehaviour.h"

CardBehaviour::CardBehaviour(CardColors color, CardTypes type, int number, int amountToAdd)
    : _cardColor(color), _cardType(type), _cardNumber(number), _amountToDrawNext(amountToAdd)
{
    
}
