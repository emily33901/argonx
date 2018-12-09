@echo off

pushd %~dp0

call create_projects

echo building...

for /F "tokens=*" %%a in ('find_my_visual_studio.exe msbuild_exe') do set msbuild_folder=%%a

echo msbuild is located at %msbuild_folder%

"%msbuild_folder%\\msbuild" /property:GenerateFullPaths=true /t:build premake\workspace.sln /p:Configuration=Debug /verbosity:minimal

echo done.

popd
exit
