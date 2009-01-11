// keyboarddll.cpp : Defines the entry point for the DLL application.
//

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#include <windows.h>
#include <math.h>
#include <atlstr.h>
#include "keyboarddll.h"

KEYBOARDDLL_API int SendString(const HWND hwnd, const RECT rect, const CString s, const bool use_comma,
							   const HWND restore_focus, const POINT restore_cursor)
{
	INPUT			input[102];

	POINT pt = RandomizeClickLocation(rect);
	double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1;
	double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1;

	// Translate click point to screen/mouse coords
	ClientToScreen(hwnd, &pt);
	double fx = pt.x*(65535.0f/fScreenWidth);
	double fy = pt.y*(65535.0f/fScreenHeight);

	// Set up the input structure

	int input_count=0;

	// First click in the rect to select it, if rect is not passed in as {-1, -1, -1, -1}
	if (rect.left!=-1 || rect.top!=-1 || rect.right!=-1 || rect.bottom!=-1)
	{
		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_MOUSE;
		input[input_count].mi.dx = (LONG) fx;
		input[input_count].mi.dy = (LONG) fy;
		input[input_count].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN;
		input_count++;
		
		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_MOUSE;
		input[input_count].mi.dx = (LONG) fx;
		input[input_count].mi.dy = (LONG) fy;
		input[input_count].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
		input_count++;
	}

	// Add each character of the string to the input struct
	char ch_str[100];
	sprintf_s(ch_str, 100, "%s", s.GetString());

	int	vkey = 0;

	for (int i=0; i<(int) strlen(ch_str); i++)
	{
		if (ch_str[i]=='.')
		{
			if (use_comma)
			{
				vkey = VK_OEM_COMMA;
			}
			else
			{
				vkey = VK_DECIMAL;
			}
		}
		else
		{
			vkey = MapVirtualKey(ch_str[i], 1);
		}

		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_KEYBOARD;
		input[input_count].ki.wVk = vkey;
		input_count++;

		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_KEYBOARD;
		input[input_count].ki.wVk = vkey;
		input[input_count].ki.dwFlags = KEYEVENTF_KEYUP;
		input_count++;
	}

	// Set focus to target window
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);

	// Send input
	SendInput(input_count, input, sizeof(INPUT));

	// Restore previous window state and cursor position
	if (restore_focus!=NULL)
	{
		SetActiveWindow(restore_focus);
		SetForegroundWindow(restore_focus);
		SetFocus(restore_focus);
	}

	if (restore_cursor.x!=-1 && restore_cursor.y!=-1)
	{
		SetCursorPos(restore_cursor.x, restore_cursor.y);
	}

	return (int) true;
}

KEYBOARDDLL_API int SendKey(const HWND hwnd, const RECT rect, UINT vkey,
							const HWND restore_focus, const POINT restore_cursor)
{
	INPUT			input[4];

	POINT pt = RandomizeClickLocation(rect);
	double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1;
	double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1;

	// Translate click point to screen/mouse coords
	ClientToScreen(hwnd, &pt);
	double fx = pt.x*(65535.0f/fScreenWidth);
	double fy = pt.y*(65535.0f/fScreenHeight);

	// Set up the input structure
	int input_count=0;

	// First click in the rect to select it, if rect is not passed in as {-1, -1, -1, -1}
	if (rect.left!=-1 || rect.top!=-1 || rect.right!=-1 || rect.bottom!=-1)
	{
		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_MOUSE;
		input[input_count].mi.dx = (LONG) fx;
		input[input_count].mi.dy = (LONG) fy;
		input[input_count].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTDOWN;
		input_count++;
		
		ZeroMemory(&input[input_count],sizeof(INPUT));
		input[input_count].type = INPUT_MOUSE;
		input[input_count].mi.dx = (LONG) fx;
		input[input_count].mi.dy = (LONG) fy;
		input[input_count].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE | MOUSEEVENTF_LEFTUP;
		input_count++;
	}

	// Add vkey to the input struct
	ZeroMemory(&input[input_count],sizeof(INPUT));
	input[input_count].type = INPUT_KEYBOARD;
	input[input_count].ki.wVk = vkey;
	input_count++;

	ZeroMemory(&input[input_count],sizeof(INPUT));
	input[input_count].type = INPUT_KEYBOARD;
	input[input_count].ki.wVk = vkey;
	input[input_count].ki.dwFlags = KEYEVENTF_KEYUP;
	input_count++;

	// Set focus to target window
	SetFocus(hwnd);
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);

	// Send input
	SendInput(input_count, input, sizeof(INPUT));

	// Restore previous window state and cursor position
	if (restore_focus!=NULL)
	{
		SetActiveWindow(restore_focus);
		SetForegroundWindow(restore_focus);
		SetFocus(restore_focus);
	}

	if (restore_cursor.x!=-1 && restore_cursor.y!=-1)
	{
		SetCursorPos(restore_cursor.x, restore_cursor.y);
	}

	return (int) true;
}

KEYBOARDDLL_API void ProcessMessage(const char *message, const void *param)
{
	if (message==NULL)  return;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return true;
}

const POINT RandomizeClickLocation(const RECT rect) 
{
	POINT p = {0};

	// uniform random distribution, yuck!
	//p.x = ((double) rand() / (double) RAND_MAX) * (rect.right-rect.left) + rect.left;
	//p.y = ((double) rand() / (double) RAND_MAX) * (rect.bottom-rect.top) + rect.top;

	// normal random distribution - much better!
	GetClickPoint(rect.left + (rect.right-rect.left)/2, 
				  rect.top + (rect.bottom-rect.top)/2, 
				  (rect.right-rect.left)/2, 
				  (rect.bottom-rect.top)/2, 
				  &p);

	return p;
}

const void GetClickPoint(const int x, const int y, const int rx, const int ry, POINT *p) 
{
	p->x = x + (int) (RandomNormalScaled(2*rx, 0, 1) + 0.5) - (rx);
	p->y = y + (int) (RandomNormalScaled(2*ry, 0, 1) + 0.5) - (ry);
}

// random number - 0 -> scale, with normal distribution
// ignore results outside 3.5 stds from the mean
const double RandomNormalScaled(const double scale, const double m, const double s) 
{
	double res = -99;
	while (res < -3.5 || res > 3.5) res = RandomNormal(m, s);
	return (res / 3.5*s + 1) * (scale / 2.0);
}

const double RandomNormal(const double m, const double s) 
{
	/* mean m, standard deviation s */
	double x1 = 0., x2 = 0., w = 0., y1 = 0., y2 = 0.;

	do {
		x1 = 2.0 * ((double) rand()/(double) RAND_MAX) - 1.0;
		x2 = 2.0 * ((double) rand()/(double) RAND_MAX) - 1.0;
		w = x1 * x1 + x2 * x2;
	} while ( w >= 1.0 );

	w = sqrt( (-2.0 * log( w ) ) / w );
	y1 = x1 * w;
	y2 = x2 * w;

	return( m + y1 * s );
}