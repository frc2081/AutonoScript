#include <stdlib.h>
#include "FieldOutputGenerator.h"

namespace AutonoScript
{
  FieldOutputGenerator::FieldOutputGenerator(FieldDefinition* field)
  {
    _field = field;
  }

  FieldOutputGenerator::~FieldOutputGenerator()
  {
    _field = NULL;
  }

  FieldDefinition* FieldOutputGenerator::GetField()
  {
    return _field;
  }

}
