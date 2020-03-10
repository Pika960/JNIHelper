@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

echo Buildsystem for JNIHelper - Windows
echo (c) 2020 Gabriel Daenner
echo.

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
        del *.class *.h
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

echo Searching for gcc in path ...
where /q gcc.exe
if ERRORLEVEL 1 (
    echo Error: GCC seems to be missing. Ensure it is installed and placed in your PATH.
    echo Closing application ...
    echo.
    pause
    exit /b
)

echo Compiling JNIHelper.java
javac JNIHelper.java
echo Generating resources
javac JNIHelper.java -h .

echo Creating JNI-DLL
g++ -Wall -D_JNI_IMPLEMENTATION_ -Wl,--kill-at  -I%JAVA_HOME%/include -I%JAVA_HOME%/include/win32  -shared -o ..\bin\CLib.dll JNIHelper.cpp -m64

echo Cleaning up ...
del *.h *.class
echo.

pause
