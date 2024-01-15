#include "CardManager.h"

void CardManager::Setup()
{
    std::cout << "Setting up Card Manager\n";
    _drawDeck.reserve(_initialDeckSize);
    CreateAllCards();
}

void CardManager::Finish()
{
}

void CardManager::CreateAllCards()
{
    CreateCardsFromColor(CardColors::Red);
    CreateCardsFromColor(CardColors::Blue);
    CreateCardsFromColor(CardColors::Yellow);
    CreateCardsFromColor(CardColors::Green);

    std::cout << "All cards created! Total of: " << _drawDeck.size() << "\n";
}

void CardManager::CreateCardsFromColor(CardColors color)
{
    CreateNumberCards(color);
    CreateReverseCards(color);
    CreateBlockCards(color);
    CreatePlusCards(color);
}

void CardManager::CreateNumberCards(CardColors color)
{
    for (int i = _minNumberOnCards; i <= _maxNumberOnCards; i++)
    {
        CreateCardsAndAddToDrawDeck(color, CardTypes::Number, i, 0);
    }

    for (int i = _minNumberOnCards; i <= _maxNumberOnCards; i++)
    {
        CreateCardsAndAddToDrawDeck(color, CardTypes::Number, i, 0);
    }
}

void CardManager::CreateReverseCards(CardColors color)
{
    for (int i = 0; i < _amountOfReverseCardsPerColor; i++)
    {
        CreateCardsAndAddToDrawDeck(color, CardTypes::Reverse, -1, 0);
    }
}

void CardManager::CreateBlockCards(CardColors color)
{
    for (int i = 0; i < _amountOfBlockCardsPerColor; i++)
    {
        CreateCardsAndAddToDrawDeck(color, CardTypes::Block, -1, 0);
    }
}

void CardManager::CreatePlusCards(CardColors color)
{
    for (int i = 0; i < _amountOfPlusTwoCardsPerColor; i++)
    {
        CreateCardsAndAddToDrawDeck(color, CardTypes::Plus, -1, 2);
    }
}

void CardManager::CreateCardsAndAddToDrawDeck(CardColors color, CardTypes type, int number, int amountToAdd)
{
    CardBehaviour card{color, type, number, amountToAdd};
    _drawDeck.emplace_back(card);
}


void CardManager::ShuffleCards()
{
    // TODO - Make a seed
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(_drawDeck), std::end(_drawDeck), rng);
}

void CardManager::RemoveCardFromDrawDeck()
{
    _drawDeck.erase(_drawDeck.begin() + 1);
}

CardBehaviour CardManager::PopNextCardFromDrawDeck()
{
    CardBehaviour selectedCard = _drawDeck.back();

    _drawDeck.pop_back();
    
    return selectedCard;
}

int CardManager::GetInitialHandSize()
{
    return _initialHandSize;
}
