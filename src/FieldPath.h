#ifndef FIELD_PATH_H
#define FIELD_PATH_H 1

#include <vector>
#include "FieldPositions.h"

namespace AutonoScript
{
  class FieldPath
  {
    public:
      // Constructor | Destructor
      FieldPath();
      virtual ~FieldPath();

      // Public Methods
      void AddPoint(int xCoordinate, int yCoordinate, double facing);
      FieldFacing* GetPoint(int index);
      int GetPointCount();
     
      // Overloads
      FieldFacing* operator[] (int index)
      {
        return GetPoint(index);
      }

    private:
      std::vector<FieldFacing*>* _points;
  };
}

#endif
