#include "RobotCommand.h"


namespace AutonoScript
{
  RobotCommand::RobotCommand(double magnitude, RobotCommands command, double facing)
  {
    _facing = facing;
    _command = command;
    _magnitude = magnitude;
  }

  RobotCommand::~RobotCommand()
  {
    _facing = 0;
    _magnitude = -1;
    _command = UnknownCommand;
  }

  double RobotCommand::GetFacing()
  {
    return _facing;
  }

  double RobotCommand::GetMagnitude()
  {
    return _magnitude;
  }

  RobotCommands RobotCommand::GetCommand()
  {
    return _command;
  }
}
