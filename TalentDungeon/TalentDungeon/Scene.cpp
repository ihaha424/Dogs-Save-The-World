#include "Scene.h"
#include "Object.h"

namespace game
{
	Scene::Scene() {}
	Scene::~Scene()
	{
		for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		{
			for (UINT j = 0; j < objArr[i].Size(); j++)
			{
				delete objArr[i][j];
			}
		}
	}
	void Scene::SetName(const char* _Name)
	{
		name = _Name;
	}
	const char* Scene::GetName()
	{
		return name;
	}
	void Scene::FixedUpdate()
	{
		for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		{
			for (UINT j = 0; j < objArr[i].Size(); j++)
			{
				if (objArr[i][j]->_status == Active || objArr[i][j]->_status == UnVisible)
					objArr[i][j]->FixedUpdate();
			}
		}
	}
	void Scene::Update()
	{
		for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		{
			for (UINT j = 0; j < objArr[i].Size(); j++)
			{
				if (objArr[i][j]->_status == Active || objArr[i][j]->_status == UnVisible)
					objArr[i][j]->Update();
			}
		}
	}

	void Scene::DestoryUpdate()
	{
		for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		{
			for (UINT j = 0; j < objArr[i].Size(); j++)
			{
				if (objArr[i][j]->_status == Destroy)
				{
 					delete objArr[i][j];
					objArr[i].Erase(j);
					j--;
				}
			}
		}
	}

	void Scene::FinalUpdate()
	{

	}

	void Scene::Render(HDC& _dc)
	{
		for (UINT i = 0; i < (UINT)OBJECT_TYPE::END; i++)
		{
			for (UINT j = 0; j < objArr[i].Size(); j++)
			{
				if (objArr[i][j]->_status == Active)
					objArr[i][j]->Render(_dc);
			}
		}
	}
	void Scene::AddObject(Object* obj, OBJECT_TYPE type)
	{
		objArr[(int)type].PushBack(obj);
	}

	void Scene::EraseObject(OBJECT_TYPE type, UINT index)
	{
		Object* temp = objArr[(int)type][index];
      		objArr[(int)type].Erase(index);
		delete temp;
	}

	const CTN::Vector<Object*>& Scene::GetGroupObject(OBJECT_TYPE type)
	{
		
		return objArr[(UINT)type];
	}

	Object* Scene::GetObjectSrc(OBJECT_TYPE _type, const char* _name)
	{
		for (UINT j = 0; j < objArr[(UINT)_type].Size(); j++)
		{
			if (!strcmp(objArr[(UINT)_type][j]->objName, _name))
				return objArr[(UINT)_type][j];
		}
		return nullptr;
	}

}