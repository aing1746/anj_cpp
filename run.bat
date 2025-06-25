@echo off
g++ -std=c++23 -o a src/main.cpp
IF %ERRORLEVEL% NEQ 0 EXIT
a.exe
