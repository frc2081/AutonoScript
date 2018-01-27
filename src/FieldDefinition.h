#ifndef FIELD_DEFINITION_H
#define FIELD_DEFINITION_H

#include "FieldPositions.h"

namespace AutonoScript
{
  class FieldDefinition
  {
    public:
      FieldDefinition();
      virtual ~FieldDefinition();

      FieldFacing* GetFacingFromPosition(FieldPositions position);
      void GetDimensions(FieldPosition** topLeft, FieldPosition** topRight, FieldPosition** bottomLeft, FieldPosition** bottomRight);
      bool IsInBounds(FieldPosition* position);

     private:
      int _xLimit;
      int _yLimit;

      int _portalHeight;
      int _exchangeHeight;
      int _alianceStationHeight;
      int _playerStationHeight;

      int _alianceStationWidth;

      FieldFacing* _red1;
      FieldFacing* _red2;
      FieldFacing* _red3;
      FieldFacing* _blue1;
      FieldFacing* _blue2;
      FieldFacing* _blue3;

      int GetStartingPositionXCoordinate(int position, bool inverted);
      int GetStartingPositionYCoordinate(bool inverted);

      int GetRelativeValue(int value, bool inverted);
      void SetStartingFieldFacings();
  };
}
#endif
