#ifndef AUTONOSCRIPT_MANAGER_H
#define AUTONOSCRIPT_MANAGER_H 1

#include "AutonoscriptReader.h"
#include "AutonoScriptInputReader.h"

namespace AutonoScript
{
  class AutonoScriptManager
  {
    public:
      AutonoScriptManager();
      virtual ~AutonoScriptManager();

      int Run(int argc, char** argv);
    
    private:
      int PrintConsoleHelp();
      int ErrorOut(const char* error, int errCode);

      AutonoScriptReader* _scriptReader;
      AutonoScriptInputReader* _inputReader;
  };
}

#endif
