#include <vector>
#include <stdio.h>
#include <unistd.h>
#include "AutonoscriptReader.h"

using namespace AutonoScript;

static void PrintHelp();
static int ErrorOut(const char* error, int errCode);
inline int ReadArgs(int argc, char** argv, char** file, int* shouldExit);

int main(int argc, char** argv)
{
  char* file;
  int rtn, shouldExit;

  unsigned int count;
  RobotCommandCollection* commands;
  AutonoScriptReader* reader = new AutonoScriptReader();

  // TODO: Implement and Options Reader class.
  if (rtn = ReadArgs(argc, argv, &file, &shouldExit) || shouldExit)
    return rtn;
  
  commands = reader->ReadScriptFile(file);
  for (int i=0; i<commands->GetCommandCount(); i++)
    printf("Magnitude: %f\nType: %d\n\n", (*commands)[i]->GetMagnitude(), (*commands)[i]->GetCommand());

  delete reader;
  delete commands;

  return 0;
}

inline int ReadArgs(int argc, char** argv, char** file, int* shouldExit)
{
  int arg;

  *file = NULL;
  *shouldExit = 0;
  while ((arg = getopt(argc, argv, ":f:h")) != -1)
    switch(arg)
    {
      case 'f':
        *file = optarg;
        break;

      case 'h':
        PrintHelp();
        return !(*shouldExit = 1);
    }

  if (*file == NULL)
    return ErrorOut("File was not specified.", -1);

  return 0;
}

static void PrintHelp()
{
  printf("\nUsage: cmd -f FILE\n");
  printf("  -f FILE : Specifies AutonoScript FILE.\n");
  printf("  -h      : Prints help information.\n");
}

static int ErrorOut(const char* error, int errCode)
{
  PrintHelp();
  fprintf(stderr, "\nError: %s\n", error);

  return errCode;
}
