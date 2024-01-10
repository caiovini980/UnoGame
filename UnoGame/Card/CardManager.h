#pragma once
#include <vector>

#include "../CardBehaviour.h"
#include "../ManagerBase.h"

class CardManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    // void ShuffleDeck();

private:
    std::vector<CardBehaviour> _drawDeck;
    std::vector<CardBehaviour> _tossDeck;

    int _initialDeckSize = 104;
    int _initialHandSize = 7;
    
    int _amountOfNumberCardsPerColor = 20;
    int _amountOfReverseCardsPerColor = 2;
    int _amountOfPlusTwoCardsPerColor = 2;
    int _amountOfBlockCardsPerColor = 2;
    
    int _maxNumberOnCards = 9;
    int _minNumberOnCards = 0;

    void CreateAllCards();
    void CreateNumberCards(CardColors color);
    void CreateReverseCards(CardColors color);
    void CreateBlockCards(CardColors color);
    void CreatePlusCards(CardColors color);
    void CreateCardsFromColor(CardColors color);
    void CreateCardsAndAddToDrawDeck(CardColors color, CardTypes type, int number, int amountToAdd);
};
