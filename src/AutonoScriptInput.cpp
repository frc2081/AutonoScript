#include "AutonoScriptCommandInputReader.h"

namespace AutonoScript
{
#define SET_INPUT(assignment) if (!_isSealed) assignment;
  AutonoScriptInput::AutonoScriptInput()
  {
    _isSealed = false;
    _mode = UnknownMode;
    _file = NULL;
  }

  virtual AutonoScriptInput::~AutonoScriptInput()
  {
    _isSealed = true;
    _mode = UnknownMode;
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
    SET_INPUT(_file = file);
  }

  void AutonoScriptInput::Seal()
  {
    _isSealed = true;
    Validate();
  }

  void AutonoScriptInput::Validate()
  {
    // TODO: Expand this.
    _isValid = _file != NULL
      && _mode != UnknownMode;
  }
}
