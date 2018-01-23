#include <stdio.h>

#include "AutonoScriptManager.h"

namespace AutonoScript
{
  // Construct / Destructor
  AutonoScriptManager::AutonoScriptManager()
  {
    _scriptReader = new AutonoScriptReader();
    _inputReader = new AutonoScriptInputReader();
  }

  AutonoScriptManager::~AutonoScriptManager()
  {
    delete _scriptReader;
    delete _inputReader;
  }

  // Public Methods
  int AutonoScriptManager::Run(int argc, char** argv)
  {
    AutonoScriptInput* input;
    RobotCommandCollection* commands;

    input = _inputReader->Read(argc, argv);
    // TODO: Do a better job of this.
    if (input->GetMode() == UnknownMode)
      return ErrorOut("Must specify an input file with -f.", 1);

    if (input->GetMode() == PrintHelp)
    {
      PrintConsoleHelp();
      return 0;
    }
    
    commands = _scriptReader->ReadScriptFile(input->GetFile());
    for (int i=0; i<commands->GetCommandCount(); i++)
      printf("Magnitude: %f\nType: %d\n\n", (*commands)[i]->GetMagnitude(), (*commands)[i]->GetCommand());

    delete input;
    delete commands;

    return 0;
  }

  // Private Methods
  int AutonoScriptManager::PrintConsoleHelp()
  {
    printf("\nUsage: cmd -f FILE\n");
    printf("  -f FILE : Specifies AutonoScript FILE.\n");
    printf("  -h      : Prints help information.\n");
  }

  int AutonoScriptManager::ErrorOut(const char* error, int errCode)
  {
    PrintConsoleHelp();
    fprintf(stderr, "\nError: %s\n", error);

    return errCode;
  }
}
