#ifndef AUTONOSCRIPT_INPUT_READ_H
#define AUTONOSCRIPT_INPUT_READ_H 1

#include "AutonoScriptInput.h"

namespace AutonoScript
{
  class AutonoScriptInputReader
  {
    public:
      AutonoScriptInputReader();
      virtual ~AutonoScriptInputReader();

      AutonoScriptInput* Read(int argc, char** argv);
    
    private:
      int _printHelp;
  };
}

#endif
