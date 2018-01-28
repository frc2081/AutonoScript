#include <stdlib.h>
#include <stdio.h>
#include "FieldGenerator.h"

namespace AutonoScript
{

  static inline void PrintFacing(FieldFacing* facing);
  FieldGenerator::FieldGenerator(FieldDefinition* fieldDefinition, FieldOutputGenerator* io)
  {
    _fieldDefinition = fieldDefinition;
    _pathGenerator = new FieldPathGenerator();
    _io = io;
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

    _io->GenerateOutput(path, outputFile);
  }
}
