@echo off
echo Building project...

REM Change directory to the project root to ensure CMake runs correctly
pushd "%~dp0"

cmake --build ./build

REM Check if the build command returned an error
IF %ERRORLEVEL% NEQ 0 (
    echo Build failed. Not running executable.
    popd
    goto :eof
)

echo Build successful. Running executable...
REM Path to your executable, assuming Debug configuration
"./build/Debug/Mario.exe"
"./build/Mario.exe"
REM Change back to the original directory if needed, though usually not necessary for this script
popd

REM Pause to keep the window open after execution if there are no errors
pause