//
// Created by guoguo on 17-3-22.
//

#ifndef GTRUETYPE_BYTEENCODINGTABLE_H
#define GTRUETYPE_BYTEENCODINGTABLE_H

#include "Base.h"
#include "CmapTable.h"

class ByteEncodingTable : public EncodingTable{
protected:
    uint8_t  mGlyphIdArray[256];

public:
    ByteEncodingTable(const char* fileName, uint16_t platformId, uint16_t encodingId);

    void setOffset(uint32_t offset){
        this->mOffset = offset;
    }

    uint16_t getGlyphIndex(uint32_t charactCode);
};


#endif //GTRUETYPE_BYTEENCODINGTABLE_H
