#pragma once
#include "CardTypes.h"
#include "CardColors.h"

struct CardData
{
    CardColors color;
    CardTypes type;
    int number;
    int amountToDrawNext;
};

class CardBehaviour
{
public:
    CardBehaviour(CardColors color, CardTypes type, int number = -1, int amountToAdd = 0);
    ~CardBehaviour() = default;

    CardData GetCardData() const;
    
private:
    CardData _data;
};
