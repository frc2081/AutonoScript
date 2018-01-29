#include <cairo.h>
#include "FieldGraphicsOutputGenerator.h"

using namespace std;

namespace AutonoScript
{

  FieldGraphicsOutputGenerator::FieldGraphicsOutputGenerator(FieldDefinition* field)
    : FieldOutputGenerator(field)
  {
  }

  void FieldGraphicsOutputGenerator::GenerateOutput(FieldPath* path, const char* outputFile)
  {
		cairo_t* cr;
		cairo_surface_t* surface;

		FieldDefinition* field;
		FieldPosition *topLeft, *topRight, *bottomLeft, *bottomRight;

		field = GetField();
		field->GetDimensions(&topLeft, &topRight, &bottomLeft, &bottomRight);

		surface = BuildSurface(topLeft, bottomRight);
		cr = cairo_create(surface);

    // Draw the field.
    DrawField(cr, topLeft, bottomRight);

    // Draw the path of the robot.
    DrawPath(cr, path, topLeft);


		cairo_destroy (cr);
		cairo_surface_write_to_png (surface, outputFile);
		cairo_surface_destroy (surface);

		delete topLeft;
		delete topRight;
		delete bottomLeft;
		delete bottomRight;
  }

	cairo_surface_t* FieldGraphicsOutputGenerator::BuildSurface(FieldPosition* topLeft, FieldPosition* bottomRight)
	{

		int height, width;

		height = topLeft->GetYCoordinate();
		width = bottomRight->GetXCoordinate();

		return cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
	}

#define GET_CAIRO_PATH_POINTS(curr_point, topY) curr_point->GetXCoordinate(), (topY - curr_point->GetYCoordinate())
	void FieldGraphicsOutputGenerator::DrawPath(cairo_t* cr, FieldPath* path, FieldPosition* topLeft)
  {
    int pointCount, topCoordinate;

    FieldFacing* currentPoint;
    currentPoint = (*path)[0];
    topCoordinate = topLeft->GetYCoordinate();

    cairo_move_to(cr, GET_CAIRO_PATH_POINTS(currentPoint, topCoordinate));
    pointCount = path->GetPointCount();
    for (int i=1; i<pointCount; i++)
    {
      currentPoint = path->GetPoint(i);
      cairo_line_to(cr, GET_CAIRO_PATH_POINTS(currentPoint, topCoordinate));
    }

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_source_rgba(cr, 1.0, 0, 0, 0.75);
    cairo_set_line_width(cr, 4.0);
    cairo_stroke(cr);
  }

  void FieldGraphicsOutputGenerator::DrawField(cairo_t* cr, FieldPosition* topLeft, FieldPosition* bottomRight)
  {
    // Draw background.
    cairo_rectangle(cr, 0, 0, bottomRight->GetXCoordinate(), topLeft->GetYCoordinate()); 
    cairo_set_source_rgb(cr, 0.52, 0.51, 0.56);
    cairo_fill(cr);

    DrawBounds(cr, topLeft, bottomRight);

    // Give a border.
    cairo_rectangle(cr, 0, 0, bottomRight->GetXCoordinate(), topLeft->GetYCoordinate()); 
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 5);
    cairo_stroke(cr);

  }

  void FieldGraphicsOutputGenerator::DrawBounds(cairo_t* cr, FieldPosition* topLeft, FieldPosition* bottomRight)
  {
    int maxHeight, maxWidth;
    int topBoundWidth, sideBoundHeight;
    int boundSlantHeight, boundSlantWidth;
    int boundTotalHeight, boundTotalWidth;
    int boundCenterX, boundCenterY;
    int boundTopLeftX, boundTopLeftY;
     

    maxHeight = topLeft->GetYCoordinate();
    maxWidth = bottomRight->GetXCoordinate();

    sideBoundHeight = 670;
    boundSlantHeight = 74;
    boundSlantWidth = 91;
    boundTotalWidth = 1646;

    topBoundWidth = boundTotalWidth - (2 * boundSlantWidth);
    boundTotalHeight = sideBoundHeight + (2 * boundSlantHeight);

    boundCenterX = maxWidth / 2;
    boundCenterY = maxHeight / 2;

    boundTopLeftY = maxHeight - (boundCenterY + (boundTotalHeight / 2));
    boundTopLeftX = maxWidth - (boundCenterX + (boundTotalWidth / 2));

    // Draw white bounds
    cairo_move_to(cr, boundTopLeftX,                                    boundTopLeftY + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX,                                    boundTopLeftY + sideBoundHeight + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth,                  boundTopLeftY + boundTotalHeight);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth + topBoundWidth,  boundTopLeftY + boundTotalHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth,                  boundTopLeftY + boundSlantHeight + sideBoundHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth,                  boundTopLeftY + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth + topBoundWidth,  boundTopLeftY);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth,                  boundTopLeftY);
    cairo_close_path(cr);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_set_line_width(cr, 3);
    cairo_stroke(cr);
  }
}
