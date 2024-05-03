#include "Texture.h"
#include <cassert>
#include "Transform.h"
#include "GameRender.h"
#include "Define.h"

namespace game
{
	Texture::Texture() : dc(NULL), hBit(NULL), bitInfo{} {}
	Texture::~Texture()
	{
		DeleteDC(dc);
		DeleteObject(hBit);
	}

	void Texture::Load(const char* _FilePath)
	{
		//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagea
		//WIn 제공 함수 관련 내용
		// LPCTSTR = const char *
		hBit = (HBITMAP)LoadImageA(nullptr, _FilePath, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		assert(hBit);

		dc = CreateCompatibleDC(GameRender::GetInstance()->GetHDC());

		//??
		HBITMAP preBit = (HBITMAP)SelectObject(dc, hBit);
		DeleteObject(preBit);

		//비트맵 정보
		GetObject(hBit, sizeof(BITMAP), &bitInfo);

	}
	UINT Texture::Width()
	{
		return bitInfo.bmWidth;
	}
	UINT Texture::Height()
	{
		return bitInfo.bmHeight;
	}
	HDC Texture::GetDC()
	{
		return dc;
	}

	void Texture::RenderTexture(HDC& _dc, gameMath::Transform& transform, UINT excep)
	{

		int texWid = (int)Width();
		int texHei = (int)Height();

		//game::GameRender::GetInstance

		gameMath::Vector3 pos = transform.GetPosition() + transform.GetRotationVector(transform.GetOffsetPosition());
		//DC를 DC에 찎기
		//BitBlt(_dc
		//	, (int)pos._x - (int)((float)texWid / 2)
		//	, (int)pos._y - (int)((float)texHei / 2)
		//	, texWid * transform._scale._y, texHei * transform._scale._y
		//	, GetDC()
		//	, 0, 0, SRCCOPY);

		//DC를 특정색을 제외하고 찍기
		TransparentBlt(_dc
			, pos._x - (float)(texWid / 2)
			, pos._y - (float)(texHei / 2)
			, texWid, texHei
			, GetDC()
			, 0, 0, texWid, texHei
			, excep);

		//POINT apt[3];
		//apt[0].x = pos._x - (float)(texWid / 2);
		//apt[0].y = pos._y - (float)(texHei / 2);
		//apt[1].x = pos._x + (float)(texWid / 2);
		//apt[1].y = pos._y - (float)(texHei / 2);
		//apt[2].x = pos._x - (float)(texWid / 2);
		//apt[2].y = pos._y + (float)(texHei / 2);
		//apt[0].x = apt[0].x * cos(transform._rotation._z * (PI / 180.0)) - apt[0].y * sin(transform._rotation._z * (PI / 180.0));
		//apt[0].y = apt[0].x * sin(transform._rotation._z * (PI / 180.0)) + apt[0].y * cos(transform._rotation._z * (PI / 180.0));

		//apt[1].x = apt[1].x * cos(transform._rotation._z * (PI / 180.0)) - apt[1].y * sin(transform._rotation._z * (PI / 180.0));
		//apt[1].y = apt[1].x * sin(transform._rotation._z * (PI / 180.0)) + apt[1].y * cos(transform._rotation._z * (PI / 180.0));

		//apt[2].x = apt[2].x * cos(transform._rotation._z * (PI / 180.0)) - apt[2].y * sin(transform._rotation._z * (PI / 180.0));
		//apt[2].y = apt[2].x * sin(transform._rotation._z * (PI / 180.0)) + apt[2].y * cos(transform._rotation._z * (PI / 180.0));


		//PlgBlt(_dc
		//	, apt
		//	, GetDC()
		//	, 0, 0, texWid, texHei
		//	,hBit
		//	,0, 0); 
		// 이후 TransparenBLT로 한다?

	}

	void Texture::RenderAlphaTexture(HDC& _dc, gameMath::Transform& transform, UINT alpha, UINT excep)
	{
		
		HDC AlphaDc = CreateCompatibleDC(_dc);
		HBITMAP AlphaHBITMAP = CreateCompatibleBitmap(_dc, ScreenWidth, ScreenHeight);

		HBITMAP preBit = (HBITMAP)SelectObject(AlphaDc, AlphaHBITMAP);
		DeleteObject(preBit);

		int texWid = (int)Width();
		int texHei = (int)Height();

		//game::GameRender::GetInstance

		gameMath::Vector3 pos = transform.GetPosition() + transform.GetRotationVector(transform.GetOffsetPosition());
		

		BitBlt(AlphaDc
			, 0, 0
			, texWid * transform._scale._y, texHei * transform._scale._y
			, _dc
			, (int)pos._x - (int)((float)texWid / 2)
			, (int)pos._y - (int)((float)texHei / 2), SRCCOPY);
		
		TransparentBlt(AlphaDc
			, 0
			, 0
			, texWid, texHei
			, GetDC()
			, 0, 0, texWid, texHei
			, excep);


		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = alpha;
		bf.AlphaFormat = 0;
		AlphaBlend(_dc
			, pos._x - (float)(texWid / 2)
			, pos._y - (float)(texHei / 2)
			, texWid, texHei
			, AlphaDc
			, 0, 0, texWid, texHei
			, bf);

		DeleteDC(AlphaDc);
		DeleteObject(AlphaHBITMAP);
		

	}

}
