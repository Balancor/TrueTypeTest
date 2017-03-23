//
// Created by guoguo on 17-3-23.
//
#include "GTrueType_defs.h"
#include "MaxpTable.h"
#include "utils.h"
MaxpTable::MaxpTable(const char* fileName){
    printf("CmapTable Constructor, fileName: %s\n", fileName);
    int offset = 0;
    DirectoryTable* directoryTable = getDirectoryTable(fileName);
    TableRecord* maxpRecord = directoryTable->getTableRecord(TABLE_TAG_MAXP);
    if(maxpRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fileName);
        return ;
    }

    const char* const content = readFromFontFile(fileName);
    this->mOffset = maxpRecord->offset;

    mMaxpTableVersion = readFourBytesAsUInt(content + mOffset + offset);
    offset += 2;
    mNumGlyphs = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxPoints = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxContours = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxCompositePoints = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxCompositeContours = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxZones = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxTwilightPoints = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxStorage = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxFunctionDefs = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxInstructionDefs = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxStackElements = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxSizeOfInstructions = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxComponentElements = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;
    mMaxComponentDepth = readTwoBytesAsUShort(content + mOffset + offset);
    offset += 2;

    this->mLength = offset;
}