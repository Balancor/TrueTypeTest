//
// Created by guoguo on 17-3-22.
//

#include "ByteEncodingTable.h"
#include "../utils.h"

ByteEncodingTable::ByteEncodingTable(const char* fileName, uint16_t platformId, uint16_t encodingId){
    CmapTable* cmapTable = getCmapTable(fileName);
    EncodingTableRecord* tableRecord = cmapTable->getEncodingRecord(platformId, encodingId);
    if(tableRecord == NULL){
        printf("Cannot get Encoding Table Record\n");
        return ;
    }

    this->mLength = 262;
    this->mOffset = cmapTable->mOffset + tableRecord->offset;
    char* content = readNumberBytesFromFile(fileName, mOffset, mLength);

    int offsetInternal = 0;
    this->mFormat = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal += 2;
    this->mLength = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal += 2;
    this->mLanguage = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal+= 2;

    for (int i = 0; i < 256; ++i) {
        mGlyphIdArray[i] = *(content+offsetInternal);
        offsetInternal++;
    }
}

uint16_t ByteEncodingTable::getGlyphIndex(uint32_t charactCode){
    if(charactCode > 0 && charactCode < 256){
        return mGlyphIdArray[charactCode];
    }
    return  0;
}