#ifndef FACING_POSIT_EVAL_H
#define FACING_POSIT_EVAL_H 1

#include "FieldPositions.h"
#include "FacingRegulator.h"

namespace AutonoScript
{
  class FacingPositionalEvaluator
  {
    public:
      FacingPositionalEvaluator();
      virtual ~FacingPositionalEvaluator();

      void EvaluateMove(FieldFacing* initialFacing, FacingRegulator* regulator, int distance, double movementFacing, FieldFacing** nextFacing);
      void EvaluateRotation(FieldFacing* initialFacing, FacingRegulator* regulator, double rotation, FieldFacing** nextFacing);
  };
}
#endif
