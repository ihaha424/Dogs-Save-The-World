#pragma once
#include <Windows.h>


// Foreground
#define FG_BLACK		0
//FG_BLACK ������ ����

#define FG_RED			FOREGROUND_RED|FOREGROUND_INTENSITY
#define FG_GREEN		FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define FG_BLUE			FOREGROUND_BLUE|FOREGROUND_INTENSITY

#define FG_RED_DARK		FOREGROUND_RED
#define FG_GREEN_DARK	FOREGROUND_GREEN 
#define FG_BLUE_DARK	FOREGROUND_BLUE

#define FG_YELLOW		FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY
#define FG_SKY			FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY
#define FG_PINK			FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY

#define FG_YELLOW_DARK	FOREGROUND_RED|FOREGROUND_GREEN
#define FG_SKY_DARK		FOREGROUND_GREEN|FOREGROUND_BLUE
#define FG_PINK_DARK	FOREGROUND_RED|FOREGROUND_BLUE

#define FG_GRAY			FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE
#define FG_WHITE		FG_GRAY|FOREGROUND_INTENSITY

// Background
#define BG_BLACK		0
//FG_BLACK ������ ����

#define BG_RED			BACKGROUND_RED|BACKGROUND_INTENSITY
#define BG_GREEN		BACKGROUND_GREEN|BACKGROUND_INTENSITY
#define BG_BLUE			BACKGROUND_BLUE|BACKGROUND_INTENSITY

#define BG_RED_DARK		BACKGROUND_RED
#define BG_GREEN_DARK	BACKGROUND_GREEN
#define BG_BLUE_DARK	BACKGROUND_BLUE

#define BG_YELLOW		BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY
#define BG_SKY			BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY
#define BG_PINK			BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_INTENSITY

#define BG_YELLOW_DARK	BACKGROUND_RED|BACKGROUND_GREEN
#define BG_SKY_DARK		BACKGROUND_GREEN|BACKGROUND_BLUE
#define BG_PINK_DARK	BACKGROUND_RED|BACKGROUND_BLUE

#define BG_GRAY			BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE
#define BG_WHITE		BG_GRAY|BACKGROUND_INTENSITY

namespace game
{
	class GameRender
	{
	private:
		HWND hWnd;

		HDC frontMemDC;    // �ո� DC
		HDC backMemDC;    // �޸� DC

		HBITMAP backBitmap = nullptr;


		HANDLE	hConsoleHandle;
		HANDLE	hScreenBuffer[2];
		int		nScreenWidth = 0;
		int		nScreenHeight = 0;
		int		nScreenBufferSize = 0;
		int		nScreenBufferIndex = 0;

		static GameRender* instance;
	public:
	private:
		GameRender();
		~GameRender();
	public:
		static GameRender* GetInstance();
		static void DestroyInstance();


		HDC& GetHDC();

		void InitRender();

		void ClearScreen();

		void BeginDraw();

		void EndDraw();

		void ReleaseRender();

		void DrawLine(int x1, int y1, int x2, int y2, COLORREF color);

		void DrawRect(int x, int y, int width, int height, COLORREF color);

		void DrawRectLine(int x, int y, int width, int height, COLORREF color);

		void DrawCircle(int x, int y, int radius, COLORREF color);

		void DrawPolygon(POINT points[], int count, COLORREF color);

		void DrawText(int x, int y, const char* text, COLORREF color);
		void DrawText(int x, int y, const char* text, COLORREF color, const wchar_t* fontName, int fontSize);
		void DrawFont(int x, int y, const char* text, COLORREF color, int fontSize, const wchar_t* fontName, int fontStyle);
	};
}
