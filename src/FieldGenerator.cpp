#include <stdlib.h>
#include <stdio.h>
#include "FieldGenerator.h"

namespace AutonoScript
{

  static inline void PrintFacing(FieldFacing* facing);
  FieldGenerator::FieldGenerator(FieldDefinition* fieldDefinition)
  {
    _fieldDefinition = fieldDefinition;
    _facingEvaluator = new FacingPositionalEvaluator();
  }

  FieldGenerator::~FieldGenerator()
  {
    _fieldDefinition = NULL;
    delete _facingEvaluator;
  }

  void FieldGenerator::Generate(FieldPositions position, RobotCommandCollection* commands, const char* outputFile)
  {
    FieldFacing* facing;
    facing = _fieldDefinition->GetFacingFromPosition(position);

    GenerateFromFacing(facing, commands, outputFile);
  }

  void FieldGenerator::GenerateFromFacing(FieldFacing* facing, RobotCommandCollection* commands, const char* outputFile)
  {
    double tmp;
    int commandCount;
    FacingRegulator* regulator = new FacingRegulator(facing->GetFacing());
    FieldFacing* currentFacing, *nextFacing;

    currentFacing = facing->Clone();
    commandCount = commands->GetCommandCount();
    for (int i=0; i<commandCount; i++)
    {
      PrintFacing(currentFacing);
      RobotCommand* command = commands->GetCommand(i);
      GetNextFacing(currentFacing, regulator, command, &nextFacing);
      delete(currentFacing);
      currentFacing = nextFacing;
    }

    
    PrintFacing(currentFacing);
    delete currentFacing;
    delete regulator;
  }

  void FieldGenerator::GetNextFacing(FieldFacing* current, FacingRegulator* regulator, RobotCommand* command, FieldFacing** next)
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
        nextMagnitude *= -1;

      GetNextRotationFacing(current, regulator, nextMagnitude, next);
      return;
    }
  }

  void FieldGenerator::GetNextMoveFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, double moveFacing, FieldFacing** next)
  {
    double meters;
    int distance, nextX, nextY;

    // AutonoSCript is in meters.
    // Translate to CM.
    meters = magnitude;
    distance = (int)(meters * 100);

    _facingEvaluator->EvaluateMove(current, regulator, distance, moveFacing, next);
  }

  void FieldGenerator::GetNextRotationFacing(FieldFacing* current, FacingRegulator* regulator, double magnitude, FieldFacing** next)
  {
    _facingEvaluator->EvaluateRotation(current, regulator, magnitude, next);
  }

  static inline void PrintFacing(FieldFacing* facing)
  {
    printf("Starting Position:\n  (%d, %d) [%f]\n", facing->GetXCoordinate(), facing->GetYCoordinate(), facing->GetFacing());
  }
}
