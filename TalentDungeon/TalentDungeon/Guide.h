#pragma once
#include "Button.h"
class Guide :
    public  game::Button
{
private:
    int flag;
    int index;
public:
    Guide();
    ~Guide();

    virtual void FixedUpdate();
    virtual void Update();
    virtual void Render(HDC& _dc);
};

