# rick-roller
A program that when installed a rick roll video appears every 67 seconds. The rick-roller program wont harm your system and it is 100% safe.

# How to use
Run the `installer.exe` with admin previlages and the rick-rolling should start, if antivrus flags it as a threat, add an exception or temporarily disable the antivirus. **Run the uninstaller with admin previlages to successfully uninstall and clean the rick-roller.**

# Installations
Install the latest version in [releases](https://github.com/DiggaTrigga/rick-roller/releases). Unzip and run the .exe file inside!

**Building from source**
1. Install [C++](https://code.visualstudio.com/docs/languages/cpp)
2. Run powershell as administrator and change your directory folder to where the source files are located with this command: `cd "C:\Path\To\Your\Folder"`.
3. Run these commands one by one:\
`g++ service_logic.cpp -o SysUpdateHost.exe -mwindows`\
`windres resources.rc -O coff -o resources.res`\
`g++ main.cpp resources.res -o Installer.exe -static`

**Note: The commands are only availablt for MinGW-x64 C++ Compiler**

# How it works
Magic
