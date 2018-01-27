#include "FieldPositions.h"

namespace AutonoScript
{

  // Field Position
  FieldPosition::FieldPosition(unsigned int xCoordinate, unsigned int yCoordinate)
  {
    _xCoordinate = xCoordinate;
    _yCoordinate = yCoordinate;
  }

  unsigned int FieldPosition::GetXCoordinate()
  {
    return _xCoordinate;
  }

  unsigned int FieldPosition::GetYCoordinate()
  {
    return _yCoordinate;
  }


  // Field Facing
  FieldFacing::FieldFacing(unsigned int xCoordinate, unsigned int yCoordinate, double facing)
    : FieldPosition(xCoordinate, yCoordinate)
  {
    _facing = facing;
  }

  double FieldFacing::GetFacing()
  {
    return _facing;
  }
}
