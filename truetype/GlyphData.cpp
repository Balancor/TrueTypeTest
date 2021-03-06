//
// Created by guoguo on 17-3-27.
//

#include <cstring>
#include "GlyphData.h"
#include "Base.h"
#include "../utils.h"
#include "HeadTable.h"

SimpleGlyph::SimpleGlyph(const char *fileName, uint32_t offset, uint32_t length) {
    char *content = readNumberBytesFromFile(fileName, offset, length);

    int offsetInternal = 0;
    numberOfCountours = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    xMin = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    yMin = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    xMax = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    yMax = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;

    endPtsOfContours = (uint16_t *) malloc(sizeof(uint16_t) * numberOfCountours);
    for (int i = 0; i < numberOfCountours; ++i) {
        endPtsOfContours[i] = readTwoBytesAsUShort(content + offsetInternal);
        offsetInternal += 2;
    }

    numberOfPoints = endPtsOfContours[numberOfCountours - 1] + 1;

    instructionLength = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal += 2;

    instructions = (uint8_t *) malloc(sizeof(uint8_t) * instructionLength);
    for (int j = 0; j < instructionLength; ++j) {
        instructions[j] = *(content + offsetInternal);
        offsetInternal++;
    }

    int lengthOfFlags = 0;
    uint8_t repeatedCount = 0;
    uint8_t flag = 0;
    flags = (uint8_t *) malloc(sizeof(uint8_t) * numberOfPoints);
    isOnCurve = (bool *) malloc(sizeof(bool) * numberOfPoints);
    for (int pointIndex = 0; pointIndex < numberOfPoints; pointIndex++) {
        isOnCurve[pointIndex] = false;
        if (repeatedCount == 0) {
            flag = (uint8_t) (*(content + offsetInternal));
            offsetInternal++;
            lengthOfFlags++;
            flags[pointIndex] = flag;

            if ((flag & SIMPLE_FLAG_REPEATED) == SIMPLE_FLAG_REPEATED) {
                repeatedCount = (uint8_t) (*(content + offsetInternal));
                offsetInternal++;
                lengthOfFlags++;
            }
        } else {
            repeatedCount--;
            flags[pointIndex] = flag;
        }
        if ((flag & SIMPLE_FLAG_ON_CUREVE) == SIMPLE_FLAG_ON_CUREVE) {
            isOnCurve[pointIndex] = true;
        }
    }

    HeadTable *headTable = new HeadTable(fileName);
    maxXCoord = headTable->xMin;
    minXCoord = headTable->xMax;
    maxYCoord = headTable->yMin;
    minYCoord = headTable->yMax;

    xCoordinates = (int16_t *) malloc(sizeof(int16_t) * numberOfPoints);
    yCoordinates = (int16_t *) malloc(sizeof(int16_t) * numberOfPoints);
    //fill xCoord
    for (int k = 0; k < numberOfPoints; ++k) {
        flag = flags[k];
        xCoordinates[k] = 0;
        if ((flag & SIMPLE_FLAG_X_SHORT) == SIMPLE_FLAG_X_SHORT) {
            uint8_t xcoord = (uint8_t) (*(content + offsetInternal));
            xCoordinates[k] = xcoord;
            xCoordinates[k] *=
                    ((flag & SIMPLE_FLAG_X_SAME) == SIMPLE_FLAG_X_SAME) ? 1 : -1;
            offsetInternal++;
        } else {
            // double byte coord value
            if (!((flag & SIMPLE_FLAG_X_SAME) == SIMPLE_FLAG_X_SAME)) {
                xCoordinates[k] = readTwoBytesAsShort(content + offsetInternal);
                offsetInternal += 2;
            }
        }
        if (k > 0) {
            xCoordinates[k] += xCoordinates[k - 1];
        }
        if (xCoordinates[k] > maxXCoord) maxXCoord = xCoordinates[k];
        if (xCoordinates[k] < minXCoord) minXCoord = xCoordinates[k];
    }

    //fill yCoord
    for (int k = 0; k < numberOfPoints; ++k) {
        flag = flags[k];
        yCoordinates[k] = 0;
        if ((flag & SIMPLE_FLAG_Y_SHORT) == SIMPLE_FLAG_Y_SHORT) {
            uint8_t ycoord = (uint8_t) (*(content + offsetInternal));
            yCoordinates[k] = ycoord;

            yCoordinates[k] *=
                    ((flag & SIMPLE_FLAG_Y_SAMED) == SIMPLE_FLAG_Y_SAMED) ? 1 : -1;
            offsetInternal++;
        } else {
            // double byte coord value
            if (!((flag & SIMPLE_FLAG_Y_SAMED) == SIMPLE_FLAG_Y_SAMED)) {
                yCoordinates[k] = readTwoBytesAsShort(content + offsetInternal);
                offsetInternal += 2;
            }
        }
        if (k > 0) {
            yCoordinates[k] += yCoordinates[k - 1];
        }

        if (yCoordinates[k] > maxYCoord) maxYCoord = yCoordinates[k];
        if (yCoordinates[k] < minYCoord) minYCoord = yCoordinates[k];
    }

    initQuadraticBezierCurves();
}

void SimpleGlyph::initQuadraticBezierCurves() {
    int pointIndex = 0;
    int curveLocation = 0;

    for (int i = 0; i < numberOfCountours; ++i) {
        uint16_t pointOfCountours = endPtsOfContours[i] + 1;
        if (i > 0) {
            pointOfCountours = endPtsOfContours[i] - endPtsOfContours[i - 1];
        }

        Point *startPoint, *controlPoint, *endPoint;
        Point *countoursStartPoint, *countoursEndPoint;
        int j = 0;

        countoursStartPoint = startPoint = new Point(xCoordinates[pointIndex], yCoordinates[pointIndex]);
        pointIndex++;
        bool curveHasStartPoint = true;
        for (j = 1; j < pointOfCountours; ++j) {
            uint8_t prevIsOnCurve = isOnCurve[pointIndex - 1];
            uint8_t onCurve = isOnCurve[pointIndex];
            Point *point = new Point(xCoordinates[pointIndex], yCoordinates[pointIndex]);

            if (onCurve) {
                if (prevIsOnCurve) {
                    controlPoint = point;
                    endPoint = point;
                    curveHasStartPoint = false;
                    QuadraticBezierCurve quadraticBezierCurve;
                    quadraticBezierCurve.startPoint = startPoint;
                    quadraticBezierCurve.controlPoint = controlPoint;
                    quadraticBezierCurve.endPoint = endPoint;
                    mQuadraticBezierCurves.push_back(quadraticBezierCurve);
                    curveLocation++;
                } else {
                    if (curveHasStartPoint) {
                        endPoint = point;
                        curveHasStartPoint = false;
                        QuadraticBezierCurve quadraticBezierCurve;
                        quadraticBezierCurve.startPoint = startPoint;
                        quadraticBezierCurve.controlPoint = controlPoint;
                        quadraticBezierCurve.endPoint = endPoint;
                        mQuadraticBezierCurves.push_back(quadraticBezierCurve);
                        curveLocation++;
                    } else {
                        curveHasStartPoint = true;
                    }
                }
                if(!curveHasStartPoint){
                    startPoint = point;
                    curveHasStartPoint = true;
                }
            } else {
                uint8_t nextIsOnCurve = isOnCurve[pointIndex +1];
                Point* nextPoint = new Point(xCoordinates[pointIndex + 1], yCoordinates[pointIndex + 1]);
                if(nextIsOnCurve){
                    controlPoint = point;
                } else {
                    startPoint = mQuadraticBezierCurves.at(curveLocation - 1).endPoint;
                    controlPoint = point;
                    endPoint->x = (point->x + nextPoint->x) / 2;
                    endPoint->y = (point->y + nextPoint->y) / 2;
                    QuadraticBezierCurve quadraticBezierCurve;
                    quadraticBezierCurve.startPoint = startPoint;
                    quadraticBezierCurve.controlPoint = controlPoint;
                    quadraticBezierCurve.endPoint = endPoint;
                    mQuadraticBezierCurves.push_back(quadraticBezierCurve);
                    curveLocation++;
                    curveHasStartPoint = false;
                }
            }
            pointIndex++;
        }

        QuadraticBezierCurve curve;
        countoursEndPoint = new Point(xCoordinates[pointIndex - 1], yCoordinates[pointIndex - 1]);
        bool countoursEndOnCurve = isOnCurve[pointIndex - 1];
        if (!countoursEndOnCurve) {
            curve.startPoint = mQuadraticBezierCurves.at(curveLocation - 1).endPoint;
            curve.controlPoint = countoursEndPoint;
            curve.endPoint = countoursStartPoint;
        } else {
            curve.startPoint = countoursEndPoint;
            curve.controlPoint = countoursStartPoint;
            curve.endPoint = countoursStartPoint;
        }
        mQuadraticBezierCurves.push_back(curve);
        curveLocation++;
    }
}