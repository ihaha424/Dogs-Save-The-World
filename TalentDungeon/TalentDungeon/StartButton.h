#pragma once
#include "Button.h"
class StartButton :
    public game::Button
{
private:
    int flag;
public:
    StartButton();
    ~StartButton();

    virtual void FixedUpdate();
    virtual void Update();
    virtual void Render(HDC& _dc);
};

