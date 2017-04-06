//
// Created by guoguo on 17-4-5.
//

#ifndef GTRUETYPE_HMTXTABLE_H
#define GTRUETYPE_HMTXTABLE_H


#include "Base.h"

typedef struct {
    uint16_t advanceWidth;
    int16_t leftSideBearing;
}LongHorMetric;

class HmtxTable : public Table{
public:
    LongHorMetric** hMetrics;
    int16_t* leftSideBearings;

    uint32_t  mNumberOfHMetrics;
    uint32_t  mNumberOfGlyphs;

    HmtxTable(const char* fileName, uint32_t numOfHMetrics, uint32_t numOfGlyphs);

    uint16_t getAdvanceWidth(uint16_t gid);
    int16_t getLeftSideBearing(uint16_t gid);


    void setOffset(uint32_t offset){
        mOffset = offset;
    }

};


#endif //GTRUETYPE_HMTXTABLE_H
