#include "Collider.h"
#include "Object.h"
#include "GameRender.h"

namespace game
{
	UINT Collider::staticID = 0;

	Collider::Collider(): myObject(nullptr), collisionID(staticID++), collisionCount(0), renderColor(RGB(255,0,0)){}
	Collider::~Collider() {}
	Collider::Collider(const Collider& _src)
		: myObject(nullptr)
		, finalTransform(_src.finalTransform)
		, collisionID(staticID++)
		, collisionCount(0)
		, renderColor(RGB(255, 0, 0))
	{}

	void Collider::SetOffsetPos(gameMath::Vector3 _offset)
	{
		finalTransform._offsetPosition = _offset;
	}

	gameMath::Vector3 Collider::GetOffsetPos()
	{
		return finalTransform._offsetPosition;
	}

	void Collider::SetScale(gameMath::Vector3 _scale)
	{
		finalTransform.SetScale(_scale);
	}

	gameMath::Vector3 Collider::GetSetScalePos()
	{
		return finalTransform.GetScale();
	}

	Object* Collider::GetMyObject()
	{
		return myObject;
	}

	void Collider::SetFinalTransform(gameMath::Transform _transform)
	{
		finalTransform = _transform;
	}

	gameMath::Transform Collider::GetFinalTransformPos()
	{
		return finalTransform;
	}


	void Collider::FinalUpdate()
	{
		//object의 위치를 따라간다.
		finalTransform._position = myObject->transform._position;
		finalTransform._rotation = myObject->transform._rotation;
		finalTransform._position = finalTransform._position + finalTransform._offsetPosition;

		assert(collisionCount >= 0);
	}

	void Collider::Render(HDC& _dc)
	{
		game::GameRender::GetInstance()->DrawRectLine(
			(int)(finalTransform._position._x - finalTransform._scale._x / 2.f)
			, (int)(finalTransform._position._y - finalTransform._scale._y / 2.f)
			, finalTransform._scale._x, finalTransform._scale._y, renderColor);
	}
	
	UINT Collider::GetColliderID()
	{
		return collisionID;
	}

	void Collider::OnCollision(Collider* src)
	{
		renderColor = RGB(0, 0, 255);
		myObject->OnCollision(src);
	}
	void Collider::OnCollisionEnter(Collider* src)
	{
		collisionCount++;
		renderColor = RGB(0, 255, 0);
		myObject->OnCollisionEnter(src);

	}
	void Collider::OnCollisionExit(Collider* src)
	{
		collisionCount--;
		renderColor = RGB(255, 0, 0);
		myObject->OnCollisionExit(src);

	}
}