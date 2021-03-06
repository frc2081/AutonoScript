#ifndef FIELD_GENERATOR_H
#define FIELD_GENERATOR_H 1

#include "RobotCommandCollection.h"
#include "FieldPositions.h"
#include "FieldDefinition.h"
#include "FieldPathGenerator.h"
#include "FieldOutputGenerator.h"

namespace AutonoScript
{
  class FieldGenerator
  {
    public:
      FieldGenerator(FieldDefinition* fieldDefinition, FieldOutputGenerator* io);
      virtual ~FieldGenerator();
      void Generate(FieldPositions position, RobotCommandCollection* commands, const char* outputFile);
      void GenerateFromFacing(FieldFacing* facing, RobotCommandCollection* commands, const char* outputFile);

    private:
      FieldDefinition* _fieldDefinition;
      FieldPathGenerator* _pathGenerator;
      FieldOutputGenerator* _io;
  };
}

#endif
