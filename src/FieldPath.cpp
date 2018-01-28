#include "FieldPath.h"

using namespace std;
namespace AutonoScript
{
  FieldPath::FieldPath()
  {
    _points = new vector<FieldFacing*>();
  }

  FieldPath::~FieldPath()
  {
    int i, count = GetPointCount();
    for (i=0; i<count; i++)
      delete GetPoint(i);

    delete _points;
  }

  void FieldPath::AddPoint(int xCoordinate, int yCoordinate, double facing)
  {
    _points->push_back(new FieldFacing(xCoordinate, yCoordinate, facing));
  }

  FieldFacing* FieldPath::GetPoint(int index)
  {
    return _points->at(index);
  }

  int FieldPath::GetPointCount()
  {
    return _points->size();
  }
}
