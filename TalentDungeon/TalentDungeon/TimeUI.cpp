#include "TimeUI.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "GameTime.h"


TimeUI::TimeUI():Time(0)
{
	SetObjName("TimeUI");
	textureSize = 11;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("Number0", "\\Texture\\Number\\Number0.bmp");
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("Number1", "\\Texture\\Number\\Number1.bmp");
	texture[2] = game::ResourceManager::GetInstance()->LoadTexture("Number2", "\\Texture\\Number\\Number2.bmp");
	texture[3] = game::ResourceManager::GetInstance()->LoadTexture("Number3", "\\Texture\\Number\\Number3.bmp");
	texture[4] = game::ResourceManager::GetInstance()->LoadTexture("Number4", "\\Texture\\Number\\Number4.bmp");
	texture[5] = game::ResourceManager::GetInstance()->LoadTexture("Number5", "\\Texture\\Number\\Number5.bmp");
	texture[6] = game::ResourceManager::GetInstance()->LoadTexture("Number6", "\\Texture\\Number\\Number6.bmp");
	texture[7] = game::ResourceManager::GetInstance()->LoadTexture("Number7", "\\Texture\\Number\\Number7.bmp");
	texture[8] = game::ResourceManager::GetInstance()->LoadTexture("Number8", "\\Texture\\Number\\Number8.bmp");
	texture[9] = game::ResourceManager::GetInstance()->LoadTexture("Number9", "\\Texture\\Number\\Number9.bmp");

	texture[10] = game::ResourceManager::GetInstance()->LoadTexture("TimeUI", "\\Texture\\UI\\TimeUI.bmp");

	transform._position._x = ScreenWidth / 2;
	transform._position._y = texture[10]->Height() / 2;
	transform._scale._x = texture[10]->Width();
	transform._scale._y = texture[10]->Height();


	for (int i = 0; i < 4; i++)
	{
		Number[i] = 0;
		NumberXPos[i] = transform;
		NumberXPos[i]._position._x += 65.0f * i;
		NumberXPos[i]._position._y -= 26.0f;
	}
}

TimeUI::~TimeUI()
{
}

void TimeUI::FixedUpdate()
{
	Time += FixedUpdateTime;
	
	Number[0] = (((int)Time / 60) / 10) % 10;
	Number[1] = ((int)Time / 60) % 10;
	Number[2] = ((int)Time % 60) / 10;
	Number[3] = ((int)Time % 60) % 10;
}

void TimeUI::Update()
{
}

void TimeUI::Render(HDC& _dc)
{
	texture[10]->RenderTexture(_dc, transform, RGB(255, 255, 255));
	for(int i = 0; i < 4; i++)
		texture[Number[i]]->RenderTexture(_dc, NumberXPos[i], RGB(255, 255, 255));
}
