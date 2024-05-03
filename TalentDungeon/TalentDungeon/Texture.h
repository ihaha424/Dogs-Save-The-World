#pragma once
#include <Windows.h>
#include "Resource.h"

namespace gameMath
{
	class Transform;
}

namespace game
{
	class Texture : public Resource
	{
	private:
		HDC		dc;
		HBITMAP hBit;
		BITMAP	bitInfo;

	//�ؽ��Ĵ� ������ recourceManage������ ���� �����ϵ���
	private:
		Texture();
		~Texture();

	public:
		void Load(const char* _FilePath);
		UINT Width();
		UINT Height();

		HDC GetDC();

		void RenderTexture(HDC& _dc, gameMath::Transform& transform, UINT excep);
		void RenderAlphaTexture(HDC& _dc, gameMath::Transform& transform, UINT alpha, UINT excep);


		//�ؽ��Ĵ� ������ recourceManage������ ���� �����ϵ���
		friend class ResourceManager;
	};
}

