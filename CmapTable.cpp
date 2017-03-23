//
// Created by guoguo on 17-3-22.
//
#include <cstring>
#include "GTrueType_defs.h"
#include "CmapTable.h"
#include "utils.h"
#include "SegmentMappingTable.h"

CmapTable::CmapTable(const char* fileName){
    printf("CmapTable Constructor, fileName: %s\n", fileName);
    int offset = 0;
    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* cmapRecord = directoryTable->getTableRecord(TABLE_TAG_CMAP);
    if(cmapRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }

    const char* const content = readFromFontFile(fileName);
    this->mOffset = cmapRecord->offset;

    printf("Cmap Table mOffset: %u\n", mOffset);

    mVersion = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mNumTable = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    printf("Cmap Table mVersion: 0x%x mNumTable: %u\n",mVersion, mNumTable);

    mEncodingTableRecords = (EncodingTableRecord**)malloc(sizeof(void*) * mNumTable);
    mSubTables = (EncodingTable**)malloc(sizeof(void*)*mNumTable);

    for (int i = 0; i < mNumTable; ++i) {
        EncodingTableRecord* record = (EncodingTableRecord*)
                malloc(sizeof(EncodingTableRecord));
        record->platformID = readTwoBytesAsUShort(content + mOffset + offset);
        offset += 2;
        record->encodingID = readTwoBytesAsUShort(content + mOffset + offset);
        offset += 2;
        record->offset = readFourBytesAsUInt(content + mOffset + offset);
        offset += 4;
        mEncodingTableRecords[i] = record;

    }
    this->mLength = offset;


    this->mRawData = (char*)malloc(sizeof(char) * (mLength + 1));
    for (int j = 0; j < mLength; ++j) {
        mRawData[j] = content[j];
    }
    strncpy(mRawData, (content + mOffset), mLength);
    mRawData[mLength] = '\0';

    delete((void*)directoryTable);
}

EncodingTableRecord* CmapTable::getEncodingRecord(uint16_t platformId, uint16_t encodingId){
    if(mEncodingTableRecords){
        for (int i = 0; i < mNumTable; ++i) {
            EncodingTableRecord* record = mEncodingTableRecords[i];
            if(platformId == record->platformID &&
               encodingId == record->encodingID){
                return record;
            }
        }
    }
    return NULL;
}