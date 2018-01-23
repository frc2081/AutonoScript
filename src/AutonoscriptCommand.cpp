#include <stdio.h>

#include "AutonoscriptReader.h"
#include "AutonoScriptInputReader.h"

using namespace AutonoScript;

static void PrintConsoleHelp();
static int ErrorOut(const char* error, int errCode);

int main(int argc, char** argv)
{
  // TODO: Replace this all with a manager.
  AutonoScriptInput* input;
  RobotCommandCollection* commands;
  AutonoScriptReader* scriptReader = new AutonoScriptReader();
  AutonoScriptInputReader* inputReader = new AutonoScriptInputReader();

  input = inputReader->Read(argc, argv);
  if (input->GetMode() == UnknownMode)
    return ErrorOut("Must specify an input file with -f.", 1);

  if (input->GetMode() == PrintHelp)
  {
    PrintConsoleHelp();
    return 0;
  }
  
  commands = scriptReader->ReadScriptFile(input->GetFile());
  for (int i=0; i<commands->GetCommandCount(); i++)
    printf("Magnitude: %f\nType: %d\n\n", (*commands)[i]->GetMagnitude(), (*commands)[i]->GetCommand());

  delete input;
  delete commands;
  delete inputReader;
  delete scriptReader;

  return 0;
}


static void PrintConsoleHelp()
{
  printf("\nUsage: cmd -f FILE\n");
  printf("  -f FILE : Specifies AutonoScript FILE.\n");
  printf("  -h      : Prints help information.\n");
}

static int ErrorOut(const char* error, int errCode)
{
  PrintConsoleHelp();
  fprintf(stderr, "\nError: %s\n", error);

  return errCode;
}
