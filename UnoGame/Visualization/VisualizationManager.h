﻿#pragma once
#include <vector>

#include "../ManagerBase.h"
#include "../CardBehaviour.h"
#include "../PlayerBehaviour.h"

class VisualizationManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    void ClearScreen();
    void WaitForInput();
    void ShowBoard(const CardBehaviour& cardOnTopOfTossDeck, const std::vector<CardBehaviour>& playerCards, bool canShoutUno) const;
    void ShowWarningText(const std::string& text) const;
    void ShowWinner(const std::string& winnerName);
    
    
    // TEMPLATES
    template <class T> T AskForInput(const std::string& question)
    {
        T input{};
        std::cout << question;
        std::cin >> input;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            return AskForInput<T>(question);
        }

        return input;
    }

private:
    const char* CardColors[4] = { "Green", "Yellow", "Blue", "Red" };
    const char* CardTypes[5] = { "Number", "Block", "+ 2", "+ 2 Discard", "Reverse" };

    const char* RESET_COLOR_CODE = "\033[0m";
    const char* RED_COLOR_CODE = "\033[1m\033[31m";
    const char* GREEN_COLOR_CODE = "\033[1m\033[32m";
    const char* YELLOW_COLOR_CODE = "\033[1m\033[33m";
    const char* BLUE_COLOR_CODE = "\033[1m\033[34m";
    
    const char* TAB_BETWEEN_CARDS = "\t\t\t";
    
    void ChangeTextColorByCard(const CardBehaviour& card) const;
    void WriteCardInfo(const CardBehaviour& card) const;
};
