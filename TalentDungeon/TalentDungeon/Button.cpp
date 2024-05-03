#include "Button.h"
#include "InputSystem.h"

namespace game
{
	Button::Button(const char* _UIName, OBJECT_TYPE _UIjType)
		:UI(_UIName, _UIjType), curStatus(ButtonStatus::Default), PrevOnMouse(false) {}
	
	Button::~Button() {}

	bool Button::IsButtonOnMouse(gameMath::Vector3 mousePos)
	{
		gameMath::Transform LTranform = this->transform;
		bool A1 = (LTranform._position._y - LTranform._scale._y / 2.f) > (mousePos._y);
		bool A2 = (LTranform._position._y + LTranform._scale._y / 2.f) < (mousePos._y);
		bool B1 = (LTranform._position._x + LTranform._scale._x / 2.f) < (mousePos._x);
		bool B2 = (LTranform._position._x - LTranform._scale._x / 2.f) > (mousePos._x);
		if (A1 || A2 || B1 || B2)
			return false;
		return true;
	}

	void Button::CurButtonStatus()
	{
		const input::MouseState& MousePos = input::InputSystem::GetInstance()->GetMouseState();
		gameMath::Vector3 dirVector(MousePos.x, MousePos.y, 0);
		bool curOnMouse = IsButtonOnMouse(dirVector);
		if (curOnMouse)
		{
			//이전에도 충돌중이고 지금도 충돌중
			if (PrevOnMouse)
			{
				curStatus = ButtonStatus::OnMouse;
			}
			else //이전에는 충돌하지 않았지만 지금은 충돌중 -> 방금 만남
			{
				PrevOnMouse = true;
				curStatus = ButtonStatus::EnterMouse;
			}
		}
		else
		{
			//이전에도 충돌중이지만 지금 충돌X
			if (PrevOnMouse)
			{
				PrevOnMouse = false;
				curStatus = ButtonStatus::ExitMouse;
			}
			else
				curStatus = ButtonStatus::Default;
		}
	}
	Button::ButtonStatus Button::GetButtonStatus()
	{
		return curStatus;
	}
}
