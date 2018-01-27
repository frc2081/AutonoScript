
#ifndef FIELD_POSITIONS_H
#define FIELD_POSITIONS_H 1

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
      FieldPosition(unsigned int xCoordinate, unsigned int yCoordinate);

      unsigned int GetXCoordinate();
      unsigned int GetYCoordinate();

    private:
      unsigned int _xCoordinate;
      unsigned int _yCoordinate;
  };

  class FieldFacing : public FieldPosition
  {
    public:
      FieldFacing(unsigned int xCoordinate, unsigned int yCoordinate, double facing);

      double GetFacing();

    private:
      double _facing;

  };
}

#endif
