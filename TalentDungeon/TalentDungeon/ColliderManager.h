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
		//���� �������� �浹 ����
		//�̰��� �־���� ���Դ��� �浹������ �������� �� �� �ִ�.
		//������ ���̵� ���� �ΰ��� �������� Hash�� ���Ͽ� ���� ����
		//UNION�� ���� ���̵� 1, ���̵� 2�� �Ѱ��� ������ �� �� ����
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

