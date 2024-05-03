#pragma once
#include <Windows.h>
#include "Define.h"
#include "Vector.hpp"


namespace game
{
	class Object;
	class Scene {
	private:
		CTN::Vector<Object*>	objArr[(UINT)OBJECT_TYPE::END];
		const char* name;
		
	public:
		Scene();
		virtual ~Scene();

		void SetName(const char* _Name);
		const char* GetName();

		void FixedUpdate();
		void Update();
		void DestoryUpdate();
		void FinalUpdate();
		void Render(HDC& _dc);

		virtual void Enter() = 0;
		virtual void Exit() = 0;
		
		void AddObject(Object* obj, OBJECT_TYPE type);
		void EraseObject(OBJECT_TYPE type, UINT index);
		//바꾸지 못하게 const값을 전달 해줘야함으로 &
		const CTN::Vector<Object*>& GetGroupObject(OBJECT_TYPE type);
		Object* GetObjectSrc(OBJECT_TYPE _type, const char* _name);
	};
}