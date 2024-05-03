#pragma once
#include "Object.h"
class StartUI :
    public game::Object
{
public:
    StartUI();
    ~StartUI();

    virtual void FixedUpdate();
    virtual void Update();
    virtual void Render(HDC& _dc);
};

