//
// Created by guoguo on 17-3-23.
//

#ifndef GTRUETYPE_LOCATABLE_H
#define GTRUETYPE_LOCATABLE_H

#include "Base.h"


class LocaTable : public Table{

public:
    bool isShortVersion;
    uint16_t mNumGlyphs;
    uint32_t *mOffsets;

public:
    LocaTable(const char* fileName, bool isShort, uint16_t numGlyphs);

    void setOffset(uint32_t offset){
        mOffset = offset;
    }
    uint32_t getGlyphOffset(uint16_t gid);
    uint32_t getGlyphLength(uint16_t gid);

    friend class HeadTable;
    friend class MaxpTable;
};


#endif //GTRUETYPE_LOCATABLE_H
