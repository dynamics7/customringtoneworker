/* 
	Custom Ringtone Worker
	(C) ultrashot 2012-2013
*/
#include "stdafx.h"
#include "regext.h"
#include "..\..\common\Tasks.hpp"

static HREGNOTIFY hNotify = NULL;
static HREGNOTIFY hNotify2 = NULL;
static wchar_t previousSong[800] = {0};

void FixGetMoreSetting()
{
	HKEY hKey = NULL;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"ControlPanel\\Sounds\\CustomRingtones", 0, KEY_ALL_ACCESS, &hKey) == S_OK)
	{
		wchar_t str[500];
		DWORD cbSize = 500;
		DWORD dwType = REG_MUI_SZ;
		if (RegQueryValueEx(hKey, L"CustomRingtone-PlaceHolder.mp3", 0, &dwType, (LPBYTE)str, &cbSize) != S_OK)
		{
			wchar_t *validPath = L"EventSndRes.dll,#117";
			RegSetValueEx(hKey, L"CustomRingtone-PlaceHolder.mp3", 0, REG_MUI_SZ, (LPBYTE)validPath, (wcslen(validPath) + 1) * sizeof(wchar_t));
		}
		RegCloseKey(hKey);
	}
	if (GetFileAttributes(L"\\My Documents\\Ringtones\\CustomRingtone-PlaceHolder.mp3") == INVALID_FILE_ATTRIBUTES)
	{
		CopyFileW(L"\\Windows\\CustomRingtone-PlaceHolder.mp3", L"\\My Documents\\Ringtones\\CustomRingtone-PlaceHolder.mp3", FALSE);
	}
}

void Ringtone0Callback(HREGNOTIFY hNotify, DWORD dwUserData, PBYTE pData, UINT cbData)
{
	DWORD *data = (DWORD*)pData;
	DWORD dwData = *data;
	
	wchar_t sound[800] = {0};
	if (RegistryGetString(HKEY_CURRENT_USER, L"ControlPanel\\Sounds\\RingTone0", L"Sound", sound, 800) == S_OK)
	{
		if (wcsicmp(sound, L"\\My Documents\\Ringtones\\CustomRingtone-Placeholder.mp3") == 0)
		{
			wchar_t temp[1000];
			wcscpy(temp, L"app://9cefc0bf-7060-45b0-ba66-2d1dcad8dc3c/_default?fromsettings=");
			wcscat(temp, previousSong);
			Shell::Tasks::StartSession(temp, true);
		}
		wcscpy(previousSong, sound);
	}
}

void CustomRingtoneEntryCallback(HREGNOTIFY hNotify, DWORD dwUserData, PBYTE pData, UINT cbData)
{
	FixGetMoreSetting();
}

int _tmain(int argc, _TCHAR* argv[])
{
	FixGetMoreSetting();
	RegistryGetString(HKEY_CURRENT_USER, L"ControlPanel\\Sounds\\RingTone0", L"Sound", previousSong, 800);

	RegistryNotifyCallback(HKEY_CURRENT_USER, L"ControlPanel\\Sounds\\RingTone0", L"Sound", Ringtone0Callback, 0, NULL, &hNotify);
	RegistryNotifyCallback(HKEY_CURRENT_USER,  L"ControlPanel\\Sounds\\CustomRingtones", L"CustomRingtone-PlaceHolder.mp3", CustomRingtoneEntryCallback, 0, NULL, &hNotify2);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

