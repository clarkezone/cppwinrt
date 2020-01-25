#pragma once

#include <dwmapi.h>
#include <unknwn.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Composition.Desktop.h>
#include <winrt/Windows.Graphics.h>
#include <windows.ui.composition.interop.h>
#include <ShellScalingAPI.h>
#include <DispatcherQueue.h>

#define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
#define FAILED(hr)      (((HRESULT)(hr)) < 0)

#define DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1 19

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

//#include "Generated Files/winrt/Microsoft.Graphics.Canvas.h"
//#include "Generated Files/winrt/Microsoft.Graphics.Canvas.Geometry.h"
//#include "Generated Files/winrt/Microsoft.Graphics.Canvas.Effects.h"
