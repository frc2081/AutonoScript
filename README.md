# AutonoScript

## Introduction
  Autonoscript is a simple scripting language for specifying sequence autonomous robot commands.  Right now the language only has three operators:
  - M (Moves the robot)
  - RC (Rotates the robot clockwise)
  - RCC (Rotates the robot counter-clockwise)

## Building
  The full AutonoScript project needs to be compiled in a unix-like environment, and depends on libcairo (for graphics.)  For Windows, the instructions are:
  - Download and install [Cygwin](https://cygwin.com/setup-x86_64.exe) with these packages:
    - git
    - automake
    - g++
    - gdb
    - lynx
  - Install [apt-cyg](https://github.com/transcode-open/apt-cyg) by running:
      ````
      lynx -source rawgit.com/transcode-open/apt-cyg/master/apt-cyg > apt-cyg
      install apt-cyg /bin
      ````
  - Install libcairo with the command:
    ````
    apt-cyg install libcairo-devel
    ````
  - Enter the root of the solution, and run the script:
    ````
    ./make.sh
    ````
 ## Language
  Operators and operands are separated by white space.  An expression consists of an operator and the constant number of operands that it receives.  The expression is terminated immediately after the correct number of operands have been read.
  
### Move
````
 M MAGNITUDE FACING
````
  The move operator takes two operands: magnitude (distance (in meters) the robot should travel) and facing (the angle it should move on (relative to where the robot was first facing and had its gyro zeroed.))  So for the command ````M 3 45````, the robot will travel 3 meters, 45 degrees from where the robot started.
  
### RC
````
RC MAGNITUDE
````
  The clockwise rotation operator only takes one command: magnitude (the number of degrees that should be rotated.)  This changes the facing of the robot, without altering the direction it will move in any way.
  
### RCC
````
RCC MAGNITUDE
````
  The counter-clockwise rotation operator acts exactly the same way the clockwise operator does, except the rotation is counter-clockwise.
  
### Examples
````
M 3 0
M 1 45
RCC 90
````
  This script would move the robot forward 3 meters, then travel 45 degrees for one meter, then it will rotate counterclockwise 90 degrees (facing left, from where the robot originally started.)
  
## AutonoscriptCommand.exe
### Full Description
  The main binary produced is AutonoscriptCommand.  It's a command line utility, that takes parameters using the [getopts syntax](http://wiki.bash-hackers.org/howto/getopts_tutorial).  When the command is run, it must have either a script file (specified with -f) or an inline script, directly from the command line (specified with -S).

  If only a script is provided, the program will parse it, and output the commands to the command line.  This is primarily used for validating the integrity of a script file.
  
  Additionally, you can specify an output file with -o, a team (RED or BLUE) with -t, and a starting positon (1-3) with -p.  Doing so will have the program calculate the full path that the robot will travel, and generate a series of coordinates (corresponding with an internal field definition).  If no further arguments are provided, the path will be printed to the command line.
  
  If you provide a -T option, you can specify the kind of output (PNG, CSV, or CONSOLE).
    - CONSOLE: The default behavior; it prints the coordinates to the command line.
    - CSV: Produces a comma-separated values file, of the coordinates the robot will travel on.
    - PNG: Produces a graphic, that draws the current playing field, the path the robot takes along it, and the final position/facing.
    
### Usage
````
Usage: cmd (-f FILE | -S SCRIPT) [-o FILE -t TEAM -p POSITION [-T OUTPUT_TYPE]]
  -f FILE         : Specifies AutonoScript FILE.
  -S SCRIPT       : Provided SCRIPT contents to run.
  -o FILE         : Specifies image output FILE.
  -t TEAM         : Specifies starting TEAM.
  -p POSITION     : Specifies starting POSITION.
  -T OUTPUT_TYPE  : Specifies the OUTPUT_TYPE.
  -h              : Prints help information.
````

### Examples
````
./bin/AutonoscriptCommand.exe -S 'M 5.25 0 M 0.75 45 M 5 90 M 1.5 180 M 0.5 270 RCC 90' -o foo.png -t RED -p 1 -T png
````

Produces a graphic called foo.png, with the robot starting at team RED, position 1, and following the path specified by -S.  This currently produces:

![foo.png](https://i.imgur.com/cNUKGOs.png)



 
