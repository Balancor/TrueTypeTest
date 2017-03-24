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
    } else {
        count = numGlyphs * sizeof(uint32_t);
    }

    char* locaContent = readNumberBytesFromFile(fileName, mOffset, count);

    mGlyphRecords = (GlyphRecord**) malloc(sizeof(void*) * (mNumGlyphs + 1));

    printf("mOffset: %u\n",mOffset);
    for (int i = 0; i < mNumGlyphs; ++i) {
        GlyphRecord* record = (GlyphRecord*)malloc(sizeof(GlyphRecord));
        if(isShortVersion){
            record->offset = readTwoBytesAsUShort(locaContent + offsetInternal);
            offsetInternal += 2;
            uint16_t  nextOffset = readTwoBytesAsUShort(locaContent + offsetInternal);
            record->length = nextOffset - record->offset;

        } else {
            record->offset = readFourBytesAsUInt(locaContent + offsetInternal);
            offsetInternal += 4;

            uint16_t  nextOffset = readTwoBytesAsUShort(locaContent + offsetInternal);
            record->length = nextOffset - record->offset;
        }
        mGlyphRecords[i] = record;
        if(i < 20){
            printf("Offset: %u, Length: %u\n",record->offset, record->length);
        }
    }

    GlyphRecord* record = (GlyphRecord*)malloc(sizeof(GlyphRecord));
    record->offset = offsetInternal;
    record->length = count - offsetInternal;
    mGlyphRecords[mNumGlyphs] = record;


    free(locaContent);
    locaContent = NULL;
}