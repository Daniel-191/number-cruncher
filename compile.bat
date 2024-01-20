@echo off
echo Compiling main.cpp...
g++ main.cpp -o main

if %errorlevel% equ 0 (
    echo Compilation successful!
    exit /b 0
) else (
    echo Compilation failed!
    exit /b 1
)
