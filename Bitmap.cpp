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

    int  rawCount = w * h * mStride;
    mRawData = (uint8_t*)malloc(sizeof(char) * rawCount);
    memset(mRawData, 0, rawCount);

    this->mWidth = w;
    this->mHeight = h;
}

void Bitmap::setPointColor(uint32_t x, uint32_t y, uint32_t color){
    uint8_t red   = (color >> 24) & 0xFF;
    uint8_t green = (color >> 16) & 0xFF;
    uint8_t blue  = (color  >> 8) & 0xFF;
    uint8_t alpha = (color ) & 0xFF;

    uint32_t offset = (x + (y * mWidth)) * mStride;
//    printf("targetX: %u, targetY: %u, offset: %u\n",x, y, offset);
//    printf("R: %u, G: %u, B: %u\n",red, green, blue);
    mRawData[offset] = red;
    mRawData[offset + 1] = green;
    mRawData[offset + 2] = blue;
    mRawData[offset + 3] = alpha;
}

void Bitmap::drawLine(uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY) {

    int dx = endX - startX;
    int dy = endY - startY;
    int ux = ((dx > 0) << 1) - 1;
    int uy = ((dy > 0) << 1) - 1;
    int x = startX, y = startY, eps;

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