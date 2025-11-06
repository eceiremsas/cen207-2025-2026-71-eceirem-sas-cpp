@echo off
@setlocal enableextensions
@cd /d "%~dp0"

rem Get the current directory path
for %%A in ("%~dp0.") do (
    set "currentDir=%%~fA"
)

echo Delete and Create the "release" folder and its contents
rd /S /Q "release_win"
rd /S /Q "publish_win"
rd /S /Q "build_win"
mkdir publish_win
mkdir release_win
mkdir build_win

echo Folders are Recreated successfully.

echo Testing Application with Coverage
echo Configure CMAKE
call cmake -B build_win -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX:PATH=publish_win
echo Build CMAKE Debug/Release
call cmake --build build_win --config Debug -j4
call cmake --build build_win --config Release -j4
call cmake --install build_win --strip
echo Test CMAKE
cd build_win
call ctest -C Debug --output-on-failure
cd ..

echo Running Test Executable

if exist ".\publish_win\bin\recipe_tests.exe" (
    call .\publish_win\bin\recipe_tests.exe
) else (
    echo Warning: recipe_tests.exe not found in publish_win\bin
    echo Trying build_win\build\Debug\recipe_tests.exe
    if exist ".\build_win\build\Debug\recipe_tests.exe" (
        call .\build_win\build\Debug\recipe_tests.exe
    )
)

if exist ".\publish_win\bin\recipeapp.exe" (
    call .\publish_win\bin\recipeapp.exe
)

echo Files and folders copied successfully.

echo Package Publish Windows Binaries
tar -czvf release_win\windows-publish-binaries.tar.gz -C publish_win .

echo Package Publish Windows Binaries
tar -czvf release_win\windows-release-binaries.tar.gz -C build_win\build\Release .

echo Package Publish Debug Windows Binaries
tar -czvf release_win\windows-debug-binaries.tar.gz -C build_win\build\Debug .

echo ....................
echo Operation Completed!
pause