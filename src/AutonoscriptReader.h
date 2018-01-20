#ifndef AUTONO_READER_H
#define AUTONO_READER_H 1

#include <vector>
#include "RobotCommandCollection.h"

using namespace std;

namespace AutonoScript
{
  class AutonoScriptReader
  {
    public:
      AutonoScriptReader();
      virtual ~AutonoScriptReader();
      
      RobotCommandCollection* ReadScriptFile(const char* fileName);
      RobotCommandCollection* ReadScript(const char* script);

    private:
      void ReadFromFile(const char* fileName, char** script);
      int ReadCommand(const char* script, int* position, RobotCommands* command, double* magnitude, double* facing);
  };
}

#endif 
