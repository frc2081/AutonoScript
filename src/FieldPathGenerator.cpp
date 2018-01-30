#include "FieldPathGenerator.h"

namespace AutonoScript
{
  FieldPathGenerator::FieldPathGenerator()
  {
    _facingEvaluator = new FacingPositionalEvaluator();
  }

  FieldPathGenerator::~FieldPathGenerator()
  {
    delete _facingEvaluator;
  }


#define ADD_POINT_TO_PATH(target_path,target_point) target_path->AddPoint(target_point->GetXCoordinate(), target_point->GetYCoordinate(), target_point->GetFacing());

  FieldPath* FieldPathGenerator::GeneratePath(FieldFacing* initialFacing, RobotCommandCollection* commands)
  {
    FieldPath* path;
    int commandCount;
    commandCount = commands->GetCommandCount();
    FacingRegulator* regulator = new FacingRegulator(initialFacing->GetFacing());

    FieldFacing* currentFacing, *nextFacing;
    currentFacing = initialFacing->Clone();

    path = new FieldPath();
    for (int i=0; i<commandCount; i++)
    {
      ADD_POINT_TO_PATH(path, currentFacing);
      RobotCommand* command = commands->GetCommand(i);
      GetNextFacing(currentFacing, regulator, command, &nextFacing);
      delete currentFacing;
      currentFacing = nextFacing;
      
    }

    ADD_POINT_TO_PATH(path, currentFacing);
    delete currentFacing;
    delete regulator;

    return path;
  }

  void FieldPathGenerator::GetNextFacing(FieldFacing* current, FacingRegulator* regulator, RobotCommand* command, FieldFacing** next)
  {
    RobotCommands commandType;
    double nextFacing, nextMagnitude;

    commandType = command->GetCommand();
    nextFacing = command->GetFacing();
    nextMagnitude = command->GetMagnitude();

    if (commandType == Move)
    {
      GetNextMoveFacing(current, regulator, nextMagnitude, nextFacing, next);
      return;
    }

    if (commandType == RotateClockwise || commandType == RotateCounterClockwise)
    {
      if (commandType == RotateCounterClockwise)
        nextMagnitude = nextMagnitude * -1;

      GetNextRotationFacing(current, regulator, nextMagnitude, next);
      return;
    }
  }

  void FieldPathGenerator::GetNextMoveFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, double moveFacing, FieldFacing** next)
  {
    double meters;
    int distance, nextX, nextY;

    // AutonoSCript is in meters.
    // Translate to CM.
    meters = magnitude;
    distance = (int)(meters * 100);

    _facingEvaluator->EvaluateMove(current, regulator, distance, moveFacing, next);
  }

  void FieldPathGenerator::GetNextRotationFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, FieldFacing** next)
  {
    _facingEvaluator->EvaluateRotation(current, regulator, magnitude, next);
  }

}
