@echo off
pushd %~dp0\..\

del /S *.sln
del /S *.vcxproj
del /S *.vcxproj.filters
del /S *.vcxproj.user

popd
PAUSE