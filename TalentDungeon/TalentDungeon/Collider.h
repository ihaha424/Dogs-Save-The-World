#pragma once
#include <Windows.h>
#include "Transform.h"

namespace game
{
	class Object;

	class Collider
	{
	private:
		static UINT staticID;

		Object*				myObject;
		gameMath::Transform finalTransform;
		UINT				collisionID;
		UINT				collisionCount;
		COLORREF			renderColor;
	private:
	public:
		Collider();
		Collider(const Collider& _src);
		~Collider();

		Collider& operator=(const Collider& _src) = delete;

		void SetOffsetPos(gameMath::Vector3 _offset);
		gameMath::Vector3 GetOffsetPos();

		void SetScale(gameMath::Vector3 _scale);
		gameMath::Vector3 GetSetScalePos();

		void SetFinalTransform(gameMath::Transform _transform);
		gameMath::Transform GetFinalTransformPos();

		UINT GetColliderID();
		Object* GetMyObject();

		void FinalUpdate();
		void Render(HDC& _dc);

		void OnCollision(Collider* src);//���� �浹��
		void OnCollisionEnter(Collider* src);//��� �浹
		void OnCollisionExit(Collider* src);//��� �浹X


		friend class Object;
	};

}
