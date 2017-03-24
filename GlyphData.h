//
// Created by guoguo on 2017/3/25.
//

#ifndef GTRUETYPE_GLYPHDATA_H
#define GTRUETYPE_GLYPHDATA_H

#include <stdint-gcc.h>

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


class Glyph {
public:
    int16_t numberOfCountours;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;
};


class SimpleGlyph : public Glyph{
public:
    uint16_t *endPtsOfContours;
    uint16_t instructionLength;
    uint8_t  *instructions;
    uint8_t  *flags;
    uint16_t *xCoordinates;
    uint16_t *yCoordinates;

};

class CompoundGlyph : public Glyph {

};

#endif //GTRUETYPE_GLYPHDATA_H
