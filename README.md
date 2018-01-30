# AutonoScript

## Introduction
  Autonoscript is a simple scripting language for specifying sequence autonomous robot commands.  Right now the language only has three operators:
  - M (Moves the robot)
  - RC (Rotates the robot clockwise)
  - RCC (Rotates the robot counter-clockwise)

## Building
  The full AutonoScript project needs to be compiled in a unix-like environment, and depends on libcairo (for graphics.)  For Windows, the instructions are:
  - Download and install (https://cygwin.com/setup-x86_64.exe)[Cygwin] with these packages:
    - git
    - automake
    - g++
    - gdb
    - lynx
  - Install (https://github.com/transcode-open/apt-cyg)[apt-cyg] by running:
    - lynx -source rawgit.com/transcode-open/apt-cyg/master/apt-cyg > apt-cyg
    - install apt-cyg /bin
  - Install libcairo with the command:
    - apt-cyg install libcairo-devel
  - Enter the root of the solution, and run the script:
    - ./make.sh
