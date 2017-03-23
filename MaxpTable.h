//
// Created by guoguo on 17-3-23.
//

#ifndef GTRUETYPE_MAXPTABLE_H
#define GTRUETYPE_MAXPTABLE_H

#include "Base.h"

class MaxpTable : public Table {
protected:
    uint32_t mMaxpTableVersion;
    uint16_t mNumGlyphs;
    uint16_t mMaxPoints;
    uint16_t mMaxContours;
    uint16_t mMaxCompositePoints;
    uint16_t mMaxCompositeContours;
    uint16_t mMaxZones;
    uint16_t mMaxTwilightPoints;
    uint16_t mMaxStorage;
    uint16_t mMaxFunctionDefs;
    uint16_t mMaxInstructionDefs;
    uint16_t mMaxStackElements;
    uint16_t mMaxSizeOfInstructions;
    uint16_t mMaxComponentElements;
    uint16_t mMaxComponentDepth;
public:
    MaxpTable(const char* fileName);
};


#endif //GTRUETYPE_MAXPTABLE_H
