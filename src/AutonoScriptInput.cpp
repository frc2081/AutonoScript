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
  }

  AutonoScriptInput::~AutonoScriptInput()
  {
    _isSealed = true;
    _mode = UnknownMode;

    if (_file != NULL)
      free(_file);

    _file = NULL;
  }

  int AutonoScriptInput::IsValid()
  {
    return _isValid;
  }

  char* AutonoScriptInput::GetFile()
  {
    return _file;
  }

  AutonoScriptModes AutonoScriptInput::GetMode()
  {
    return _mode;
  }

  void AutonoScriptInput::SetMode(AutonoScriptModes mode)
  {
    SET_INPUT(_mode = mode);
  }

  void AutonoScriptInput::SetFile(char* file)
  {
    if(_isSealed) return;
    if (_file != NULL) free(_file);

    _file = (char*) malloc(sizeof(char) * (strlen(file)+1));
    strcpy(_file, file);
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
}
