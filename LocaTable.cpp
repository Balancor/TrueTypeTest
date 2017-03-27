//
// Created by guoguo on 17-3-23.
//

#include "LocaTable.h"
#include "utils.h"
#include "GTrueType_defs.h"
LocaTable::LocaTable(const char* fileName, bool isShort, uint16_t numGlyphs){
    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* locaTableRecord = directoryTable->getTableRecord(TABLE_TAG_LOCA);
    if(locaTableRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }
    this->mOffset = locaTableRecord->offset;
    this->isShortVersion = isShort;
    this->mNumGlyphs = numGlyphs;

    int offsetInternal = 0;
    int count = 0;
    if(isShortVersion){
        count = numGlyphs * sizeof(uint16_t);
        this->mOffsets = (uint32_t*)malloc(sizeof(uint16_t) * (mNumGlyphs + 1));
    } else {
        count = numGlyphs * sizeof(uint32_t);
        this->mOffsets = (uint32_t*)malloc(sizeof(uint32_t) * (mNumGlyphs + 1));
    }

    char* locaContent = readNumberBytesFromFile(fileName, mOffset, count);

    for (int i = 0; i < mNumGlyphs; ++i) {
        if(isShortVersion){
            this->mOffsets[i] = readTwoBytesAsUShort(locaContent + offsetInternal);
            offsetInternal += 2;
        } else {
            this->mOffsets[i] = readFourBytesAsUInt(locaContent + offsetInternal);
            offsetInternal += 4;
        }
    }

    free(locaContent);
    locaContent = NULL;
}

uint32_t LocaTable::getGlyphOffset(uint16_t gid){
    uint32_t  offset = 0;
    if(gid >=0 && gid < mNumGlyphs){
        if(mOffsets){
            offset = mOffsets[gid];
        }

    }
    return offset;
}
uint32_t LocaTable::getGlyphLength(uint16_t gid){
    uint32_t  length = 0;
    if(gid >=0 && gid < mNumGlyphs ){
        uint32_t nextOffset = 0;
        if(gid < mNumGlyphs -1){
            nextOffset = mOffsets[gid + 1];
        }
        length = nextOffset - mOffsets[gid];
    }
    return length;
}