// Created by guoguo on 17-3-23.
#include "Base.h"
#include "utils.h"
#include "GTrueType_defs.h"
DirectoryTable::DirectoryTable(const char* fontFileName){
    char* content = readNumberBytesFromFile(fontFileName, 0, DIRECTORY_TABLE_LENGTH); //readFromFontFile(fontFileName);
    int offset = 0;
    this->sfntVersion = readFourBytesAsUInt(content + offset);
    offset += 4;
    this->mNumTables = readTwoBytesAsUShort(content + offset);
    offset += 2;
    this->mSearchRange = readTwoBytesAsUShort(content + offset);
    offset += 2;
    this->mEntrySelector = readTwoBytesAsUShort(content + offset);
    offset += 2;
    this->mRangeShift = readTwoBytesAsUShort(content + offset);
    offset += 2;
    free(content);
    content = NULL;

    char* recordContent = readNumberBytesFromFile(fontFileName, offset, TABLE_RECORD_LENGTH * mNumTables);
    offset = 0;
    mTableRecords = (TableRecord**)malloc(sizeof(void*) * mNumTables);
    for (int i = 0; i < mNumTables; ++i) {
        TableRecord *record =  (TableRecord*)malloc(sizeof(TableRecord));
        record->tag = readFourBytesAsUInt(recordContent + offset);
        offset += 4;
        record->checkSum = readFourBytesAsUInt(recordContent + offset);
        offset += 4;
        record->offset = readFourBytesAsUInt(recordContent + offset);
        offset += 4;
        record->length = readFourBytesAsUInt(recordContent + offset);
        offset += 4;

//        printf("Tag: %c%c%c%c, offset: %u\n",
//               record->tag >> 24 & 0xFF,record->tag >> 16 & 0xFF,
//               record->tag >> 8 & 0xFF,record->tag & 0xFF,
//               record->offset);

        this->mTableRecords[i] = record;
    }
    free(content);
    content = NULL;
}

TableRecord* DirectoryTable::getTableRecord(uint32_t tag){
    if(mTableRecords){
        for (int i = 0; i < mNumTables; ++i) {
            TableRecord *record = mTableRecords[i];
            if(record == NULL){
                break;
            }

            if(!(tag - record->tag)){
//                printf("return Tag: %c%c%c%c, offset: %u\n",
//                       record->tag >> 24 & 0xFF,record->tag >> 16 & 0xFF,
//                       record->tag >> 8 & 0xFF,record->tag & 0xFF,
//                       record->offset);
                return record;
            }
        }
    }
    return NULL;
}