@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

echo Buildsystem for JNIHelper - Windows
echo (c) 2020 Gabriel Daenner
echo.

set JAVA_ARGS=undefined

if /i [%1]==[--interactive]  set JAVA_ARGS=
if /i [%1]==[--quick]        set JAVA_ARGS=noMenu

if exist ..\bin (
    cd ..\bin
    
    if exist *.class (
        echo Cleaning up ...
        del *.class
    ) else (echo Nothing to clean)
    
    cd ..
) else (
    echo Error: No build directory found.
    echo Closing application ...
    echo.
    pause
    exit /b
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

echo Searching for java-files ...
for /f %%i in ('dir /b/s *.java') do (
    set temp=%%i
    set filenames=!filenames! !temp!
)

echo Compiling sources ...
javac -d bin %filenames%

if not "%JAVA_ARGS%" == "undefined" (
    echo Running example-app ...
    cd bin
    java TestApp %JAVA_ARGS%
)

echo.
pause
