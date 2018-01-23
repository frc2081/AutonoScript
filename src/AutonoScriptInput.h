#ifndef AUTONOSCRIPT_INPUT_H
#define AUTONOSCRIPT_INPUT_H 1

namespace AutonoScript
{
  enum AutonoScriptModes
  {
    UnknownMode = 0x0,
    PrintHelp = 0x1,
    ReadFromFile = 0x2
  };

  class AutonoScriptInput
  {
    public:
      AutonoScriptInput();
      virtual ~AutonoScriptInput();

      int IsValid();

      char* GetFile();
      AutonoScriptModes GetMode();

      void SetMode(AutonoScriptModes mode);
      void SetFile(char* file);
      AutonoScriptInput* Seal();

    private:
      int _isValid;
      char* _file;
      int _isSealed;

      AutonoScriptModes _mode;

      void Validate();
  };
}

#endif
