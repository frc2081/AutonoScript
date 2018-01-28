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
      double ChangeRobotFacing(double ammount);

    private:
      double _initialGyroFacing;
      double _currentRobotFacing;

      double GetFacingValue(double value);
  };
}

#endif
