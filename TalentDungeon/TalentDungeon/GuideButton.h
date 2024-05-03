#pragma once
#include "Button.h"
class GuideButton :
    public game::Button
{
private:
    int flag;
public:
    GuideButton();
    ~GuideButton();

    virtual void FixedUpdate();
    virtual void Update();
    virtual void Render(HDC& _dc);
};

