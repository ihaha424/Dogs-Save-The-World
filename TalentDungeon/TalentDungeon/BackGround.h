#pragma once
#include "Object.h"

class BackGround :
    public game::Object
{
public:
    BackGround();
    ~BackGround();

    virtual void FixedUpdate();
    virtual void Update();
    virtual void Render(HDC& _dc);
};

