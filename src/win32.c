#include <windows.h>

// https://learn.microsoft.com/en-us/windows/win32/dxtecharts/disabling-shortcut-keys-in-games

STICKYKEYS g_StartupStickyKeys = { sizeof(STICKYKEYS), 0 };
TOGGLEKEYS g_StartupToggleKeys = { sizeof(TOGGLEKEYS), 0 };
FILTERKEYS g_StartupFilterKeys = { sizeof(FILTERKEYS), 0 };

void win32c_changeKeyExtra(char bAllowKeys) {
    if (bAllowKeys) {
        STICKYKEYS sk = g_StartupStickyKeys;
        TOGGLEKEYS tk = g_StartupToggleKeys;
        FILTERKEYS fk = g_StartupFilterKeys;

        SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &g_StartupStickyKeys, 0);
        SystemParametersInfo(SPI_SETTOGGLEKEYS, sizeof(TOGGLEKEYS), &g_StartupToggleKeys, 0);
        SystemParametersInfo(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &g_StartupFilterKeys, 0);
    }
    else {
        STICKYKEYS skOff = g_StartupStickyKeys;
        if ((skOff.dwFlags & SKF_STICKYKEYSON) == 0) {
            skOff.dwFlags &= ~SKF_HOTKEYACTIVE;
            skOff.dwFlags &= ~SKF_CONFIRMHOTKEY;

            SystemParametersInfo(SPI_SETSTICKYKEYS, sizeof(STICKYKEYS), &skOff, 0);
        }

        TOGGLEKEYS tkOff = g_StartupToggleKeys;
        if ((tkOff.dwFlags & TKF_TOGGLEKEYSON) == 0) {
            tkOff.dwFlags &= ~TKF_HOTKEYACTIVE;
            tkOff.dwFlags &= ~TKF_CONFIRMHOTKEY;

            SystemParametersInfo(SPI_SETTOGGLEKEYS, sizeof(TOGGLEKEYS), &tkOff, 0);
        }
        
        FILTERKEYS fkOff = g_StartupFilterKeys;
        if ((fkOff.dwFlags & FKF_FILTERKEYSON) == 0) {
            fkOff.dwFlags &= ~FKF_HOTKEYACTIVE;
            fkOff.dwFlags &= ~FKF_CONFIRMHOTKEY;

            SystemParametersInfo(SPI_SETFILTERKEYS, sizeof(FILTERKEYS), &fkOff, 0);
        }
    }
}

void win32c_init() {
    SystemParametersInfo(SPI_GETSTICKYKEYS, sizeof(STICKYKEYS), &g_StartupStickyKeys, 0);
    SystemParametersInfo(SPI_GETTOGGLEKEYS, sizeof(TOGGLEKEYS), &g_StartupToggleKeys, 0);
    SystemParametersInfo(SPI_GETFILTERKEYS, sizeof(FILTERKEYS), &g_StartupFilterKeys, 0);

    win32c_changeKeyExtra(0);
}