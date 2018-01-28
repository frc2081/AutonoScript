#include <stdio.h>
#include "FieldCsvOutputGenerator.h"

using namespace std;

namespace AutonoScript
{

  FieldCsvOutputGenerator::FieldCsvOutputGenerator(FieldDefinition* field)
    : FieldOutputGenerator(field)
  {
  }

  void FieldCsvOutputGenerator::GenerateOutput(FieldPath* path, const char* outputFile)
  {
    int pointCount;
    FILE* csvFile;

    csvFile = fopen(outputFile, "w");
    fprintf(csvFile, "X-Coordinate, Y-Coordinate, Facing");

    pointCount = path->GetPointCount();
    for(int i=0; i<pointCount; i++)
    {
      int x, y;
      double facing;
      FieldFacing* point;
      point = path->GetPoint(i);

      x = point->GetXCoordinate();
      y = point->GetYCoordinate();
      facing = point->GetFacing();

      fprintf(csvFile, "\n%d, %d, %0.2f", x, y, facing);
    }

    fclose(csvFile);
  }
}
