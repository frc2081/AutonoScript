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

    while ((arg = getopt(argc, argv, ":f:o:h")) != -1)
      switch(arg)
      {
        case 'f':
          input->SetFile(optarg);
          break;

        case 'o':
          input->SetOutputFile(optarg);
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
}
