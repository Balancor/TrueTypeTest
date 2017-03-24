//
// Created by guoguo on 17-3-22.
//

#ifndef GTRUETYPE_SEGMENTMAPPINGTABLE_H
#define GTRUETYPE_SEGMENTMAPPINGTABLE_H


#include "Base.h"
#include "CmapTable.h"

class SegmentMappingTable : public EncodingTable
{
protected:
    uint16_t 	mSegCount;
    uint16_t 	mSearchRange;
    uint16_t 	mEntrySelector;
    uint16_t 	mRangeShift;
    uint16_t 	*mEndCodes;
    uint16_t 	mReservedPad;
    uint16_t 	*mStartCodes;
    int16_t 	*mIdDeltas;
    uint16_t 	*mIdRangeOffsets;
//    uint16_t 	*mGlyphIdArray;

    uint16_t mIdRangeOffsetOffset;

public:
    SegmentMappingTable(const char* fileName, uint16_t platformId, uint16_t encodingId);

    void setOffset(uint32_t offset){
        this->mOffset = offset;
    }

    uint16_t getGlyphIndex(uint32_t charactCode);

};


#endif //GTRUETYPE_SEGMENTMAPPINGTABLE_H
