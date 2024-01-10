#pragma once
#include "CardTypes.h"
#include "CardColors.h"

class CardBehaviour
{
public:
    CardBehaviour(CardColors color, CardTypes type, int number = -1, int amountToAdd = 0);
    ~CardBehaviour() = default;
    
private:
    CardColors _cardColor;
    CardTypes _cardType;
    int _cardNumber;
    int _amountToDrawNext;
};
