#include "Object.h"
#include "Collider.h"
#include "ColliderManager.h"


namespace game
{
	Object::Object(const char* _objName, OBJECT_TYPE _objType)
		: objName(_objName), objType(_objType), texture(nullptr),
		textureSize(0), collider(nullptr), _status(Active) {}
	Object::~Object()
	{
		if (collider != nullptr)
			delete collider;
		if (texture != nullptr)
		{
			for (int i = 0; i < textureSize; i++)
			{
				texture[i];
			}
			delete texture;
		}
	}

	void Object::CreateCollider()
	{
		collider = new Collider;
		collider->myObject = this;
		game::ColliderManager::GetInstance()->AddColliderObject(this, objType);
	}

	Collider* Object::GetCollider()
	{
		return collider;
	}


	void Object::SetObjName(const char* _name)
	{
		objName = _name;
	}

	const char* Object::GetObjName()
	{
		return objName;
	}

	void Object::SetObjType(OBJECT_TYPE _type)
	{
		objType = _type;
	}

	OBJECT_TYPE Object::GetObjType()
	{
		return objType;
	}

	void Object::SetObjStatus(Status _type)
	{
		_status = _type;
	}

	Status Object::GetObjStatus()
	{
		return _status;
	}


	void Object::OnCollision(Collider* src) {}

	void Object::OnCollisionEnter(Collider* src) {}

	void Object::OnCollisionExit(Collider* src) {}

	void Object::FinalUpdate()
	{
		if (collider)
			collider->FinalUpdate();
	}
	void Object::ComponentRender(HDC& _dc)
	{
		if (collider != nullptr && DebugModeFlag)
		{
			collider->Render(_dc);
		}
	}
}

