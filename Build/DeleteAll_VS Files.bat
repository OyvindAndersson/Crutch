@echo off
pushd %~dp0\..\
ECHO Delete all MSVS project and solution filters
ECHO --------------------------------------------
setlocal
:PROMPT
SET /P AREYOUSURE=Are you sure? (Y/[N])?
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END

del /S *.sln
del /S *.vcxproj
del /S *.vcxproj.filters
del /S *.vcxproj.user
ECHO --------------------------------------------

SET /P ALSORMBINS=Would you also like to delete all built binaries / intermediates? ([Y]/N)?
IF /I "%ALSORMBINS%" NEQ "N" GOTO RMBINS
ECHO --------------------------------------------

:RMBINS
rmdir /S Binaries
rmdir /S Binaries-Int

:END
endlocal
popd
PAUSE