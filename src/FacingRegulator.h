#ifndef FACING_REGULATOR_H
#define FACING_REGULATOR_H 1

namespace AutonoScript
{
  class FacingRegulator
  {
    public:
      FacingRegulator();
      virtual ~FacingRegulator();

      double GetAdjustedFacing(double currentFacing, double movementFacing);
      double GetFacingValue(double value);

    private:

  };
}

#endif
