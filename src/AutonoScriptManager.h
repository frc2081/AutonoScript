#ifndef AUTONOSCRIPT_MANAGER_H
#define AUTONOSCRIPT_MANAGER_H 1

#include <regex>
#include "AutonoscriptReader.h"
#include "AutonoScriptInputReader.h"
#include "FieldGenerator.h"
#include "AutonoScriptInput.h"
#include "FieldDefinition.h"

namespace AutonoScript
{
  class AutonoScriptManager
  {
    public:
      AutonoScriptManager();
      virtual ~AutonoScriptManager();

      int Run(int argc, char** argv);
    
    private:
      int ErrorOut(const char* error, int errCode);
      int PrintRobotCommands(RobotCommandCollection* commands, AutonoScriptInput* input);
      int GenerateField(RobotCommandCollection* commands, AutonoScriptInput* input);
      FieldPositions GetFieldPosition(AutonoScriptInput* input);

      AutonoScriptReader* _scriptReader;
      AutonoScriptInputReader* _inputReader;
      FieldDefinition* _fieldDefinition;

      std::regex* _redRegex;
      std::regex* _blueRegex;
  };
}

#endif
