#include "DieUI.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "DieUI.h"

DieUI::DieUI(gameMath::Vector3 pos):survivalTime(1)
{
	SetObjName("DieMotion");
	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("DieMotion", "\\Texture\\Cats\\\Die\\Die.bmp");

	transform._position = pos;
	transform._scale._x = texture[0]->Width();
	transform._scale._y = texture[0]->Height();

}

DieUI::~DieUI()
{
}

void DieUI::FixedUpdate()
{
	survivalTime -= (float)(FixedUpdateTime);
	if (survivalTime < 0)
	{
		_status = game::Destroy;
		return;
	}
	gameMath::Vector3 pos = transform.GetPosition();
	pos._y -= (float)(10 * (float)(FixedUpdateTime));

	transform.SetPosition(pos);
}

void DieUI::Update()
{
}

void DieUI::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(255, 174, 201));
}
