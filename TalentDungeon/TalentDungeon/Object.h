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

		//Texture나 transform도 componet로 묶게 되면 이런식으로 하면 되지 않나?
		void CreateCollider();
		Collider* GetCollider();

		void SetObjName(const char* _name);
		const char* GetObjName();

		void SetObjType(OBJECT_TYPE _type);
		OBJECT_TYPE GetObjType();

		void SetObjStatus(Status _type);
		Status GetObjStatus();

		virtual void OnCollision(Collider* src);//현재 충돌중
		virtual void OnCollisionEnter(Collider* src);//방금 충돌
		virtual void OnCollisionExit(Collider* src);//방금 충돌X

		virtual void FixedUpdate() = 0;
		virtual void Update() = 0;
		virtual void FinalUpdate() final;
		virtual void ComponentRender(HDC& _dc) final;
		virtual void Render(HDC& _dc) = 0;
	};
}
