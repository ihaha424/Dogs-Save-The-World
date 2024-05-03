#pragma once

#include "Define.h"
#include "LinkedHashMap.hpp"
#include "Vector.hpp"
#include <Windows.h>

namespace game
{
	class Collider;
	class Object;

	union ColliderID
	{
		struct {
			UINT LeftID;
			UINT RightID;
		};
		LONGLONG ID;
	};

	class ColliderManager
	{
	private:
		static ColliderManager* instance;

		CTN::Vector<Object*>	colliderArr[(UINT)OBJECT_TYPE::END];
		UINT	checkArr[(UINT)OBJECT_TYPE::END];
		//이전 프레임의 충돌 정보
		//이것이 있어야지 들어왔는지 충돌중인지 나갔는지 알 수 있다.
		//고유한 아이디를 통해 두개의 조합으로 Hash를 통하여 값을 저장
		//UNION을 통해 아이디 1, 아이디 2를 한개의 변수로 볼 수 있음
		CTN::LinkedHashMap<long long, bool> collisionInfo;
	public:

	private:
		ColliderManager();
		~ColliderManager();

		void CollisionCheck(OBJECT_TYPE lhs, OBJECT_TYPE rhs);
		bool IsCollision(Collider* lhs, Collider* rhs);

	public:
		static ColliderManager* GetInstance();
		static void DestroyInstance();

		void Initialize();
		void Update();
		void FinalUpdate();
		void DestoryUpdate();
		void AddColliderObject(Object* obj, OBJECT_TYPE type);
		void CheckGourp(OBJECT_TYPE lhs, OBJECT_TYPE rhs);
		void ResetGourp();

	};
}

