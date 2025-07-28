@echo off
echo Compiling main.cpp...
g++ main.cpp -o main.exe
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b %errorlevel%
)
echo Running the program...
main.exe
pause