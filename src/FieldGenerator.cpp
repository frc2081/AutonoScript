#include "FieldGenerator.h"

namespace AutonoScript
{

  // Field Position
  FieldPosition::FieldPosition(double xCoordinate, double yCoordinate)
  {
    _xCoordinate = xCoordinate;
    _yCoordinate = yCoordinate;
  }

  double FieldPosition::GetXCoordinate()
  {
    return _xCoordinate;
  }

  double FieldPosition::GetYCoordinate()
  {
    return _yCoordinate;
  }


  // Field Facing
  FieldFacing::FieldFacing(double xCoordinate, double yCoordinate, double facing)
    : FieldPosition(xCoordinate, yCoordinate)
  {
    _facing = facing;
  }

  double FieldFacing::GetFacing()
  {
    return _facing;
  }


  // Field Generator
  FieldGenerator::FieldGenerator()
  {
  }

  FieldGenerator::~FieldGenerator()
  {
  }

  void FieldGenerator::Generate(FieldPositions position, RobotCommandCollection* commands, const char* outputFile)
  {
  }

  void FieldGenerator::GenerateFromFacing(FieldFacing* facing, RobotCommandCollection* commands, const char* outputFile)
  {
  }


  void FieldGenerator::GetFacingFromPosition(FieldPositions position, FieldFacing* facing)
  {
  }
}
