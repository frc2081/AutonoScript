#include <stdio.h>

#include "AutonoScriptManager.h"
#include "FieldGenerator.h"

namespace AutonoScript
{
  using namespace std;
  using namespace std::regex_constants;

  // Construct / Destructor
  AutonoScriptManager::AutonoScriptManager()
  {
    _scriptReader = new AutonoScriptReader();
    _inputReader = new AutonoScriptInputReader();
    
    // TODO: Do this better.
    _fieldDefinition = new FieldDefinition();
    _fieldGenerator = new FieldGenerator(_fieldDefinition);

    _redRegex = new regex("^ *r(ed)? *$", icase);
    _blueRegex = new regex("^ *b(lue)? *$", icase);
  }

  AutonoScriptManager::~AutonoScriptManager()
  {
    delete _scriptReader;
    delete _inputReader;
    delete _fieldGenerator;
    delete _redRegex;
    delete _blueRegex;
    delete _fieldDefinition;
  }

  // Public Methods
  int AutonoScriptManager::Run(int argc, char** argv)
  {
    int rtn;
    char* inputFile;
    AutonoScriptModes mode;
    AutonoScriptInput* input;
    RobotCommandCollection* commands;

    // Read input from command line.
    input = _inputReader->Read(argc, argv);

    // Print help, if specified.
    if ((mode = input->GetMode()) == PrintHelp)
    {
        _inputReader->PrintConsoleHelp();
        return 0;
    }

    // Validate that input file is specified.
    if (mode == UnknownMode || (inputFile = input->GetFile()) == NULL)
      return ErrorOut("Must specify an input file with -f.", 1);


    // Read the input file.
    commands = _scriptReader->ReadScriptFile(input->GetFile());

    switch(mode)
    {
      case ReadFromFile:
        rtn = PrintRobotCommands(commands, input);
        break;

      case GenerateImage:
        rtn = GenerateField(commands, input);
        break;
    }
    
    delete input;
    delete commands;

    return rtn;
  }

  // Private Methods
  int AutonoScriptManager::PrintRobotCommands(RobotCommandCollection* commands, AutonoScriptInput* input)
  {
    for (int i=0; i<commands->GetCommandCount(); i++)
      printf("Magnitude: %f\nType: %d\n\n", (*commands)[i]->GetMagnitude(), (*commands)[i]->GetCommand());
  }

  int AutonoScriptManager::GenerateField(RobotCommandCollection* commands, AutonoScriptInput* input)
  {
    char* outputFile;
    FieldPositions position;
    if ((position = GetFieldPosition(input)) == UnknownPosition)
      return ErrorOut("Uknown position.  Must specify with -t TEAM and -p POSITION.", 2);

    if ((outputFile = input->GetOutputFile()) == NULL)
      return ErrorOut("Must specify an output file with -o.", 3);

    
    _fieldGenerator->Generate(position, commands, outputFile);
    return 0;
  }


  int AutonoScriptManager::ErrorOut(const char* error, int errCode)
  {
    _inputReader->PrintConsoleHelp();
    fprintf(stderr, "\nError: %s\n", error);

    return errCode;
  }


  FieldPositions AutonoScriptManager::GetFieldPosition(AutonoScriptInput* input)
  {
    int position = UnknownPosition;
    char* team = input->GetTeam();
    int posVal = input->GetPosition();

    if (team == NULL || posVal < 1 || posVal > 3)
      return (FieldPositions) position;

     if (regex_match(team, *_redRegex))
       position |= RedTeam;

     if (regex_match(team, *_blueRegex))
       position |= BlueTeam;

     position |= (BlueTeam << posVal);
     return (FieldPositions) position;
  }
}
