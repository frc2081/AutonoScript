#ifndef FIELD_OUTPUT_GENERATOR_H
#define FIELD_OUTPUT_GENERATOR_H 1

#include "FieldPath.h"
#include "FieldDefinition.h"

namespace AutonoScript
{
  class FieldOutputGenerator
  {
    public:
      FieldOutputGenerator(FieldDefinition* field);
      virtual ~FieldOutputGenerator();

      virtual void GenerateOutput(FieldPath* path, const char* outputFile) = 0;

    protected:
      FieldDefinition* GetField();

    private:
      FieldDefinition* _field;
  };
}
#endif
