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
      char* GetTeam();
      char* GetOutputType();
      int GetPosition();
      AutonoScriptModes GetMode();

      void SetMode(AutonoScriptModes mode);
      void SetFile(const char* file);
      void SetOutputFile(const char* file);
      void SetTeam(const char* team);
      void SetOutputType(const char* outputType);
      void SetPosition(int position);
      AutonoScriptInput* Seal();

    private:
      int _isValid;
      char* _file;
      char* _outputFile;
      int _isSealed;
      char* _team;
      int _position;
      char* _outputType;

      AutonoScriptModes _mode;

      void Validate();
      void SetStringInputValue(char** destination, const char* source);
  };
}

#endif
