#include <cmath>
#include "FacingRegulator.h"

namespace AutonoScript
{
  using namespace std;
  FacingRegulator::FacingRegulator(double initialGyroFacing)
  {
    _initialGyroFacing = initialGyroFacing;
  }

  FacingRegulator::~FacingRegulator()
  {
    _initialGyroFacing = 0;
  }

  double FacingRegulator::GetAdjustedFacing(double facing)
  {
    return GetFacingValue(facing + _initialGyroFacing);
  }

  double FacingRegulator::GetFacingValue(double value)
  {
    double val;

    return (val = fmod(value, 360)) >= 0
      ? val
      : 360 + val;
  }

}
