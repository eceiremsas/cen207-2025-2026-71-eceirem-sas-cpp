@echo off
@setlocal enableextensions
@cd /d "%~dp0"

echo Cleaning build directories...
if exist "build_win" (
    rd /S /Q "build_win"
    echo build_win deleted
) else (
    echo build_win does not exist
)

if exist "build" (
    rd /S /Q "build"
    echo build deleted
) else (
    echo build does not exist
)

echo Cleanup completed!
pause

