#include <stdlib.h>
#include <stdio.h>
#include "FieldGenerator.h"

namespace AutonoScript
{

  static inline void PrintFacing(FieldFacing* facing);
  FieldGenerator::FieldGenerator(FieldDefinition* fieldDefinition)
  {
    _fieldDefinition = fieldDefinition;
    _pathGenerator = new FieldPathGenerator();
  }

  FieldGenerator::~FieldGenerator()
  {
    _fieldDefinition = NULL;
    delete _pathGenerator;
  }

  void FieldGenerator::Generate(FieldPositions position, RobotCommandCollection* commands, const char* outputFile)
  {
    FieldFacing* facing;
    facing = _fieldDefinition->GetFacingFromPosition(position);

    GenerateFromFacing(facing, commands, outputFile);
  }

  void FieldGenerator::GenerateFromFacing(FieldFacing* facing, RobotCommandCollection* commands, const char* outputFile)
  {
    FieldPath* path;
    int pointCount;
    path = _pathGenerator->GeneratePath(facing, commands);
    pointCount = path->GetPointCount();

    for (int i=0; i<pointCount; i++)
      PrintFacing(path->GetPoint(i));

    delete path;
  }


  static inline void PrintFacing(FieldFacing* facing)
  {
    printf("Starting Position:\n  (%d, %d) [%f]\n", facing->GetXCoordinate(), facing->GetYCoordinate(), facing->GetFacing());
  }
}
