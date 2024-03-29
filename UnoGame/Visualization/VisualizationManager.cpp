﻿#include <stdlib.h>
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

void VisualizationManager::ShowBoard(const CardBehaviour& cardOnTopOfTossDeck, const std::vector<CardBehaviour>& playerCards, bool canShoutUno) const
{
    std::cout << "Card on the board: \n";
    ChangeTextColorByCard(cardOnTopOfTossDeck);
    WriteCardInfo(cardOnTopOfTossDeck);

    std::cout << RESET_COLOR_CODE;
    std::cout << "\n---------------------\nCards on hand:\n";

    // show Uno option if player have 2 cards on hand
    if (canShoutUno)
    {
        std::cout << "[ -2 ]\tSHOUT UNO\n";
    }
    
    std::cout << "[ -1 ]\tDRAW CARD\n";
    // indexes
    for (int i = 0; i < static_cast<int>(playerCards.size()); i++)
    {
        std::cout << RESET_COLOR_CODE;
        std::cout << "[" << i << "]\t";
        ChangeTextColorByCard(playerCards[i]);
        WriteCardInfo(playerCards[i]);
        std::cout << "\n";
    }
    
    std::cout << RESET_COLOR_CODE;
    std::cout << "\n";
}

void VisualizationManager::ShowWarningText(const std::string& text) const
{
    std::cout << YELLOW_COLOR_CODE << text << RESET_COLOR_CODE;
}

void VisualizationManager::ShowWinner(const std::string& winnerName)
{
    std::cout << GREEN_COLOR_CODE << winnerName << "WON THE MATCH!\n" << RESET_COLOR_CODE;
}

void VisualizationManager::WriteCardInfo(const CardBehaviour& card) const
{
    if (card.GetCardData().type != Number)
    {
        std::cout << "[ " << CardTypes[card.GetCardData().type] << " ]";
        return;
    }
    
    std::cout << "[ " << card.GetCardData().number << " ]";
}

void VisualizationManager::ChangeTextColorByCard(const CardBehaviour& card) const
{
    switch (card.GetCardData().color) {
    case Green:
        std::cout << GREEN_COLOR_CODE;
        break;
        
    case Yellow:
        std::cout << YELLOW_COLOR_CODE;
        break;
        
    case Blue:
        std::cout << BLUE_COLOR_CODE;
        break;
        
    case Red:
        std::cout << RED_COLOR_CODE;
        break;
    }
}
