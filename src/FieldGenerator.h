#ifndef FIELD_GENERATOR_H
#define FIELD_GENERATOR_H 1

#include "RobotCommandCollection.h"
#include "FieldPositions.h"
#include "FieldDefinition.h"
#include "FacingRegulator.h"
#include "FacingPositionalEvaluator.h"

namespace AutonoScript
{
  class FieldGenerator
  {
    public:
      FieldGenerator(FieldDefinition* fieldDefinition);
      virtual ~FieldGenerator();
      void Generate(FieldPositions position, RobotCommandCollection* commands, const char* outputFile);
      void GenerateFromFacing(FieldFacing* facing, RobotCommandCollection* commands, const char* outputFile);

    private:
      FieldDefinition* _fieldDefinition;
      FacingPositionalEvaluator* _facingEvaluator;

      void GetNextFacing(FieldFacing* current, FacingRegulator* regulator, RobotCommand* command, FieldFacing** next);
      void GetNextMoveFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, double moveFacing, FieldFacing** next);
      void GetNextRotationFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, FieldFacing** next);
  };
}

#endif
