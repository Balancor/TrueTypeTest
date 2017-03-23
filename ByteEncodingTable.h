//
// Created by guoguo on 17-3-22.
//

#ifndef GTRUETYPE_BYTEENCODINGTABLE_H
#define GTRUETYPE_BYTEENCODINGTABLE_H

#include "CmapTable.h"

class ByteEncodingTable : public EncodingTable{
private:
    uint8_t  mGlyphIdArray[256];

public:
    ByteEncodingTable(char* content, uint32_t offset, uint32_t length);
};


#endif //GTRUETYPE_BYTEENCODINGTABLE_H
