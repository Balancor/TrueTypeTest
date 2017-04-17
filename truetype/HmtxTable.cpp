//
// Created by guoguo on 17-4-5.
//

#include <cstring>
#include "HmtxTable.h"
#include "../utils.h"
#include "GTrueType_defs.h"

HmtxTable::HmtxTable(const char* fileName, uint32_t numOfHMetrics, uint32_t numOfGlyphs){
    int offset = 0;
    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* hmtxTableRecord = directoryTable->getTableRecord(TABLE_TAG_HMTX);
    if(hmtxTableRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }

    this->mNumberOfHMetrics = numOfHMetrics;
    this->mNumberOfGlyphs = numOfGlyphs;
    int numOfLSB =(mNumberOfGlyphs - mNumberOfHMetrics);
    this->mLength = sizeof(LongHorMetric) * mNumberOfHMetrics +
            sizeof(int16_t) * numOfLSB;

    this->mOffset = hmtxTableRecord->offset;
    char* content = readNumberBytesFromFile(fileName, mOffset, mLength);



    hMetrics = (LongHorMetric**)malloc(sizeof(void*) * mNumberOfHMetrics);
    memset(hMetrics, 0, sizeof(LongHorMetric) * mNumberOfHMetrics);
    for (int i = 0; i < mNumberOfHMetrics; ++i) {
        LongHorMetric* metric = (LongHorMetric*)malloc(sizeof(LongHorMetric));
        metric->advanceWidth = readTwoBytesAsUShort(content + offset);
        offset += sizeof(uint16_t);
        metric->leftSideBearing = readTwoBytesAsShort(content + offset);
        offset += sizeof(int16_t);

        hMetrics[i] = metric;
    }

    leftSideBearings = (int16_t*)malloc(sizeof(int16_t) * numOfLSB);
    for (int i = 0; i < numOfLSB; ++i) {
        leftSideBearings[i] = readTwoBytesAsShort(content + offset);
        offset += sizeof(int16_t);
    }


}

uint16_t HmtxTable::getAdvanceWidth(uint16_t gid){
    uint16_t  advanceWidth = 0;
    if(gid <= mNumberOfHMetrics){
        advanceWidth = hMetrics[gid]->advanceWidth;
    } else {
        advanceWidth = 0;
    }
    return  advanceWidth;
}
int16_t HmtxTable::getLeftSideBearing(uint16_t gid){
    int16_t  leftSideBearing = 0;
    if(gid <= mNumberOfHMetrics){
        leftSideBearing = hMetrics[gid]->leftSideBearing;
    } else {
        leftSideBearing = leftSideBearings[gid - mNumberOfHMetrics];
    }
    return  leftSideBearing;
}