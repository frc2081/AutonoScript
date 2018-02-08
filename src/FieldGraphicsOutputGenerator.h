#ifndef FIELD_GRAPHICS_OGEN_H
#define FIELD_GRAPHICS_OGEN_H 1

#include <cairo.h>
#include "FieldOutputGenerator.h"

namespace AutonoScript
{
  class FieldGraphicsOutputGenerator : public FieldOutputGenerator
  {
    public:
      FieldGraphicsOutputGenerator(FieldDefinition* field);
      virtual void GenerateOutput(FieldPath* path, const char* outputFile);

		private:
      void DrawField(cairo_t* cr, FieldPosition* topLeft, FieldPosition* bottomRight);
      void DrawBounds(cairo_t* cr, FieldPosition* topLeft, FieldPosition* bottomRight);
			void DrawPath(cairo_t* cr, FieldPath* path, FieldPosition* topLeft, FieldPosition* bottomRight);
      void DrawRobot(cairo_t* cr, FieldFacing* vector, FieldPosition* topLeft, FieldPosition* bottomRight, bool isRed);
      void DrawScales(cairo_t* cr, int xAxis, int yAxis, int width, int height);
      void DrawPlatform(cairo_t* cr, int innerX, int innerY, int innerWidth, int innerHeight, int outerX, int outerY, int outerWidth, int outerHeight);
			cairo_surface_t* BuildSurface(FieldPosition* topLeft, FieldPosition* bottomRight);
  };
}

#endif
