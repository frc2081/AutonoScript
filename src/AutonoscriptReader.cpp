#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
    double magnitude, facing;
    RobotCommands command;

    RobotCommandCollection* commands = new RobotCommandCollection();
    while (ReadCommand(script, &position, &command, &magnitude, &facing))
      commands->AddRobotCommand(magnitude, command, facing);

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
  int AutonoScriptReader::ReadCommand(const char* script, int* position, RobotCommands* command, double* magnitude, double* facing)
  {
    int rtn;
    char curr;
    string cmdStr, magStr, faceStr;

    EXTRACT_ROB_CMD_TOKEN(cmdStr);
    EXTRACT_ROB_CMD_TOKEN(magStr);

    *facing = 0;
    *magnitude = strtod(magStr.c_str(), NULL);
    *command = GetRobotCommand(&cmdStr);

    // For now, only a move command has a real facing.
    if (*command != Move)
      return 1;

    EXTRACT_ROB_CMD_TOKEN(faceStr);
    *facing = strtod(faceStr.c_str(), NULL);
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

    return true;
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
    const char* cmdChr = cmdStr->c_str();

    if (!strcmp(cmdChr, "M"))
      return Move;

    if (!strcmp(cmdChr, "RC"))
      return RotateClockwise;

    return (strcmp(cmdChr, "RCC"))
      ? UnknownCommand
      : RotateCounterClockwise;
  }
}
