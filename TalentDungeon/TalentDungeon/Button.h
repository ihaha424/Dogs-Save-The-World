#pragma once
#include "UI.h"
namespace game
{

    class Button :
        public UI
    {
    protected:
        enum ButtonStatus
        {
            Default,
            EnterMouse,
            OnMouse,
            ExitMouse,
        };
        ButtonStatus curStatus;
        bool        PrevOnMouse;
    public:
        Button(const char* _UIName = "Default", OBJECT_TYPE _UIType = OBJECT_TYPE::UI);
        virtual ~Button();

        bool IsButtonOnMouse(gameMath::Vector3 mousePos);
        void CurButtonStatus();
        ButtonStatus GetButtonStatus();

        virtual void FixedUpdate() = 0;
        virtual void Update() = 0;
        virtual void Render(HDC& _dc) = 0;
    };
}

