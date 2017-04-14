//
// Created by guoguo on 17-4-1.
//

#ifndef GTRUETYPE_BITMAP_H
#define GTRUETYPE_BITMAP_H


#include <cstdint>
#include "Base.h"

#define FLAG_POINT_DRAWED  1

class Bitmap {
public:
    uint32_t mWidth;
    uint32_t mHeight;
    uint8_t  mStride = 4;//RGBA 3byte

    uint32_t mPointNumbers;
    uint8_t *mPointFlags;
    uint8_t * mRawData;


    Bitmap(uint32_t w, uint32_t h);

    uint8_t getFlag(uint32_t x, uint32_t y);
    uint8_t getFlag(Point point);

    void setPointColor(uint32_t x, uint32_t y, uint32_t color);
    void setPointColor(Point point, uint32_t color);


    void drawLine(uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY);
    void drawLine(Point startPoint, Point endPoint);


    void drawQuadraticBezier(Point startPoint, Point controlPoint, Point endPoint);

};

#endif //GTRUETYPE_BITMAP_H
