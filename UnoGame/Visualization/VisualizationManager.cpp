#include <stdlib.h>
#include "VisualizationManager.h"


void VisualizationManager::Setup()
{
    std::cout << "Setting up Visualization Manager\n";
}

void VisualizationManager::Finish()
{
}

void VisualizationManager::ClearScreen()
{
    system("cls");
}

void VisualizationManager::WaitForInput()
{
    system("pause");
}

void VisualizationManager::ShowTable(const CardBehaviour& cardOnTopOfTossDeck, const std::vector<CardBehaviour>& playerCards)
{
    std::cout << "Card on the board\n";
    ShowCard(cardOnTopOfTossDeck);
    std::cout << "\n---------------------\nCards on hand:\n";

    for (int i = 0; i < playerCards.size(); i++)
    {
        std::cout << "[" << i << "]\n";
        ShowCard(playerCards[i]);
    }
}

void VisualizationManager::ShowCard(const CardBehaviour& card) const
{
    std::cout << "{\n"
                 "\t" << "Color: " << CardColors[card.GetCardData().color] <<
                 "\n\t" << "Type: " << CardTypes[card.GetCardData().type] <<
                 "\n\t" << "Number: " << card.GetCardData().number <<
                 "\n}\n";
}
