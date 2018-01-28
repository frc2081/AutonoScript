#ifndef FIELD_PATH_GENERATOR_H
#define FIELD_PATH_GENERATOR_H 1

#include "FacingRegulator.h"
#include "FacingPositionalEvaluator.h"
#include "FieldPath.h"

namespace AutonoScript
{
  class FieldPathGenerator
  {
    public:
      FieldPathGenerator();
      virtual ~FieldPathGenerator();

      FieldPath* GeneratePath(FieldFacing* initialFacing, RobotCommandCollection* commands);

    private:
      FacingPositionalEvaluator* _facingEvaluator;

      void GetNextFacing(FieldFacing* current, FacingRegulator* regulator, RobotCommand* command, FieldFacing** next);
      void GetNextMoveFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, double moveFacing, FieldFacing** next);
      void GetNextRotationFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, FieldFacing** next);
  };
}
#endif
