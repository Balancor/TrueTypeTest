//
// Created by guoguo on 17-4-5.
//

#ifndef GTRUETYPE_HHEATABLE_H
#define GTRUETYPE_HHEATABLE_H


#include "Base.h"

class HheaTable : public Table{

public:
    uint16_t	majorVersion;
    uint16_t	minorVersion;
    int16_t	    ascender;
    int16_t	    descender;
    int16_t	    lineGap;
    uint16_t	advanceWidthMax;
    int16_t	    minLeftSideBearing;
    int16_t	    minRightSideBearing;
    int16_t	    xMaxExtent;
    int16_t	    caretSlopeRise;
    int16_t	    caretSlopeRun;
    int16_t	    caretOffset;
    int16_t	    reserved1;
    int16_t	    reserved2;
    int16_t	    reserved3;
    int16_t	    reserved4;
    int16_t	    metricDataFormat;
    uint16_t	numberOfHMetrics;

    HheaTable(const char* fontFileName);

    void setOffset(uint32_t offset){
        mOffset = offset;
    }

};


#endif //GTRUETYPE_HHEATABLE_H
