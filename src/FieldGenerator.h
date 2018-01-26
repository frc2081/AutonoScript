#ifndef FIELD_GENERATOR_H
#define FIELD_GENERATOR_H 1

#include "RobotCommandCollection.h"

namespace AutonoScript
{
  enum FieldPositions
  {
    UnknownPosition = 0x0,
    RedTeam = 0x1,
    BlueTeam = 0x2,
    Position1 = 0x4,
    Position2 = 0x8,
    Position3 = 0x10,

    RedTeam1  = RedTeam | Position1,
    RedTeam2  = RedTeam | Position2,
    RedTeam3  = RedTeam | Position3,
    BlueTeam1 = BlueTeam | Position1,
    BlueTeam2 = BlueTeam | Position2,
    BlueTeam3 = BlueTeam | Position3
  };

  class FieldPosition
  {
    public:
      FieldPosition(double xCoordinate, double yCoordinate);

      double GetXCoordinate();
      double GetYCoordinate();

    private:
      double _xCoordinate;
      double _yCoordinate;
  };

  class FieldFacing : public FieldPosition
  {
    public:
      FieldFacing(double xCoordinate, double yCoordinate, double facing);

      double GetFacing();

    private:
      double _facing;

  };

  class FieldGenerator
  {
    public:
      FieldGenerator();
      virtual ~FieldGenerator();
      void Generate(FieldPositions position, RobotCommandCollection* commands, const char* outputFile);
      void GenerateFromFacing(FieldFacing* facing, RobotCommandCollection* commands, const char* outputFile);

    private:
      void GetFacingFromPosition(FieldPositions position, FieldFacing* facing);
  };
}

#endif
