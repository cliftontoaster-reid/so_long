@echo off
setlocal enabledelayedexpansion

:: Check for administrative privileges and elevate if necessary
call :checkAdmin || (
    echo Requesting administrative privileges...
    powershell -Command "Start-Process -FilePath '%~f0' -Verb RunAs"
    exit /b
)

REM This script will install WSL 2, set up Ubuntu, install dependencies,
REM execute "make", define environment variables, and run ./so_long.

REM **Prerequisites:**
REM - You need to have Windows 10 version 2004 or higher (Build 19041 or higher) or Windows 11.
REM - You need to have virtualization enabled in your BIOS.

echo Checking if WSL feature is enabled...
dism /online /get-feature /featurename:Microsoft-Windows-Subsystem-Linux | findstr /I "State : Enabled"
if %errorlevel% neq 0 (
    :checkAdmin
    echo Enabling WSL feature...
    dism /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
) else (
    echo WSL feature is already enabled.
)

echo Checking if Virtual Machine Platform feature is enabled...
dism /online /get-feature /featurename:VirtualMachinePlatform | findstr /I "State : Enabled"
if %errorlevel% neq 0 (
    :checkAdmin
    echo Enabling Virtual Machine Platform feature...
    dism /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
    echo Please restart your computer now to complete the installation of these features.
    pause
    exit /b
) else (
    echo Virtual Machine Platform feature is already enabled.
)

echo Checking if WSL 2 is the default version...
wsl --list --verbose | findstr /I "WSL 2"
if %errorlevel% neq 0 (
    :checkAdmin
    echo Setting default WSL version to 2...
    wsl --set-default-version 2
    echo If you encounter an error, you might need to update the WSL 2 kernel.
    echo You can find instructions here: https://learn.microsoft.com/en-us/windows/wsl/install-manual#step-4---download-the-linux-kernel-update-package
    pause
) else (
    echo WSL 2 is already the default version.
)

echo Checking if Ubuntu is installed...
wsl --list --online | findstr /I "Ubuntu"
wsl --list --distributions | findstr /I "Ubuntu"
if %errorlevel% neq 0 (
    :checkAdmin
    echo Installing the latest Ubuntu...
    wsl --install -d Ubuntu
    echo Please wait while Ubuntu is being installed. This might take a few minutes.
    echo Once the installation is complete, a new terminal window will open for the initial Ubuntu setup.
    echo Please set up your username and password when prompted.
    wsl -d Ubuntu
    pause
) else (
    echo Ubuntu is already installed.
)

echo Opening Ubuntu to install dependencies and run commands...
start wsl -d Ubuntu -e bash -c "sudo apt update && sudo apt install -y build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev && cd /mnt/c/%cd:/ && make && export DISPLAY=$(ip route list default | awk '{print \$3}'):0 && export LIBGL_ALWAYS_INDIRECT=0 && ./so_long"

echo Script finished. The 'so_long' application should be running in the Ubuntu window.
pause
