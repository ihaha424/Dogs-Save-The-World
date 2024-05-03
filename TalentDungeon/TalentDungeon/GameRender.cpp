#include "WinApp.h"
#include "GameRender.h"

#pragma comment(lib, "msimg32.lib")

namespace game
{
    GameRender* GameRender::instance = nullptr;

    GameRender::GameRender() : hConsoleHandle(0), hScreenBuffer{} {}

    GameRender::~GameRender() {}

    GameRender* GameRender::GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new GameRender();
        }
        return instance;
    }

    void GameRender::DestroyInstance()
    {
        if (instance != nullptr)
        {
            delete instance;
            instance = nullptr;
        }
    }

    HDC& GameRender::GetHDC()
    {
        return backMemDC;
    }

    void GameRender::InitRender()
    {
        hWnd = global::GetWinApp().GetWindow();

        frontMemDC = GetDC(hWnd);

        backMemDC = CreateCompatibleDC(frontMemDC);

        backBitmap = CreateCompatibleBitmap(frontMemDC, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight());
    }

    void GameRender::ClearScreen()
    {
        ::PatBlt(backMemDC, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), WHITENESS);
    }

    void GameRender::BeginDraw()
    {
        ClearScreen();

        ::SelectObject(backMemDC, backBitmap);
    }

    void GameRender::EndDraw()
    {
        ::BitBlt(frontMemDC, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), backMemDC, 0, 0, SRCCOPY);
    }

    void GameRender::ReleaseRender()
    {
        DeleteObject(backBitmap);

        DeleteDC(backMemDC);

        ReleaseDC(hWnd, frontMemDC);
    }

    void GameRender::DrawLine(int x1, int y1, int x2, int y2, COLORREF color)
    {
        HPEN hPen = CreatePen(PS_SOLID, 5, color);

        HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

        MoveToEx(backMemDC, x1, y1, NULL);

        LineTo(backMemDC, x2, y2);

        SelectObject(backMemDC, hOldPen);

        DeleteObject(hPen);
    }


    void GameRender::DrawRect(int x, int y, int width, int height, COLORREF color)
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, color);

        HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

        HBRUSH hBrush = CreateSolidBrush(color);

        HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

        Rectangle(backMemDC, x, y, x + width, y + height);

        SelectObject(backMemDC, hOldPen);
        SelectObject(backMemDC, hOldBrush);

        DeleteObject(hPen);
        DeleteObject(hBrush);
    }

    void GameRender::DrawRectLine(int x, int y, int width, int height, COLORREF color)
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, color);

        HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

        HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

        HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

        Rectangle(backMemDC, x, y, x + width, y + height);

        SelectObject(backMemDC, hOldPen);
        SelectObject(backMemDC, hOldBrush);

        DeleteObject(hPen);
        DeleteObject(hBrush);
    }


    void GameRender::DrawCircle(int x, int y, int radius, COLORREF color)
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, color);

        HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

        HBRUSH hBrush = CreateSolidBrush(color);

        HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

        Ellipse(backMemDC, x - radius, y - radius, x + radius, y + radius);

        SelectObject(backMemDC, hOldPen);
        SelectObject(backMemDC, hOldBrush);

        DeleteObject(hPen);
        DeleteObject(hBrush);

    }

    void GameRender::DrawPolygon(POINT points[], int count, COLORREF color)
    {
        HPEN hPen = CreatePen(PS_SOLID, 1, color);

        HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

        HBRUSH hBrush = CreateSolidBrush(color);

        HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

        Polygon(backMemDC, points, count);

        SelectObject(backMemDC, hOldPen);
        SelectObject(backMemDC, hOldBrush);

        DeleteObject(hPen);
        DeleteObject(hBrush);

    }

    void GameRender::DrawText(int x, int y, const char* text, COLORREF color)
    {
        SetTextColor(backMemDC, color);

        TextOutA(backMemDC, x, y, text, strlen(text));
    }

    void GameRender::DrawText(int x, int y,
        const char* text, COLORREF color,
        const wchar_t* fontName, int fontSize)
    {
        HFONT hFont = CreateFontW(fontSize, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, fontName);

        HFONT hOldFont = (HFONT)SelectObject(backMemDC, hFont);
        SetTextColor(backMemDC, color);
        SetBkMode(backMemDC, TRANSPARENT);//배경색 투영하기.
        TextOutA(backMemDC, x, y, text, strlen(text));
        SelectObject(backMemDC, hFont);
        DeleteObject(hFont);
    }

}