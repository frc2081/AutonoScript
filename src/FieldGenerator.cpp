#include <stdlib.h>
#include <stdio.h>
#include "FieldGenerator.h"
#include "FacingRegulator.h"

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
    double tmp;
    FacingRegulator* regulator = new FacingRegulator(facing->GetFacing());

    tmp = regulator->GetAdjustedFacing(0);
    tmp = regulator->GetAdjustedFacing(90);
    tmp = regulator->GetAdjustedFacing(180);
    tmp = regulator->GetAdjustedFacing(270);
    tmp = regulator->GetAdjustedFacing(355);
    
    delete regulator;
  }
}
