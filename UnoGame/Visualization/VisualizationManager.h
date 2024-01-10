#pragma once
#include "../ManagerBase.h"

class VisualizationManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    void ClearScreen();
    void WaitForInput();

    
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
};
