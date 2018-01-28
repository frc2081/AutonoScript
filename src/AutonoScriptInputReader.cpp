#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "AutonoScriptInputReader.h"


namespace AutonoScript
{
  AutonoScriptInputReader::AutonoScriptInputReader()
  {
  }

  AutonoScriptInputReader::~AutonoScriptInputReader()
  {
  }

  AutonoScriptInput* AutonoScriptInputReader::Read(int argc, char** argv)
  {
    char arg;
    AutonoScriptInput* input = new AutonoScriptInput();

    while ((arg = getopt(argc, argv, ":f:o:t:p:h")) != -1)
      switch(arg)
      {
        case 'f':
          input->SetFile(optarg);
          break;

        case 'o':
          input->SetOutputFile(optarg);
          break;

        case 't':
          input->SetTeam(optarg);
          break;

        case 'p':
          // TODO: Error handling.
          input->SetPosition(atoi(optarg));
          break;

        case 'h':
          input->SetMode(PrintHelp);
          break;
      }

    input->SetMode(GetMode(input));
    return input->Seal();
  }


  AutonoScriptModes AutonoScriptInputReader::GetMode(AutonoScriptInput* input)
  {
    AutonoScriptModes currentMode = input->GetMode();

    if (currentMode != UnknownMode)
      return currentMode;


    if (input->GetOutputFile() != NULL)
      return GenerateImage;


    return input->GetFile() == NULL
      ? currentMode
      : ReadFromFile;
  }

  int AutonoScriptInputReader::PrintConsoleHelp()
  {
    printf("\nUsage: cmd -f FILE [-o FILE -t TEAM -p POSITION]\n");
    printf("  -f FILE     : Specifies AutonoScript FILE.\n");
    printf("  -o FILE     : Specifies image output FILE.\n");
    printf("  -t TEAM     : Specifies starting TEAM.\n");
    printf("  -p POSITION : Specifies starting POSITION.\n");
    printf("  -h          : Prints help information.\n");
  }
}
