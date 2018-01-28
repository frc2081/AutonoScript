#ifndef FIELD_GRAPHICS_OGEN_H
#define FIELD_GRAPHICS_OGEN_H 1

#include "FieldOutputGenerator.h"

namespace AutonoScript
{
  class FieldGraphicsOutputGenerator : public FieldOutputGenerator
  {
    public:
      FieldGraphicsOutputGenerator(FieldDefinition* field);
      virtual void GenerateOutput(FieldPath* path, const char* outputFile);
  };
}

#endif
