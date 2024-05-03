#include "ColliderManager.h"
#include "Collider.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Vector.hpp"
#include "Object.h"
#include <iostream>

namespace game
{
	ColliderManager* ColliderManager::instance = nullptr;
	ColliderManager::ColliderManager() : checkArr{} {}
	ColliderManager::~ColliderManager() {}

	void ColliderManager::CollisionCheck(OBJECT_TYPE lhs, OBJECT_TYPE rhs)
	{
		Scene* curScene = SceneManager::GetInstance()->GetCurScene();
		
		const CTN::Vector<Object*>& LGourp = colliderArr[(UINT)lhs];
		const CTN::Vector<Object*>& RGourp = colliderArr[(UINT)rhs];


		bool PrevCollision;
		for (UINT i = 0; i  < LGourp.Size(); i++)
		{
			if (LGourp[i]->GetCollider() == nullptr 
				|| (LGourp[i]->_status != Active 
				&& LGourp[i]->_status != UnVisible))
				continue;
			int num = RGourp.Size();
			for (UINT j = 0; j < RGourp.Size(); j++)
			{
				if (RGourp[j]->GetCollider() == nullptr 
					|| LGourp[i] == RGourp[j]
					|| (RGourp[j]->_status != Active
					&& RGourp[j]->_status != UnVisible))
					continue;

				Collider* LCollider = LGourp[i]->GetCollider();
				Collider* RCollider = RGourp[j]->GetCollider();

				//두 충돌체의 고유한 키값
				ColliderID ID;
				ID.LeftID = LCollider->GetColliderID();
				ID.RightID = RCollider->GetColliderID();

				if (!collisionInfo.Find(ID.ID))
				{
					collisionInfo.Put(ID.ID, false);
				}

				PrevCollision = collisionInfo.Get(ID.ID);
				//현재 충돌 중
				if (IsCollision(LCollider, RCollider))
				{
					//이전에도 충돌중이고 지금도 충돌중
					if (PrevCollision)
					{
						LCollider->OnCollision(RCollider);
						RCollider->OnCollision(LCollider);
					}
					else //이전에는 충돌하지 않았지만 지금은 충돌중 -> 방금 만남
					{
						LCollider->OnCollisionEnter(RCollider);
						RCollider->OnCollisionEnter(LCollider);
						collisionInfo.Put(ID.ID, true);
					}
				}
				else
				{
					//이전에도 충돌중이지만 지금 충돌X
					if (PrevCollision)
					{
						LCollider->OnCollisionExit(RCollider);
						RCollider->OnCollisionExit(LCollider);
						collisionInfo.Put(ID.ID, false);
					}
				}
			}
		}
	}

	bool ColliderManager::IsCollision(Collider* lhs, Collider* rhs)
	{
		gameMath::Transform LTranform = lhs->GetFinalTransformPos();
		gameMath::Transform RTranform = rhs->GetFinalTransformPos();

		bool A2 = (LTranform._position._y + LTranform._scale._y / 2.f) < (RTranform._position._y - RTranform._scale._y / 2.f);
		bool A1 = (LTranform._position._y - LTranform._scale._y / 2.f) > (RTranform._position._y + RTranform._scale._y / 2.f);
		bool B1 = (LTranform._position._x + LTranform._scale._x / 2.f) < (RTranform._position._x - RTranform._scale._x / 2.f);
		bool B2 = (LTranform._position._x - LTranform._scale._x / 2.f) > (RTranform._position._x + RTranform._scale._x / 2.f);
		if (A1 || A2 || B1 || B2)
			return false;
		return true;
	}

	ColliderManager* ColliderManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ColliderManager();
		}
		return instance;
	}

	void ColliderManager::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void ColliderManager::Initialize()
	{

	}

	void ColliderManager::Update()
	{
		for (UINT row = 0; row < (UINT)OBJECT_TYPE::END; row++)
		{
			for (UINT col = row; col < (UINT)OBJECT_TYPE::END; col++)
			{
				if (checkArr[row] & (1 << col))
				{
					//작은 숫자의 그룹이 왼쪽으로
					CollisionCheck((OBJECT_TYPE)row, (OBJECT_TYPE)col);
				}
			}
		}
	}

	void ColliderManager::AddColliderObject(Object* obj, OBJECT_TYPE type)
	{
		colliderArr[(int)type].PushBack(obj);
	}


	void ColliderManager::CheckGourp(OBJECT_TYPE lhs, OBJECT_TYPE rhs)
	{
		UINT row = (UINT)lhs;
		UINT col = (UINT)rhs;

		if (col < row)
		{
			row = (UINT)rhs;
			col = (UINT)lhs;
		}

		if (checkArr[row] & (1 << col))//있으면
		{
			//뺴기
			checkArr[row] &= ~(1 << col);
		}
		else
		{
			//채우기
			checkArr[row] |= (1 << col);
		}
	}

	void ColliderManager::ResetGourp()
	{
		memset(checkArr, 0, sizeof(UINT) * (UINT)OBJECT_TYPE::END);
	}

	void ColliderManager::FinalUpdate()
	{
		//	조작같은 것이 아니라 엔진차원에서 당연하게 진행되어야 하는 것들
		//	ex> 충돌체가 오브젝트를 따라 가는 것.
		for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		{
			for (UINT j = 0; j < colliderArr[i].Size(); j++)
			{
				if (colliderArr[i][j]->_status == Active || colliderArr[i][j]->_status == UnVisible)
					colliderArr[i][j]->FinalUpdate();
			}
		}
	}

	void ColliderManager::DestoryUpdate()
	{
		for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		{
			for (UINT j = 0; j < colliderArr[i].Size(); j++)
			{
				if (colliderArr[i][j]->_status == Destroy)
				{
					colliderArr[i].Erase(j);
					j--;
				}
			}
		}
	}
}