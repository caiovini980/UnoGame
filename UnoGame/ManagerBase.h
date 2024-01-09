#pragma once
#include <iostream>

class ManagerBase
{
public:
    virtual void Setup() = 0;
    virtual void Finish() = 0;
    
protected:
    virtual ~ManagerBase() = default;
};
