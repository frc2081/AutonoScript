#ifndef AUTONOSCRIPT_INPUT_H
#define AUTONOSCRIPT_INPUT_H 1

namespace AutonoScript
{
  enum AutonoScriptModes
  {
    UnknownMode = 0x0,
    PrintHelp = 0x1,
    ReadFromFile = 0x2,
    GenerateImage = 0x3
  };

  class AutonoScriptInput
  {
    public:
      AutonoScriptInput();
      virtual ~AutonoScriptInput();

      int IsValid();

      char* GetFile();
      char* GetOutputFile();
      AutonoScriptModes GetMode();

      void SetMode(AutonoScriptModes mode);
      void SetFile(const char* file);
      void SetOutputFile(const char* file);
      AutonoScriptInput* Seal();

    private:
      int _isValid;
      char* _file;
      char* _outputFile;
      int _isSealed;

      AutonoScriptModes _mode;

      void Validate();
      void SetStringInputValue(char** destination, const char* source);
  };
}

#endif
