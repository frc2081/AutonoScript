#ifndef FIELD_CSV_OGEN_H
#define FIELD_CSV_OGEN_H 1

#include "FieldOutputGenerator.h"

namespace AutonoScript
{
  class FieldCsvOutputGenerator : public FieldOutputGenerator
  {
    public:
      FieldCsvOutputGenerator(FieldDefinition* field);
      virtual void GenerateOutput(FieldPath* path, const char* outputFile);
  };
}

#endif
