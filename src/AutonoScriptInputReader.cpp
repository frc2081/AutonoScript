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

    while ((arg = getopt(argc, argv, ":f:h")) != -1)
      switch(arg)
      {
        case 'f':
          input->SetFile(optarg);
          break;

        case 'h':
          input->SetMode(PrintHelp);
          break;
      }

    if (input->GetMode() == UnknownMode && input->GetFile() != NULL)
      input->SetMode(ReadFromFile);

    return input->Seal();
  }
}
