#ifndef ROBOT_CMD_COL_H
#define ROBOT_CMD_COL_H 1

#include <vector>
#include "RobotCommand.h"

namespace AutonoScript
{
  class RobotCommandCollection
  {
    public:
      // Constructor | Destructor
      RobotCommandCollection();
      virtual ~RobotCommandCollection();

      // Public Methods
      void AddRobotCommand(double magnitude, RobotCommands command);
      RobotCommand* GetCommand(int index);
      int GetCommandCount();
     
      // Overloads
      RobotCommand* operator[] (int index)
      {
        return GetCommand(index);
      }

    private:
      std::vector<RobotCommand*>* _commands;
  };
}

#endif
