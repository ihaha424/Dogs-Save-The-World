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

	//텍스쳐는 오로지 recourceManage에서만 관리 가능하도록
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


		//텍스쳐는 오로지 recourceManage에서만 관리 가능하도록
		friend class ResourceManager;
	};
}

