@echo off

echo creating projects...

premake5 vs2019
premake5 export-compile-commands

echo finished.