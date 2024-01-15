#pragma once
#include <vector>

#include "../ManagerBase.h"
#include "../CardBehaviour.h"

class VisualizationManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    void ClearScreen();
    void WaitForInput();
    void ShowTable(const CardBehaviour& cardOnTopOfTossDeck, const std::vector<CardBehaviour>& playerCards);
    
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
    const char* CardTypes[4] = { "Number", "Block", "Plus", "Reverse" };
    
    void ShowCard(const CardBehaviour& card) const;
};
