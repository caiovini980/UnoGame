#pragma once
#include "../ManagerBase.h"

class VisualizationManager : public ManagerBase
{
public:
    void Setup() override;
    void Finish() override;

    void ClearScreen();
    void WaitForInput();
};
