#include <stdlib.h>
#include "FieldDefinition.h"

namespace AutonoScript
{
  // TODO: Replace with an abstract class, and eventually add a provider.
  FieldDefinition::FieldDefinition()
  {
    _xLimit = 2255;
    _portalHeight = 122;
    _exchangeHeight = 122;
    _alianceStationHeight = 671;

    _alianceStationWidth = 305;

    _playerStationHeight = (_alianceStationHeight - _exchangeHeight) / 3;
    _yLimit = (2 * _portalHeight) + _alianceStationHeight;

    SetStartingFieldFacings();
  }

  FieldDefinition::~FieldDefinition()
  {
    _xLimit = 0;
    _yLimit = 0;
    _portalHeight = 0;
    _exchangeHeight = 0;
    _alianceStationHeight = 0;
    _playerStationHeight = 0;

    delete _red1;
    delete _red2;
    delete _red3;
    delete _blue1;
    delete _blue2;
    delete _blue3;
  }

  FieldFacing* FieldDefinition::GetFacingFromPosition(FieldPositions position)
  {
    
    switch(position)
    {
      case RedTeam1:
        return _red1;

      case RedTeam2:
        return _red2;

      case RedTeam3:
        return _red3;

      case BlueTeam1:
        return _blue1;

      case BlueTeam2:
        return _blue2;

      case BlueTeam3:
        return _blue3;
      
      default:
        return NULL;
    }
  }

  void FieldDefinition::GetDimensions(FieldPosition** topLeft, FieldPosition** topRight, FieldPosition** bottomLeft, FieldPosition** bottomRight)
  {
    *topLeft = new FieldPosition(0, _yLimit);
    *topRight = new FieldPosition(_xLimit, _yLimit);
    *bottomLeft = new FieldPosition(0, 0);
    *bottomRight = new FieldPosition(_xLimit, 0);
  }

  bool FieldDefinition::IsInBounds(FieldPosition* position)
  {
    int x, y;
    x = position->GetXCoordinate();
    y = position->GetYCoordinate();

    return x >= 0
      && x <= _xLimit
      && y >= 0
      && y <= _yLimit;
  }

  int FieldDefinition::GetStartingPositionYCoordinate(int position, bool inverted)
  {
    int height = inverted
      ? _yLimit
      : 0;

    height += GetRelativeValue(_portalHeight, inverted);
    height += GetRelativeValue(_playerStationHeight * position, inverted);

    if (position > 1)
      height += GetRelativeValue(_exchangeHeight, inverted);

    height -= (GetRelativeValue(_playerStationHeight / 2, inverted));

    return height;
  }

  int FieldDefinition::GetStartingPositionXCoordinate(bool inverted)
  {
    return inverted
      ? _alianceStationWidth
      : _xLimit - _alianceStationWidth;
  }

  int FieldDefinition::GetRelativeValue(int value, bool inverted)
  {
    return inverted
      ?  -1 * (int)value
      : (int) value;
  }

#define CreateFacing(position, inverted, facing) new FieldFacing(GetStartingPositionXCoordinate(inverted), GetStartingPositionYCoordinate(position, inverted), facing);
  void FieldDefinition::SetStartingFieldFacings()
  {
    double redFacing = 90;
    double blueFacing = 270;

    _red1 = CreateFacing(1, true, redFacing);
    _red2 = CreateFacing(2, true, redFacing);
    _red3 = CreateFacing(3, true, redFacing);

    _blue1 = CreateFacing(1, false, blueFacing);
    _blue2 = CreateFacing(2, false, blueFacing);
    _blue3 = CreateFacing(3, false, blueFacing);
  }
}
