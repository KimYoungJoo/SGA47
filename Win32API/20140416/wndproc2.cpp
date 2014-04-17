﻿#include "windefine.h"

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		::SetTimer(hWnd, 0, 1000, NULL);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::KillTimer(hWnd, 0);
		::PostQuitMessage(0);
		return 0;
	}
	else if (uMsg == WM_TIMER)
	{
		RECT rc;
		::GetClientRect(hWnd, &rc);
		::InvalidateRect(hWnd, &rc, TRUE);
		return 0;
	}
	else if (uMsg == WM_PAINT)
	{
		PAINTSTRUCT ps;
		// Handle Device Context
		HDC hdc = ::BeginPaint(hWnd, &ps);

		// GDI object
		// pen, brush, font, path, region, pallete
		RECT rc;
		::GetClientRect(hWnd, &rc);

		RECT box = {0,0,50,50};
		LONG width = box.right - box.left;
		LONG height = box.bottom - box.top;

		RECT rcDraw;

		for (int y = 0; y < rc.bottom - rc.top; y += height)
		{
			BYTE r = rand()%256;
			BYTE g = rand()%256;
			BYTE b = rand()%256;
			for (int x = 0; x < rc.right - rc.left; x += width)
			{
				rcDraw = box;
				::OffsetRect(&rcDraw, x, y);

				r = max(r - 10, 0);
				g = max(g - 10, 0);
				b = max(b - 10, 0);

				HBRUSH hRandBrush = ::CreateSolidBrush(RGB(r,g,b));

				::FillRect(hdc, &rcDraw, hRandBrush);
				::DeleteObject(hRandBrush);

			}
		}

		::EndPaint(hWnd, &ps);
		return 0;
	}

	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}
