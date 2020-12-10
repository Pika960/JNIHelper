@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

echo Buildsystem for JNIHelper - Windows
echo (c) 2020 Gabriel Daenner
echo.

if /i [%1]==[--use-gcc]  set PREFERRED_COMPILER=GCC
if /i [%1]==[--use-msvc] set PREFERRED_COMPILER=MSVC

if not exist ..\bin (
    echo Error: No build directory found.
    echo Closing application ...
    echo.
    pause
    exit /b
)

if exist ..\src (
    cd ..\src
    
    if exist *.class (
        echo Cleaning up build ...
        del /s /q *.class JNIHelper.h *.obj > NUL
    ) else (echo Nothing to clean)
) else (
    echo Error: No src directory found.
    echo Closing application ...
    echo.
    pause
    exit /b
)

echo Checking environment ...
if not defined JAVA_HOME (
    if not exist %JAVA_HOME%\include (
        echo Error: The environment variable JAVA_HOME is required to build this application.
        echo Please install the JAVA SDK and set this variable to the path of the root folder.
        echo Closing application ...
        echo.
        pause
        exit /b
    )
)

echo Searching for javac in path ...
where /q javac.exe
if ERRORLEVEL 1 (
    echo Error: Javac seems to be missing. Ensure it is installed and placed in your PATH.
    echo Closing application ...
    echo.
    pause
    exit /b
)

if /i "%PREFERRED_COMPILER%"=="GCC"  (goto LOOKUP_GCC)
if /i "%PREFERRED_COMPILER%"=="MSVC" (goto LOOKUP_MSVC)

:LOOKUP_GCC
echo Searching for gcc in path ...
where /q gcc.exe
if ERRORLEVEL 1 (
    if /i "%PREFERRED_COMPILER%"=="GCC" (
        echo Error: GCC seems to be missing. Ensure it is installed and placed in your PATH.
        echo Closing application ...
        echo.
        pause
        exit /b
    ) else (
        echo INFO: GCC seems to be missing.
    )
) else (
    set  PREFERRED_COMPILER=GCC
    goto BUILD_DLL
)

:LOOKUP_MSVC
if exist "!ProgramFiles(x86)!\Microsoft Visual Studio\Installer\" (
    set "path=!path!;!ProgramFiles(x86)!\Microsoft Visual Studio\Installer\"
    echo Searching for Visual Studio native workload ...

    for /f "usebackq tokens=*" %%i in (`vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        set InstallDir=%%i
    )

    if exist "!InstallDir!\Common7\Tools\vsdevcmd.bat" (
        call "!InstallDir!\Common7\Tools\vsdevcmd.bat" -no_logo -arch=x64
        set PREFERRED_COMPILER=MSVC
    ) else (
        echo Error: The workload "Desktop development with C++" is not installed on this system.
        echo Closing application ...
        echo.
        pause
        exit /b
    )
) else (
    echo Error: Visual Studio Installer is not installed on this system.
    echo Closing application ...
    echo.
    pause
    exit /b
)

:BUILD_DLL
echo Compiling JNIHelper.java
javac .\java\JNIHelper.java
echo Generating resources
javac .\java\JNIHelper.java -h .\native

echo Creating JNI-DLL
if /i "%PREFERRED_COMPILER%"=="GCC" (
    g++ -fPIC -m64 -shared -Wall -Wl,--kill-at -O2 -o ..\bin\CLib.dll .\native\JNIHelper.cpp .\native\windows.cpp -I%JAVA_HOME%/include -I%JAVA_HOME%/include/win32
)

if /i "%PREFERRED_COMPILER%"=="MSVC" (
    cl -I%JAVA_HOME%/include -I%JAVA_HOME%/include/win32 -LD -MT -Fe..\bin\CLib.dll .\native\JNIHelper.cpp .\native\windows.cpp Advapi32.lib User32.lib
)

echo Cleaning up ...
del /s /q *.class JNIHelper.h *.obj > NUL
echo.

pause
