//
// Created by guoguo on 17-3-23.
//

#include "HeadTable.h"
#include "utils.h"
#include "GTrueType_defs.h"
#include "Base.h"

HeadTable::HeadTable(const char* fileName){
    int offset = 0;
    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* headTableRecord = directoryTable->getTableRecord(TABLE_TAG_HEAD);
    if(headTableRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }

    this->mOffset = headTableRecord->offset;
    char* content = readNumberBytesFromFile(fileName, mOffset, HEAD_TABLE_LENGTH);


    mVersion = readFourBytesAsUInt(content + offset);
    offset += 4;
    mFontVersion = readFourBytesAsUInt(content + offset);
    offset += 4;
    mCheckSumAdjustment = readFourBytesAsUInt(content + offset);
    offset += 4;
    mMagicNumber = readFourBytesAsUInt(content + offset);
    offset += 4;

    mFlags = readTwoBytesAsUShort(content + offset);
    offset += 2;
    mUnitsPerEm = readTwoBytesAsUShort(content + offset);
    offset += 2;

    uint64_t highInt = readFourBytesAsUInt(content + offset);
    offset += 4;
    uint64_t lowInt = readFourBytesAsUInt(content + offset);
    offset += 4;
    mCreated =  ((highInt << 32) & 0xFFFFFFFF) | lowInt ;


    highInt = readFourBytesAsUInt(content + offset);
    offset += 4;
    lowInt = readFourBytesAsUInt(content + offset);
    offset += 4;
    mModifie = ((highInt << 32) & 0xFFFFFFFF) | lowInt ;

    xMin = readTwoBytesAsShort(content + offset);
    offset += 2;
    yMin  = readTwoBytesAsShort(content + offset);
    offset += 2;
    xMax = readTwoBytesAsShort(content + offset);
    offset += 2;
    yMax = readTwoBytesAsShort(content + offset);
    offset += 2;

    mMacStyle = readTwoBytesAsUShort(content + offset);
    offset += 2;
    mLowestRecPPEM = readTwoBytesAsUShort(content + offset);
    offset += 2;
    mFontDirectionHint = readTwoBytesAsShort(content + offset);
    offset += 2;
    mIndexToLocFormat = readTwoBytesAsShort(content + offset);
    offset += 2;
    mGlyphDataFormat = readTwoBytesAsShort(content + offset);
    offset += 2;

    this->mLength = offset;
    free(content);
    content = NULL;
}

void  HeadTable::dump() {
    printf("Head Table: \n");
    printf("\tmVersion: %u.%u\n", (mVersion>>16 & 0xFFFF), (mVersion & 0xFFFF) );
    printf("\tmFontVersion: %u\n", mFontVersion);
    printf("\tmCheckSumAdjustment: %u\n", mCheckSumAdjustment);
    printf("\tmMagicNumber: %u\n", mMagicNumber);
    printf("\tmFlags: %u\n", mFlags);
    printf("\tmUnitsPerEm: %u\n", mUnitsPerEm);
    printf("\tmCreated: %llu\n", mCreated);
    printf("\tmModifie: %llu\n", mModifie);
    printf("\txMin: %d\n", xMin);
    printf("\tyMin: %d\n", yMin);
    printf("\txMax: %d\n", xMax);
    printf("\tyMax: %d\n", yMax);
    printf("\tmMacStyle: %u\n", mMacStyle);
    printf("\tmLowestRecPPEM: %u\n", mLowestRecPPEM);
    printf("\tmFontDirectionHint: %d\n", mFontDirectionHint);
    printf("\tmIndexToLocFormat: %d\n", mIndexToLocFormat);
    printf("\tmGlyphDataFormat: %d\n", mGlyphDataFormat);
}