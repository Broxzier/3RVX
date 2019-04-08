// Copyright (c) 2015, Matthew Malensek.
// Distributed under the BSD 2-Clause License (see LICENSE.txt for details)

#include "BrightnessOSD.h"

#include "../Controllers/Brightness/BrightnessController.h"
#include "../Controllers/Brightness/DDCBrightnessController.h"
#include "../DisplayManager.h"
#include "../HotkeyInfo.h"
#include "../Skin/OSDComponent.h"
#include "../Skin/Skin.h"
#include "../Skin/SkinManager.h"

BrightnessOSD::BrightnessOSD() :
OSD(L"3RVX-BrightnessDispatcher"),
_mWnd(L"3RVX-BrightnessOSD", L"3RVX-BrightnessOSD") {

    SkinManager *skin = SkinManager::Instance();
    _mWnd.BackgroundImage(skin->BrightnessOSD()->background);
    _mWnd.EnableGlass(skin->BrightnessOSD()->mask);
    _mWnd.Update();

    OSD::InitMeterWnd(_mWnd);

    _brightnessCtrl = new DDCBrightnessController(
        DisplayManager::Primary().Handle());
}

BrightnessOSD::~BrightnessOSD() {
    delete _brightnessCtrl;
}

void BrightnessOSD::Hide() {
    _mWnd.Hide(false);
}

void BrightnessOSD::HideIcon() {

}

void BrightnessOSD::ProcessHotkeys(HotkeyInfo &hki) {
    switch (hki.action) {
	case HotkeyInfo::IncreaseBrightness: {
		float newval = _brightnessCtrl->Brightness() + _stepsize;
		if (newval > 1.0) break;
		_brightnessCtrl->Brightness(newval);
		}break;

    case HotkeyInfo::DecreaseBrightness: {
		float newval = _brightnessCtrl->Brightness() - _stepsize;
		if (newval < 0.0) break;
		_brightnessCtrl->Brightness(newval);
        }break;

    case HotkeyInfo::SetBrightness:

        break;
    }
}

void BrightnessOSD::OnDisplayChange() {
    InitMeterWnd(_mWnd);
}

LRESULT
BrightnessOSD::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    return OSD::WndProc(hWnd, message, wParam, lParam);
}

