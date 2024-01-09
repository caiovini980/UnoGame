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
