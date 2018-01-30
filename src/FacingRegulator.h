#ifndef FACING_REGULATOR_H
#define FACING_REGULATOR_H 1

namespace AutonoScript
{
  class FacingRegulator
  {
    public:
      FacingRegulator(double initalGyroFacing);
      virtual ~FacingRegulator();

      double GetAdjustedFacing(double facing);
      double GetFacingValue(double value);

    private:
      double _initialGyroFacing;

  };
}

#endif
