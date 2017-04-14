//
// Created by guoguo on 17-4-1.
//

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "Bitmap.h"
Bitmap::Bitmap(uint32_t w, uint32_t h){
    if( w <= 0 || h <= 0){
        return ;
    }
    this->mPointNumbers = w * h;
    mPointFlags = (uint8_t*)malloc(sizeof(uint8_t) * mPointNumbers);
    if(mPointFlags == NULL){
        printf("Cannot malloc the memory for Bitmap\n");
        return ;
    }
    memset(mPointFlags, 0, mPointNumbers);

    int  rawCount = mPointNumbers * mStride;
    mRawData = (uint8_t*)malloc(sizeof(char) * rawCount);
    if(rawCount <= 0 || mRawData == NULL){
        printf("Cannot malloc the memory for Bitmap\n");
        return ;
    }
    memset(mRawData, 0, rawCount);

    this->mWidth = w;
    this->mHeight = h;
}

uint8_t Bitmap::getFlag(uint32_t x, uint32_t y){
    uint32_t  index = x + (y * mWidth);
    return mPointFlags[index];
}
uint8_t Bitmap::getFlag(Point point){
    return getFlag(point.x, point.y);
}

void Bitmap::setPointColor(uint32_t x, uint32_t y, uint32_t color){
    uint8_t pointFlag = getFlag(x, y);

    if((pointFlag&FLAG_POINT_DRAWED) == FLAG_POINT_DRAWED){
        //printf("This point has been drawed\n");
        return;
    }
    uint8_t red   = (color >> 24) & 0xFF;
    uint8_t green = (color >> 16) & 0xFF;
    uint8_t blue  = (color  >> 8) & 0xFF;
    uint8_t alpha = (color ) & 0xFF;
    uint32_t  index = (x + (y * mWidth));
    uint32_t offset = index * mStride;
    mRawData[offset] = red;
    mRawData[offset + 1] = green;
    mRawData[offset + 2] = blue;
    mRawData[offset + 3] = alpha;

    mPointFlags[index] = ((pointFlag | FLAG_POINT_DRAWED) & 0xFF);
}

void Bitmap::setPointColor(Point point, uint32_t color){
    setPointColor(point.x, point.y, color);
}

void Bitmap::drawLine(uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY) {

    int dx = endX - startX;
    int dy = endY - startY;
    int ux = ((dx > 0) << 1) - 1;
    int uy = ((dy > 0) << 1) - 1;
    int x = startX, y = startY, eps;

    printf("startX: %u, startY: %u, endX: %u, endY: %u\n",startX, startY, endX, endY);
    eps = 0;dx = abs(dx); dy = abs(dy);
    if (dx > dy) {
        for (x = startX; x != endX; x += ux) {
            setPointColor(x, y, 255 << 24);
            eps += dy;
            if ((eps << 1) >= dx) {
                y += uy; eps -= dx;
            }
        }
    } else {
        for (y = startY; y != endY; y += uy) {
            setPointColor(x, y, 255 << 24);
            eps += dx;
            if ((eps << 1) >= dy) {
                x += ux; eps -= dy;
            }
        }
    }
}

void Bitmap::drawLine(Point startPoint, Point endPoint){

    drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

void Bitmap::drawQuadraticBezier(Point startPoint, Point controlPoint, Point endPoint){
    printf("drawQuadraticBezier START\n");
    startPoint.dump();
    controlPoint.dump();
    endPoint.dump();
    float step = 0.01;
    Point p1, p2, targetPoint;
    for (float per= 0; per < 1; per+=step) {
        p1 = startPoint.getLocationAtLine(controlPoint, per);
        p2 = controlPoint.getLocationAtLine(endPoint, per);
        targetPoint = p1.getLocationAtLine(p2, per);
//        targetPoint.dump();
        setPointColor(targetPoint,255 << 24);
    }
}

