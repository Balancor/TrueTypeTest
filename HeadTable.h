//
// Created by guoguo on 17-3-23.
//

#ifndef GTRUETYPE_HEADTABLE_H
#define GTRUETYPE_HEADTABLE_H


#include "Base.h"

class HeadTable : public Table {

public:
    uint32_t mVersion;
    uint32_t mFontVersion;
    uint32_t mCheckSumAdjustment;
    uint32_t mMagicNumber;
    uint16_t mFlags;
    uint16_t mUnitsPerEm;
    uint64_t mCreated;
    uint64_t mModifie;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;
    uint16_t mMacStyle;
    uint16_t mLowestRecPPEM;
    int16_t mFontDirectionHint;
    int16_t mIndexToLocFormat;
    int16_t mGlyphDataFormat;


public:
    HeadTable(const char* fileName);

    void setOffset(uint32_t offset){
        mOffset = offset;
    }

    void dump();
    friend class LocaTable;
};


#endif //GTRUETYPE_HEADTABLE_H
