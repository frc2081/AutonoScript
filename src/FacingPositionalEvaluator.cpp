#include <math.h>
#include "FacingPositionalEvaluator.h"
#define PI 3.14159265

namespace AutonoScript
{
  FacingPositionalEvaluator::FacingPositionalEvaluator()
  {
  }

  FacingPositionalEvaluator::~FacingPositionalEvaluator()
  {
  }


  void FacingPositionalEvaluator::EvaluateMove(FieldFacing* initialFacing, FacingRegulator* regulator, int distance, double movementFacing, FieldFacing** nextFacing)
  {
    double currentFacing, adjustedFacing, theta;
    int currentX, currentY, adjacent, opposite, sector;
    int deltaX, deltaY, nextX, nextY;

    currentX = initialFacing->GetXCoordinate();
    currentY = initialFacing->GetYCoordinate();
    currentFacing = initialFacing->GetFacing();

    adjustedFacing = regulator->GetAdjustedFacing(movementFacing);
    theta = (adjustedFacing *PI/180);

    nextX = currentX + (distance * sin(theta));
    nextY = currentY + (distance * cos(theta));

    *nextFacing = new FieldFacing(nextX, nextY, currentFacing); 
  }

  void FacingPositionalEvaluator::EvaluateRotation(FieldFacing* initialFacing, FacingRegulator* regulator, double rotation, FieldFacing** nextFacing)
  {
    double currentFacing, adjustedFacing;
    int currentX, currentY;

    currentX = initialFacing->GetXCoordinate();
    currentY = initialFacing->GetYCoordinate();
    currentFacing = initialFacing->GetFacing();

    adjustedFacing = regulator->GetFacingValue(currentFacing + rotation);
    *nextFacing = new FieldFacing(currentX, currentY, adjustedFacing);
  }
}
