#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "AutonoscriptReader.h"

using namespace std;

namespace AutonoScript
{
  // Inline Function Declarations
  static inline int GetNextToken(const char* script, int* position, string* token);
  static inline int IsTokenChar(const char character);
  static inline RobotCommands GetRobotCommand(string* cmdStr);

  // Constructor | Destructor
  AutonoScriptReader::AutonoScriptReader()
  {
  }

  AutonoScriptReader::~AutonoScriptReader()
  {
  }
      
  // Public Methods
  RobotCommandCollection* AutonoScriptReader::ReadScriptFile(const char* fileName)
  {
    int rtn;
    char* script; 

    ReadFromFile(fileName, &script);

    RobotCommandCollection* commands;
    commands = ReadScript(script);
    delete script;

    return commands;
  }

  RobotCommandCollection* AutonoScriptReader::ReadScript(const char* script)
  {

    int position = 0;
    double magnitude;
    RobotCommands command;

    RobotCommandCollection* commands = new RobotCommandCollection();
    while (ReadCommand(script, &position, &command, &magnitude))
      commands->AddRobotCommand(magnitude, command);

    return commands;
  }

  // Private Methods
  void AutonoScriptReader::ReadFromFile(const char* fileName, char** script)
  {
    FILE *file;
    long fileSize;
    
    file = fopen(fileName, "rb");

    fseek(file, 0L, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    *script = new char[fileSize+1];
    fread(*script, fileSize, sizeof(char), file);
    fclose(file);
  }


#define EXTRACT_ROB_CMD_TOKEN(strVal) if (!(rtn = GetNextToken(script, position, &strVal))) return rtn;
  int AutonoScriptReader::ReadCommand(const char* script, int* position, RobotCommands* command, double* magnitude)
  {
    int rtn;
    char curr;
    string cmdStr, magStr;

    EXTRACT_ROB_CMD_TOKEN(cmdStr);
    EXTRACT_ROB_CMD_TOKEN(magStr);

    *magnitude = strtod(magStr.c_str(), NULL);
    *command = GetRobotCommand(&cmdStr);
  }

  // Inline Functions
#define GET_NEXT_TOKEN_CHAR current = script[(*position)++]
  static inline int GetNextToken(const char* script, int* position, string* token)
  {
    char current;

    while(!IsTokenChar(GET_NEXT_TOKEN_CHAR))
      if (current == 0x0)
        return 0;

    *token += current;
    while (IsTokenChar(GET_NEXT_TOKEN_CHAR))
      *token += current;

    return current != 0x0;
  }
  
  static inline int IsTokenChar(const char character)
  {
    const int charCnt = 4;
    const char tokenChars[] =
    {
      'M', 'R', 'C', '.'
    };

    for(int i=0; i<charCnt; i++) if (character == tokenChars[i]) return 1;
    return isdigit(character);
  }

  static inline RobotCommands GetRobotCommand(string* cmdStr)
  {
    if (cmdStr->compare("M"))
      return Move;

    if (cmdStr->compare("RC"))
      return RotateClockwise;

    return (cmdStr->compare("RCC"))
      ? RotateCounterClockwise
      : UnknownCommand;
  }
}
