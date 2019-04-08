// Copyright (c) 2015, Matthew Malensek.
// Distributed under the BSD 2-Clause License (see LICENSE.txt for details)

#pragma once

#include "OSD.h"

class BrightnessController;

class BrightnessOSD : public OSD {
public:
    BrightnessOSD();
    ~BrightnessOSD();

    void Hide();
    void HideIcon();

    virtual void ProcessHotkeys(HotkeyInfo &hki);

private:
    MeterWnd _mWnd;
    BrightnessController *_brightnessCtrl;

    virtual void OnDisplayChange();

    virtual LRESULT WndProc(HWND hWnd, UINT message,
        WPARAM wParam, LPARAM lParam);

	float _stepsize = 0.1f;
};