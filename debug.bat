@echo off
g++ -std=c++23 -g -o a src/main.cpp
IF %ERRORLEVEL% NEQ 0 EXIT
gdb -q -x debug.gdb a.exe
