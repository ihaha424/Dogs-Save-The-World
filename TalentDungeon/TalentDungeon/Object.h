#pragma once
#include <Windows.h>
#include "Transform.h"
#include "Define.h"
//#include "Texture.h"
//#include "Collider.h"

//->componet.h
//Vector<componet> a;

namespace game
{
	class Collider;
	class Texture;
	enum Status;


	class Object
	{
	public:
		const char*			objName;
		OBJECT_TYPE			objType;
		gameMath::Transform transform;
		Status				_status;
		Texture**			texture;
		UINT				textureSize;
		Collider*			collider;

	public:
		Object(const char* _objName = "Default", OBJECT_TYPE _objType = OBJECT_TYPE::DEFAULT);
		virtual ~Object();

		//Texture�� transform�� componet�� ���� �Ǹ� �̷������� �ϸ� ���� �ʳ�?
		void CreateCollider();
		Collider* GetCollider();

		void SetObjName(const char* _name);
		const char* GetObjName();

		void SetObjType(OBJECT_TYPE _type);
		OBJECT_TYPE GetObjType();

		void SetObjStatus(Status _type);
		Status GetObjStatus();

		virtual void OnCollision(Collider* src);//���� �浹��
		virtual void OnCollisionEnter(Collider* src);//��� �浹
		virtual void OnCollisionExit(Collider* src);//��� �浹X

		virtual void FixedUpdate() = 0;
		virtual void Update() = 0;
		virtual void FinalUpdate() final;
		virtual void ComponentRender(HDC& _dc) final;
		virtual void Render(HDC& _dc) = 0;
	};
}
