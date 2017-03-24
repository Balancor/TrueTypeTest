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

    mGlyphRecords = (GlyphRecord**) malloc(sizeof(void*) * mNumGlyphs);

    int preOffset = 0;
    for (int i = 0; i < mNumGlyphs; ++i) {
        GlyphRecord* record = (GlyphRecord*)malloc(sizeof(GlyphRecord));
        if(isShortVersion){
            record->offset = readTwoBytesAsUShort(locaContent + offsetInternal);
            record->length = record->offset - preOffset;
            offsetInternal += 2;
            preOffset = record->offset;
        } else {
            record->offset = readFourBytesAsUInt(locaContent + offsetInternal);
            record->length = record->offset - preOffset;
            offsetInternal += 4;
            preOffset = record->offset;
        }
        if(i < 20)
            printf("offset: %u, length: %u\n", record->offset, record->length);
    }

    free(locaContent);
    locaContent = NULL;
}