#include <stdlib.h>
#include <stdio.h>
#include "FieldGenerator.h"

namespace AutonoScript
{

  FieldGenerator::FieldGenerator(FieldDefinition* fieldDefinition)
  {
    _fieldDefinition = fieldDefinition;
  }

  FieldGenerator::~FieldGenerator()
  {
    _fieldDefinition = NULL;
  }

  void FieldGenerator::Generate(FieldPositions position, RobotCommandCollection* commands, const char* outputFile)
  {
    FieldFacing* facing;
    facing = _fieldDefinition->GetFacingFromPosition(position);

    GenerateFromFacing(facing, commands, outputFile);
  }

  void FieldGenerator::GenerateFromFacing(FieldFacing* facing, RobotCommandCollection* commands, const char* outputFile)
  {
    printf("Starting Position:\n  (%d, %d) [%f]\n", facing->GetXCoordinate(), facing->GetYCoordinate(), facing->GetFacing());
  }
}
