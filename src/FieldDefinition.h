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
      unsigned int _xLimit;
      unsigned int _yLimit;

      unsigned int _portalHeight;
      unsigned int _exchangeHeight;
      unsigned int _alianceStationHeight;
      unsigned int _playerStationHeight;

      unsigned int _alianceStationWidth;

      FieldFacing* _red1;
      FieldFacing* _red2;
      FieldFacing* _red3;
      FieldFacing* _blue1;
      FieldFacing* _blue2;
      FieldFacing* _blue3;

      unsigned int GetStartingPositionXCoordinate(unsigned int position, bool inverted);
      unsigned int GetStartingPositionYCoordinate(bool inverted);

      int GetRelativeValue(unsigned int value, bool inverted);
      void SetStartingFieldFacings();
  };
}
#endif
