#include "window.hpp"
#include "raylib.h"
#include "iostream"
#include <math.h>
#include <algorithm>

int GetMaxWindowScale()
{
	int maxWidthScale = (int)floorf(GetMonitorWidth(GetCurrentMonitor()) / 120.0f);
	int maxHeightScale = (int)floorf(GetMonitorHeight(GetCurrentMonitor()) / 160.0f);
	return std::min(maxWidthScale, maxHeightScale);
}

void SetWindowPositionCenter()
{
	int monitorWindthHalf = (int)floorf(GetMonitorWidth(GetCurrentMonitor()) / 2.0f);
	int monitorHeightHalf = (int)floorf(GetMonitorHeight(GetCurrentMonitor()) / 2.0f);
	int screenWidthHalf = GetScreenWidth() / 2;
	int screenHeightHalf = GetScreenHeight() / 2;
	SetWindowPosition(monitorWindthHalf - screenWidthHalf,monitorHeightHalf - screenHeightHalf);
}
