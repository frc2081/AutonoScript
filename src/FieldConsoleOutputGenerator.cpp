#include <stdio.h>
#include "FieldConsoleOutputGenerator.h"

namespace AutonoScript
{
  FieldConsoleOutputGenerator::FieldConsoleOutputGenerator(FieldDefinition* field)
    : FieldOutputGenerator(field)
  {
  }
  
  void FieldConsoleOutputGenerator::GenerateOutput(FieldPath* path, const char* outputFile)
  {
    int pointCount;

    pointCount = path->GetPointCount();
    for(int i=0; i<pointCount; i++)
    {
      FieldFacing* facing = path->GetPoint(i);
      printf("(%d, %d) [%f]\n", facing->GetXCoordinate(), facing->GetYCoordinate(), facing->GetFacing());
    }
  }
}
