#pragma once
#include <Windows.h>
#include "Object.h"
#include "Transform.h"
#include "Define.h"

namespace game
{
	class	Texture;
	enum	Status;
	class UI : public game::Object
	{
	public:
		UI(const char* _UIName = "Default", OBJECT_TYPE _UIType = OBJECT_TYPE::UI);
		virtual ~UI();

		virtual void FixedUpdate() = 0;
		virtual void Update() = 0;
		virtual void Render(HDC& _dc) = 0;
	};
}

