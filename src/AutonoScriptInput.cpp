#include <stdlib.h>
#include <string.h>
#include "AutonoScriptInputReader.h"

namespace AutonoScript
{
#define SET_INPUT(assignment) if (!_isSealed) assignment;
  AutonoScriptInput::AutonoScriptInput()
  {
    _isSealed = false;
    _mode = UnknownMode;
    _file = NULL;
    _outputFile = NULL;
  }

  AutonoScriptInput::~AutonoScriptInput()
  {
    _isSealed = true;
    _mode = UnknownMode;

    if (_file != NULL)
      free(_file);

    if (_outputFile != NULL)
      free(_outputFile);

    _file = NULL;
    _outputFile = NULL;
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
