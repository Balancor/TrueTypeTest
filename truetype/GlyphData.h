//
// Created by guoguo on 2017/3/25.
//

#ifndef GTRUETYPE_GLYPHDATA_H
#define GTRUETYPE_GLYPHDATA_H

#include <stdint-gcc.h>
#include <list>
#include <vector>
#include "Base.h"

#define SIMPLE_FLAG_ON_CUREVE 1 << 0
#define SIMPLE_FLAG_X_SHORT   1 << 1
#define SIMPLE_FLAG_Y_SHORT   1 << 2
#define SIMPLE_FLAG_REPEATED  1 << 3
#define SIMPLE_FLAG_X_SAME    1 << 4
#define SIMPLE_FLAG_Y_SAMED   1 << 5
#define SIMPLE_FLAG_RESERVED1 1 << 6
#define SIMPLE_FLAG_RESERVED2 1 << 7

/*Compound Glyph Flag*/
#define ARG_1_AND_2_ARE_WORDS 1 << 0
#define ARGS_ARE_XY_VALUES    1 << 1
#define ROUND_XY_TO_GRID      1 << 2
#define WE_HAVE_A_SCALE       1 << 3
#define RESERVED              1 << 4
#define MORE_COMPONENTS       1 << 5
#define WE_HAVE_AN_X_AND_Y_SCALE 1 << 6
#define WE_HAVE_A_TWO_BY_TWO     1 << 7
#define WE_HAVE_INSTRUCTIONS     1 << 8
#define USE_MY_METRICS           1 << 9

using namespace std;

class GlyphDataHeader {
public:
    int16_t numberOfCountours;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;

    static uint16_t getNumOfCountors();
};


class SimpleGlyph : public GlyphDataHeader{
public:
    uint16_t *endPtsOfContours;
    uint16_t instructionLength;
    uint8_t  *instructions;
    uint8_t  *flags;
    int16_t *xCoordinates;
    int16_t *yCoordinates;

    uint16_t numberOfPoints;

    int16_t maxXCoord = 0, minXCoord = 0,
            maxYCoord = 0, minYCoord = 0;

    bool *isOnCurve;
    vector<QuadraticBezierCurve> mQuadraticBezierCurves;

    SimpleGlyph(const char* fileName, uint32_t offset, uint32_t length);

    int16_t *getXCoords(){ return xCoordinates;}
    int16_t *getYCoords(){ return yCoordinates;}
    uint16_t getNumOfPoints(){ return numberOfPoints;}

    int16_t  getMaxXCoord(){
        return maxXCoord;
    }
    int16_t  getMinXCoord(){
        return minXCoord;
    }
    int16_t  getMaxYCoord(){
        return maxYCoord;
    }
    int16_t  getMinYCoord(){
        return minYCoord;
    }

    void initQuadraticBezierCurves();
    vector<QuadraticBezierCurve> getQuadraticBezierCurves(){
        return mQuadraticBezierCurves;
    }

};

class CompoundGlyph : public GlyphDataHeader {

};

#endif //GTRUETYPE_GLYPHDATA_H
