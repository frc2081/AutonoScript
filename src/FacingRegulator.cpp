#include <cmath>
#include "FacingRegulator.h"

namespace AutonoScript
{
  using namespace std;
  FacingRegulator::FacingRegulator()
  {
  }

  FacingRegulator::~FacingRegulator()
  {
  }

  double FacingRegulator::GetAdjustedFacing(double currentFacing, double movementFacing)
  {
    return GetFacingValue(currentFacing + movementFacing);
  }

  double FacingRegulator::GetFacingValue(double value)
  {
    double val;

    return (val = fmod(value, 360)) >= 0
      ? val
      : 360 + val;
  }

}
