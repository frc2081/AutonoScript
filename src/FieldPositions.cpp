#include "FieldPositions.h"

namespace AutonoScript
{

  // Field Position
  FieldPosition::FieldPosition(int xCoordinate, int yCoordinate)
  {
    _xCoordinate = xCoordinate;
    _yCoordinate = yCoordinate;
  }

  int FieldPosition::GetXCoordinate()
  {
    return _xCoordinate;
  }

  int FieldPosition::GetYCoordinate()
  {
    return _yCoordinate;
  }


  // Field Facing
  FieldFacing::FieldFacing(int xCoordinate, int yCoordinate, double facing)
    : FieldPosition(xCoordinate, yCoordinate)
  {
    _facing = facing;
  }

  FieldFacing* FieldFacing::Clone()
  {
    return new FieldFacing(GetXCoordinate(), GetYCoordinate(), GetFacing());
  }

  double FieldFacing::GetFacing()
  {
    return _facing;
  }
}
