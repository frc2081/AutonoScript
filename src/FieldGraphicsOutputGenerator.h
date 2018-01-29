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
			void DrawPath(cairo_t* cr, FieldPath* path);
			cairo_surface_t* BuildSurface(FieldPosition* topLeft, FieldPosition* bottomRight);
  };
}

#endif
