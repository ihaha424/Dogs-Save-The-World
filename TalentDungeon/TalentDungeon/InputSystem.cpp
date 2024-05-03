#include "InputSystem.h"
#include "WinApp.h"

namespace input
{
	int KeyArr[KEY::LAST] =
	{
		VK_LEFT,
		VK_UP,
		VK_DOWN,
		VK_RIGHT,
		'Q',
		'W',
		'E',
		'R',
		'T',
		'Y',
		'U',
		'I',
		'O',
		'P',
		'A',
		'S',
		'D',
		'F',
		'G',
		'Z',
		'X',
		'C',
		'V',
		'B',
		'J',
		'K',
		VK_MENU,
		VK_LSHIFT,
		VK_SPACE,
		VK_CONTROL,
		VK_RETURN,
		VK_ESCAPE,
		VK_LBUTTON,
		VK_RBUTTON,
		VK_MBUTTON
	};

	InputSystem* InputSystem::instance = nullptr;
	InputSystem::InputSystem() {}
	InputSystem::~InputSystem() {}

	InputSystem* InputSystem::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new InputSystem();
		}
		return instance;
	}

	void InputSystem::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void InputSystem::InitInput()
	{
		for (int i = 0; i < KEY::LAST; ++i)
		{
			keyList.PushBack(KeyInfo{ KEY_STATE::NONE, false });
		}
		InitMouse();
	}

	void InputSystem::InitMouse()
	{
		hWnd = global::GetWinApp().GetWindow();
		curMouse.x = ScreenWidth / 2;
		curMouse.y = ScreenHeight / 2;
		curMouse.wheel = 0;

		curMouse.left = false;
		curMouse.right = false;
		curMouse.middle = false;

		prevMouse = curMouse;

		SetCursorPos(curMouse.x, curMouse.y);
	}

	void InputSystem::Update()
	{
		/*
			포커스(활성화) 되고 있는 원도우가 현재 다루는 원도우가 아닌때도 가능
			tmp = GetMainHwnd();
			tmp == hWnd
		*/
		//현재 포커스(활성화) 되고 있는 원도우가 Null이 아니면
		HWND hWnd = GetFocus();

		if (nullptr != hWnd)
		{
			for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
			{
				if (GetAsyncKeyState(KeyArr[i]) & 0x8000)
				{
					if (keyList[i].isPush)
					{
						keyList[i].state = KEY_STATE::HOLD;
					}
					else
					{
						keyList[i].state = KEY_STATE::TAP;
					}
					keyList[i].isPush = true;
				}
				else
				{
					if (keyList[i].isPush)
					{
						keyList[i].state = KEY_STATE::AWAY;
					}
					else
					{
						keyList[i].state = KEY_STATE::NONE;
					}
					keyList[i].isPush = false;
				}
			}
		}
		else
		{
			ResetInput();
		}
		UpdateMouse();
	}

	KEY_STATE InputSystem::GetKeyState(KEY key)
	{
		return keyList[key].state;
	}

	void InputSystem::ResetInput()
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); ++i)
		{
			keyList[i].isPush = false;
			if (keyList[i].state == KEY_STATE::TAP || keyList[i].state == KEY_STATE::HOLD)
			{
				keyList[i].state = KEY_STATE::AWAY;
			}
			else if (keyList[i].state == KEY_STATE::AWAY)
			{
				keyList[i].state = KEY_STATE::NONE;
			}
		}
	}

	void InputSystem::UpdateMouse()
	{
		prevMouse = curMouse;

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		curMouse.x = pt.x;
		curMouse.y = pt.y;
		curMouse.wheel = 0;

		curMouse.left = (GetKeyState(L_MOUSE_BUTTON) & 0x8000) != 0;
		curMouse.right = (GetKeyState(R_MOUSE_BUTTON) & 0x8000) != 0;
		curMouse.middle = (GetKeyState(M_MOUSE_BUTTON) & 0x8000) != 0;
	}

	bool InputSystem::IsSame(const MouseState& a, const MouseState& b)
	{
		return a.x == b.x && a.y == b.y && a.wheel == b.wheel && a.left == b.left && a.right == b.right && a.middle == b.middle;

	}

	const MouseState& InputSystem::GetMouseState()
	{
		return curMouse;
	}

	const MouseState& InputSystem::GetPrevMouseState()
	{
		return prevMouse;
	}

}