#include <stdlib.h>
#include <string.h>
#include "AutonoScriptInputReader.h"

namespace AutonoScript
{
#define SET_INPUT(assignment) if (!_isSealed) assignment;
  AutonoScriptInput::AutonoScriptInput()
  {
    _isSealed = false;
    _position = 0;
    _mode = UnknownMode;
    _file = NULL;
    _team = NULL;
    _script = NULL;
    _outputFile = NULL;
    _outputType = NULL;
  }

  AutonoScriptInput::~AutonoScriptInput()
  {
    _isSealed = true;
    _mode = UnknownMode;

    if (_file != NULL)
      free(_file);

    if (_outputFile != NULL)
      free(_outputFile);

    if (_team != NULL)
      free(_team);

    if (_outputType != NULL)
      free(_outputType);

    if (_script != NULL)
      free(_script);

    _file = NULL;
    _outputFile = NULL;
    _team = NULL;
    _position = 0;
  }

  int AutonoScriptInput::IsValid()
  {
    return _isValid;
  }

  char* AutonoScriptInput::GetFile()
  {
    return _file;
  }

  char* AutonoScriptInput::GetOutputFile()
  {
    return _outputFile;
  }

  char* AutonoScriptInput::GetTeam()
  {
    return _team;
  }

  char* AutonoScriptInput::GetOutputType()
  {
    return _outputType;
  }

  char* AutonoScriptInput::GetScript()
  {
    return _script;
  }

  int AutonoScriptInput::GetPosition()
  {
    return _position;
  }

  AutonoScriptModes AutonoScriptInput::GetMode()
  {
    return _mode;
  }

  void AutonoScriptInput::SetMode(AutonoScriptModes mode)
  {
    SET_INPUT(_mode = mode);
  }

  void AutonoScriptInput::SetFile(const char* file)
  {
    SetStringInputValue(&_file, file);
  }

  void AutonoScriptInput::SetOutputFile(const char* outputFile)
  {
    SetStringInputValue(&_outputFile, outputFile);
  }

  void AutonoScriptInput::SetTeam(const char* team)
  {
    SetStringInputValue(&_team, team);
  }

  void AutonoScriptInput::SetOutputType(const char* outputType)
  {
    SetStringInputValue(&_outputType, outputType);
  }

  void AutonoScriptInput::SetScript(const char* script)
  {
    SetStringInputValue(&_script, script);
  }


  void AutonoScriptInput::SetPosition(int position)
  {
    _position = position;
  }

  AutonoScriptInput* AutonoScriptInput::Seal()
  {
    _isSealed = true;
    Validate();

    return this;
  }

  void AutonoScriptInput::Validate()
  {
    // TODO: Expand this.
    _isValid = _file != NULL
      && _mode != UnknownMode;
  }

  void AutonoScriptInput::SetStringInputValue(char** destination, const char* source)
  {
    if(_isSealed) return;
    if ((*destination) != NULL) free(*destination);

    *destination = (char*) malloc(sizeof(char) * strlen(source)+1);
    strcpy(*destination, source);
  }
}
