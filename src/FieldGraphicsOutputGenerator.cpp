#include <math.h>
#include <cairo.h>
#include "FieldGraphicsOutputGenerator.h"

#define PI 3.14159265359

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
    DrawPath(cr, path, topLeft, bottomRight);

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
#define SET_TEAM_COLOR(bool_isRed)                  \
    if (isRed)                                      \
      cairo_set_source_rgba(cr, 0.8, 0, 0, 0.75);   \
    else                                            \
      cairo_set_source_rgba(cr, 0, 0, 1.0, 0.75);

	void FieldGraphicsOutputGenerator::DrawPath(cairo_t* cr, FieldPath* path, FieldPosition* topLeft, FieldPosition* bottomRight)
  {
    bool isRed;
    int pointCount, topMax, rightMax;
    double dashes[] = { 20, 20 };

    FieldFacing* currentPoint;
    currentPoint = (*path)[0];
    topMax = topLeft->GetYCoordinate();
    rightMax = bottomRight->GetXCoordinate();

    isRed = currentPoint->GetXCoordinate() < (rightMax / 2);
    cairo_move_to(cr, GET_CAIRO_PATH_POINTS(currentPoint, topMax));
    pointCount = path->GetPointCount();
    for (int i=1; i<pointCount; i++)
    {
      currentPoint = path->GetPoint(i);
      cairo_line_to(cr, GET_CAIRO_PATH_POINTS(currentPoint, topMax));
    }

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    SET_TEAM_COLOR(isRed);

    cairo_set_dash(cr, dashes, 2, -10);
    cairo_set_line_width(cr, 6);
    cairo_stroke(cr);

    // Draw the robot.
    DrawRobot(cr, (*path)[path->GetPointCount() -1], topLeft, bottomRight, isRed);
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
    int boundLeftAutoLineX, boundRightAutoLineX;
    int cubeZoneWidth, cubeZoneHeight;
    int exchangeZoneWidth, exchangeZoneHeight;
    int autoLineWidth;
    int playerStationHeight, playerStationWidth;
    int playerStationTopLeftX, playerStationTopRightX;
    int playerStationDeskWidth;
    int platformZoneWidth;
    int scaleWidth, scaleHeight;
    int scaleHeightOffset, scaleWidthOffset;
    int platformHeight, platformWidth;
    int platformHeightOffset, platformWidthOffset;
    int innerPlatformWidth, innerPlatformHeight;
    int nullTerritoryWidth;

    maxHeight = topLeft->GetYCoordinate();
    maxWidth = bottomRight->GetXCoordinate();

    sideBoundHeight = 670;
    boundSlantHeight = 74;
    boundSlantWidth = 91;
    boundTotalWidth = 1646;
    autoLineWidth = 305;
    cubeZoneWidth = 107;
    cubeZoneHeight = 114;
    exchangeZoneWidth = 91;
    exchangeZoneHeight = 122;
    playerStationHeight = 183;
    playerStationWidth = 71;
    scaleWidth = 142;
    scaleHeightOffset = 217;
    scaleWidthOffset = 356;
    platformHeightOffset = 242;
    platformWidthOffset = 664;
    nullTerritoryWidth = 183;

    topBoundWidth = boundTotalWidth - (2 * boundSlantWidth);
    boundTotalHeight = sideBoundHeight + (2 * boundSlantHeight);

    boundCenterX = maxWidth / 2;
    boundCenterY = maxHeight / 2;

    boundTopLeftY = maxHeight - (boundCenterY + (boundTotalHeight / 2));
    boundTopLeftX = maxWidth - (boundCenterX + (boundTotalWidth / 2));

    boundLeftAutoLineX = boundTopLeftX + autoLineWidth;
    boundRightAutoLineX = boundTopLeftX + boundTotalWidth - autoLineWidth;

    playerStationTopLeftX = boundTopLeftX - playerStationWidth;
    playerStationTopRightX = boundTopLeftX + boundTotalWidth + playerStationWidth;
    playerStationDeskWidth = playerStationWidth - 20;

    scaleHeight = boundTotalHeight - (2 * scaleHeightOffset);
    platformHeight = boundTotalHeight - (2 * platformHeightOffset);
    platformWidth = boundTotalWidth - (2 * platformWidthOffset);
    platformZoneWidth = (boundTotalWidth / 2) - scaleWidthOffset - scaleWidth;

    // TODO: Find the real metrics on this.
    innerPlatformWidth = platformWidth * 0.8;
    innerPlatformHeight = platformHeight * 0.8;

    // Draw lesser markings
    cairo_move_to(cr, 1, boundCenterY);
    cairo_line_to(cr, maxWidth - 1, boundCenterY);

    cairo_move_to(cr, boundCenterX, 0);
    cairo_line_to(cr, boundCenterX, maxHeight);

    cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
    cairo_set_line_width(cr, 2);
    cairo_stroke(cr);

    // Draw Autonomous Lines
    cairo_move_to(cr, boundLeftAutoLineX, boundTopLeftY);
    cairo_line_to(cr, boundLeftAutoLineX, boundTopLeftY + boundTotalHeight);

    cairo_move_to(cr, boundRightAutoLineX, boundTopLeftY);
    cairo_line_to(cr, boundRightAutoLineX, boundTopLeftY + boundTotalHeight);

    cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
    cairo_set_line_width(cr, 4);
    cairo_stroke(cr);

    // Draw Red Zones
    cairo_rectangle(cr, boundLeftAutoLineX - (cubeZoneWidth / 2), boundCenterY - (cubeZoneHeight / 2), cubeZoneWidth, cubeZoneHeight);
    cairo_rectangle(cr, boundTopLeftX, boundTopLeftY + boundSlantHeight + playerStationHeight, exchangeZoneWidth, exchangeZoneHeight);
    cairo_rectangle(cr, 0, boundTopLeftY + boundSlantHeight, boundTopLeftX, sideBoundHeight);

    cairo_move_to(cr, boundTopLeftX + boundTotalWidth - boundSlantWidth, boundTopLeftY);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth - boundSlantWidth, 0);
    cairo_line_to(cr, maxWidth, 0);
    cairo_line_to(cr, maxWidth, boundTopLeftY + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundSlantHeight);
    cairo_close_path(cr);

    cairo_move_to(cr, boundTopLeftX + boundTotalWidth - boundSlantWidth, boundTopLeftY + boundTotalHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth - boundSlantWidth, maxHeight);
    cairo_line_to(cr, maxWidth, maxHeight);
    cairo_line_to(cr, maxWidth, boundTopLeftY + boundSlantHeight + sideBoundHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundSlantHeight + sideBoundHeight);
    cairo_close_path(cr);

    cairo_rectangle(cr, boundTopLeftX + scaleWidthOffset + scaleWidth, boundTopLeftY + platformHeightOffset, platformZoneWidth, platformHeight);

    cairo_set_source_rgba(cr, 0.6, 0.1, 0.1, 0.25);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 0.6, 0.1, 0.1);
    cairo_set_line_width(cr, 4);
    cairo_stroke(cr);


    // Draw Blue Zones
    cairo_rectangle(cr, boundRightAutoLineX - (cubeZoneWidth / 2), boundCenterY - (cubeZoneHeight / 2), cubeZoneWidth, cubeZoneHeight);
    cairo_rectangle(cr, boundTopLeftX + boundTotalWidth - exchangeZoneWidth, boundTopLeftY + boundSlantHeight + (2 * playerStationHeight), exchangeZoneWidth, exchangeZoneHeight);
    cairo_rectangle(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundSlantHeight, boundTopLeftX, sideBoundHeight);

    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth, 0);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth, boundTopLeftY);
    cairo_line_to(cr, boundTopLeftX, boundTopLeftY + boundSlantHeight);
    cairo_line_to(cr, 0, boundTopLeftY + boundSlantHeight);
    cairo_close_path(cr);

    cairo_move_to(cr, 0, maxHeight);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth, maxHeight);
    cairo_line_to(cr, boundTopLeftX + boundSlantWidth, boundTopLeftY + boundTotalHeight);
    cairo_line_to(cr, boundTopLeftX, boundTopLeftY + boundSlantHeight + sideBoundHeight);
    cairo_line_to(cr, 0, boundTopLeftY + boundSlantHeight + sideBoundHeight);
    cairo_close_path(cr);

    cairo_rectangle(cr, boundCenterX, boundTopLeftY + platformHeightOffset, platformZoneWidth, platformHeight);

    cairo_set_source_rgba(cr, 0.1, 0.1, 0.6, 0.25);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 0.1, 0.1, 0.6);
    cairo_set_line_width(cr, 4);
    cairo_stroke(cr);

    // Draw Null Zones
    cairo_rectangle(cr, boundCenterX - (nullTerritoryWidth / 2), boundTopLeftY, nullTerritoryWidth, platformHeightOffset);
    cairo_rectangle(cr, boundCenterX - (nullTerritoryWidth / 2), boundTopLeftY + platformHeightOffset + platformHeight, nullTerritoryWidth, platformHeightOffset);

    cairo_set_source_rgba(cr, 0.6, 0.6, 0.1, 0.25);
    cairo_fill_preserve(cr);
    cairo_set_source_rgb(cr, 0.6, 0.6, 0.1);
    cairo_set_line_width(cr, 4);
    cairo_stroke(cr);

    // Draw Scales
    DrawScales(cr, boundTopLeftX + scaleWidthOffset, boundTopLeftY + scaleHeightOffset, scaleWidth, scaleHeight);
    DrawScales(cr, boundTopLeftX + boundTotalWidth - (scaleWidthOffset + scaleWidth), boundTopLeftY + scaleHeightOffset, scaleWidth, scaleHeight);

    // Draw platforms
    DrawPlatform(cr, boundTopLeftX + platformWidthOffset, boundTopLeftY + platformHeightOffset, platformWidth, platformHeight,
      boundCenterX - (innerPlatformWidth / 2), boundCenterY - (innerPlatformHeight / 2), innerPlatformWidth, innerPlatformHeight);

    // Draw Desks
    cairo_rectangle(cr, boundTopLeftX - playerStationDeskWidth, boundTopLeftY + boundSlantHeight, playerStationDeskWidth, playerStationHeight);
    cairo_rectangle(cr, boundTopLeftX - playerStationDeskWidth, boundTopLeftY + sideBoundHeight + boundSlantHeight - (2 * playerStationHeight), playerStationDeskWidth, (2 * playerStationHeight));
    cairo_rectangle(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundSlantHeight, playerStationDeskWidth, (2 * playerStationHeight));
    cairo_rectangle(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundTotalHeight - boundSlantHeight - playerStationHeight, playerStationDeskWidth, playerStationHeight);
    cairo_set_source_rgb(cr, .8, .8, .8);
    cairo_fill(cr);

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

    cairo_move_to(cr, playerStationTopLeftX, boundTopLeftY + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX, boundTopLeftY + boundSlantHeight);

    cairo_move_to(cr, playerStationTopLeftX, boundTopLeftY + boundSlantHeight + playerStationHeight);
    cairo_line_to(cr, boundTopLeftX, boundTopLeftY + boundSlantHeight + playerStationHeight);

    cairo_move_to(cr, playerStationTopLeftX, boundTopLeftY + boundSlantHeight + playerStationHeight + exchangeZoneHeight);
    cairo_line_to(cr, boundTopLeftX, boundTopLeftY + boundSlantHeight + playerStationHeight + exchangeZoneHeight);

    cairo_move_to(cr, playerStationTopLeftX, boundTopLeftY + boundTotalHeight - boundSlantHeight - playerStationHeight);
    cairo_line_to(cr, boundTopLeftX, boundTopLeftY + boundTotalHeight - boundSlantHeight - playerStationHeight);

    cairo_move_to(cr, playerStationTopLeftX, boundTopLeftY + sideBoundHeight + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX, boundTopLeftY + sideBoundHeight + boundSlantHeight);

    cairo_move_to(cr, playerStationTopRightX, boundTopLeftY + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundSlantHeight);

    cairo_move_to(cr, playerStationTopRightX, boundTopLeftY + boundSlantHeight + playerStationHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundSlantHeight + playerStationHeight);

    cairo_move_to(cr, playerStationTopRightX, boundTopLeftY + boundSlantHeight + (playerStationHeight * 2));
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundSlantHeight + (playerStationHeight * 2));

    cairo_move_to(cr, playerStationTopRightX, boundTopLeftY + boundTotalHeight - boundSlantHeight - playerStationHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + boundTotalHeight - boundSlantHeight - playerStationHeight);

    cairo_move_to(cr, playerStationTopRightX, boundTopLeftY + sideBoundHeight + boundSlantHeight);
    cairo_line_to(cr, boundTopLeftX + boundTotalWidth, boundTopLeftY + sideBoundHeight + boundSlantHeight);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_set_line_width(cr, 4);
    cairo_stroke(cr);
  }

  void FieldGraphicsOutputGenerator::DrawRobot(cairo_t* cr, FieldFacing* vector, FieldPosition* topLeft, FieldPosition* bottomRight, bool isRed)
  {
    int robotSize;
    int xCoordinate, yCoordinate;
    int arrowX, arrowY, arrowLength;
    double facing;

    robotSize = 30;
    arrowLength = 45;

    // Draw the Robot
    xCoordinate = vector->GetXCoordinate();
    yCoordinate = topLeft->GetYCoordinate() - vector->GetYCoordinate();
    facing = vector->GetFacing() * PI / 180;
    arrowX = sin(facing) * arrowLength;
    arrowY = cos(facing) * arrowLength;

    cairo_arc(cr, xCoordinate, yCoordinate, robotSize, 0, 2 * PI);
    SET_TEAM_COLOR(isRed);

    cairo_set_dash(cr, 0, 0, 0);
    cairo_fill_preserve(cr);
    cairo_stroke(cr);

    // Draw the facing
    cairo_move_to(cr, xCoordinate, yCoordinate);
    cairo_line_to(cr, xCoordinate + arrowX, yCoordinate - arrowY);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_stroke(cr);
  }

  void FieldGraphicsOutputGenerator::DrawScales(cairo_t* cr, int xAxis, int yAxis, int width, int height)
  {
    int scalePadding;
    int topScaleX, topScaleY;
    int bottomScaleX, bottomScaleY;
    int scaleWidth, scaleHeight;
    int armWidth, armHeight, leftArmX, leftArmY;
    int rightArmX, rightArmY, armOverlap, armsPerWidth;

    scaleWidth = 122;
    scaleHeight = 91;
    armOverlap = 5;
    armsPerWidth = 8;

    scalePadding = (width - scaleWidth) / 2;
    topScaleX = xAxis + scalePadding;
    topScaleY = yAxis + scalePadding;

    bottomScaleX = topScaleX;
    bottomScaleY = yAxis + height - scalePadding - scaleHeight;

    armWidth = width / armsPerWidth;
    armHeight = height - (2 * scalePadding) - (2 * scaleHeight) + (2 * armOverlap);
    leftArmY = rightArmY = yAxis + scalePadding + scaleHeight - armOverlap;
    leftArmX = xAxis + scalePadding + (scaleWidth / 2) - (2 * armWidth);
    rightArmX = leftArmX + (3 * armWidth);

    cairo_rectangle(cr, topScaleX, topScaleY, scaleWidth, scaleHeight);
    cairo_rectangle(cr, bottomScaleX, bottomScaleY, scaleWidth, scaleHeight);
    cairo_rectangle(cr, leftArmX, leftArmY, armWidth, armHeight);
    cairo_rectangle(cr, rightArmX, rightArmY, armWidth, armHeight);

    cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
    cairo_fill_preserve(cr);

    cairo_rectangle(cr, xAxis, yAxis, width, height);
    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_set_line_width(cr, 4);
    cairo_stroke(cr);
  }

  void FieldGraphicsOutputGenerator::DrawPlatform(cairo_t* cr, int innerX, int innerY, int innerWidth, int innerHeight, int outerX, int outerY, int outerWidth, int outerHeight)
  {
    int outerLeftX, outerRightX;
    int outerTopY, outerBottomY;

    int innerLeftX, innerRightX;
    int innerTopY, innerBottomY;
    int centerX, centerY;

    outerLeftX = outerX;
    outerRightX = outerX + outerWidth;
    outerTopY = outerY;
    outerBottomY = outerY + outerHeight;

    innerLeftX = innerX;
    innerRightX = innerX + innerWidth;
    innerTopY = innerY;
    innerBottomY = innerY + innerHeight;

    centerX = outerLeftX + (outerWidth / 2);
    centerY = outerTopY + (outerHeight / 2);

    // Red
    cairo_rectangle(cr, innerLeftX, innerTopY, (innerWidth / 2), innerHeight);
    cairo_set_source_rgb(cr, 0.81, 0.33, 0.33);
    cairo_fill(cr);

    // Light Pink
    cairo_move_to(cr, centerX, outerTopY);
    cairo_line_to(cr, centerX, innerTopY);
    cairo_line_to(cr, innerLeftX, innerTopY);
    cairo_line_to(cr, innerLeftX, innerBottomY);
    cairo_line_to(cr, outerLeftX, outerBottomY);
    cairo_line_to(cr, outerLeftX, outerTopY);
    cairo_close_path(cr);

    cairo_set_source_rgb(cr, 0.99, 0.58, 0.58);
    cairo_fill(cr);

    // Dark Red
    cairo_move_to(cr, centerX, innerBottomY);
    cairo_line_to(cr, centerX, outerBottomY);
    cairo_line_to(cr, outerLeftX, outerBottomY);
    cairo_line_to(cr, innerLeftX, innerBottomY);
    cairo_close_path(cr);

    cairo_set_source_rgb(cr, 0.53, 0.1, 0.1);
    cairo_fill(cr);

    // Blue
    cairo_rectangle(cr, centerX, innerY, innerWidth / 2, innerHeight);
    cairo_set_source_rgb(cr, 0.25, 0.44, 0.92);
    cairo_fill(cr);

    // Light Blue
    cairo_move_to(cr, centerX, outerTopY);
    cairo_line_to(cr, outerRightX, outerTopY);
    cairo_line_to(cr, innerRightX, innerTopY);
    cairo_line_to(cr, centerX, innerTopY);
    cairo_close_path(cr);

    cairo_set_source_rgb(cr, 0.49, 0.71, 0.98);
    cairo_fill(cr);

    // Dark Blue
    cairo_move_to(cr, centerX, innerBottomY);
    cairo_line_to(cr, innerRightX, innerBottomY);
    cairo_line_to(cr, innerRightX, innerTopY);
    cairo_line_to(cr, outerRightX, outerTopY);
    cairo_line_to(cr, outerRightX, outerBottomY);
    cairo_line_to(cr, centerX, outerBottomY);
    cairo_close_path(cr);

    cairo_set_source_rgb(cr, 0.04, 0.2, 0.71);
    cairo_fill(cr);
  }
}
