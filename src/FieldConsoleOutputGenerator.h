#ifndef FIELD_CONSOLE_OGEN_H
#define FIELD_CONSOLE_OGEN_H 1

#include "FieldOutputGenerator.h"

namespace AutonoScript
{
  class FieldConsoleOutputGenerator : public FieldOutputGenerator
  {
    public:
      FieldConsoleOutputGenerator(FieldDefinition* field);
      virtual void GenerateOutput(FieldPath* path, const char* outputFile);
  };
}

#endif
