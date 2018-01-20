#include "RobotCommandCollection.h"

using namespace std;

namespace AutonoScript
{
  RobotCommandCollection::RobotCommandCollection()
  {
    _commands = new vector<RobotCommand*>();
  }

  RobotCommandCollection::~RobotCommandCollection()
  {
    int i, count = GetCommandCount();
    for (i=0; i<count; i++)
      delete GetCommand(i);

    delete _commands;
  }

  void RobotCommandCollection::AddRobotCommand(double magnitude, RobotCommands command)
  {
    _commands->push_back(new RobotCommand(magnitude, command));
  }

  RobotCommand* RobotCommandCollection::GetCommand(int index)
  {
    return _commands->at(index); 
  }

  int RobotCommandCollection::GetCommandCount()
  {
    return _commands->size();
  }
}
