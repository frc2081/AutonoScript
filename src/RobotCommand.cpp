#include "RobotCommand.h"


namespace AutonoScript
{
  RobotCommand::RobotCommand(double magnitude, RobotCommands command)
  {
    _magnitude = magnitude;
    _command = command;
  }

  RobotCommand::~RobotCommand()
  {
    _magnitude = -1;
    _command = UnknownCommand;
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
