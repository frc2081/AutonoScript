#include <cmath>
#include "FacingRegulator.h"

namespace AutonoScript
{
  using namespace std;
  FacingRegulator::FacingRegulator(double initialGyroFacing)
  {
    _initialGyroFacing = initialGyroFacing;
    _currentRobotFacing = 0;
  }

  FacingRegulator::~FacingRegulator()
  {
    _initialGyroFacing = 0;
    _currentRobotFacing = 0;
  }

  double FacingRegulator::GetAdjustedFacing(double facing)
  {
    return GetFacingValue(facing + _initialGyroFacing);
  }

  double FacingRegulator::ChangeRobotFacing(double ammount)
  {
    _currentRobotFacing = GetFacingValue(_currentRobotFacing + ammount);
  }

  double FacingRegulator::GetFacingValue(double value)
  {
    return abs(fmod(value, 360));
  }

}
