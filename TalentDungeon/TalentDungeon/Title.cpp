#include "Title.h"
#include "ResourceManager.h"
#include "Texture.h"


Title::Title()
{
	SetObjName("Title");
	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("Title", "\\Texture\\UI\\Title.bmp");
	transform._position._x = ScreenWidth / 30 *6 - 50;
	transform._position._y = ScreenHeight / 7 * 3 + 50;
	transform._scale._x = texture[0]->Width();
	transform._scale._y = texture[0]->Height();
}

Title::~Title()
{
}

void Title::FixedUpdate()
{
}

void Title::Update()
{
}

void Title::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(255, 255, 255));
}
