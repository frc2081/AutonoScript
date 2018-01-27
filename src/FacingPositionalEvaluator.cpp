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
    double currentFacing, adjustedFacing;
    int currentX, currentY, adjacent, opposite, sector;
    int deltaX, deltaY, nextX, nextY;

    currentX = initialFacing->GetXCoordinate();
    currentY = initialFacing->GetYCoordinate();
    currentFacing = initialFacing->GetFacing();

    adjustedFacing = regulator->GetAdjustedFacing(movementFacing);
    GetMovementComponents(adjustedFacing, distance, &adjacent, &opposite, &sector);

    switch (sector)
    {
      case 0:
        deltaX = adjacent;
        deltaY = opposite;
        break;

      case 1:
        deltaX = opposite;
        deltaY = -1 * adjacent;
        break;

      case 2:
        deltaX = -1 * adjacent;
        deltaY = -1 * opposite;
        break;

      case 3:
        deltaX = -1 * opposite;
        deltaY = adjacent;
        break;
    }

    nextX = currentX + deltaX;
    nextY = currentY + deltaY;

    *nextFacing = new FieldFacing(nextX, nextY, currentFacing); 
  }

  void FacingPositionalEvaluator::EvaluateRotation(FieldFacing* initialFacing, FacingRegulator* regulator, double rotation, FieldFacing** nextFacing)
  {
    double currentFacing, adjustedFacing;
    int currentX, currentY;

    currentX = initialFacing->GetXCoordinate();
    currentY = initialFacing->GetYCoordinate();
    currentFacing = initialFacing->GetFacing();

    adjustedFacing = regulator->GetAdjustedFacing(regulator->ChangeRobotFacing(rotation));
    
    *nextFacing = new FieldFacing(currentX, currentY, adjustedFacing);
  }

  void FacingPositionalEvaluator::GetMovementComponents(double adjustedFacing, int distance, int* adjacent, int* opposite, int* sector)
  {
    double thetaDegrees, theta;

    *opposite = *adjacent = 0;
    thetaDegrees = (90 - fmod(adjustedFacing, 90));

    theta = (thetaDegrees*PI/180);
    *opposite = distance * sin(theta);
    *adjacent = distance * cos(theta);

    *sector = (int)(fmod(adjustedFacing, 360) / 90);
  }
}
