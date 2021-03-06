#ifndef ROBOT_CMD_H
#define ROBOT_CMD_H 1

namespace AutonoScript
{
  enum RobotCommands
  {
    UnknownCommand = 0x0,
    Move = 0x1,
    RotateClockwise = 0x2,
    RotateCounterClockwise = 0x3
  };

  class RobotCommand
  {
    public:
      RobotCommand(double magnitude, RobotCommands command, double facing);
      virtual ~RobotCommand();

      double GetFacing();
      double GetMagnitude();
      RobotCommands GetCommand();

    private:
      double _facing;
      double _magnitude;
      RobotCommands _command;
  };
}

#endif
