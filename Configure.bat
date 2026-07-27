@echo off

REM Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
powershell.exe -ExecutionPolicy Bypass -File "configure.ps1"

pause
