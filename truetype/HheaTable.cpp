//
// Created by guoguo on 17-4-5.
//

#include "HheaTable.h"
#include "../utils.h"
#include "GTrueType_defs.h"
#include "Base.h"

HheaTable::HheaTable(const char* fontFileName){

    DirectoryTable* directoryTable = getDirectoryTable(fontFileName);
    TableRecord* hheaTableRecord = directoryTable->getTableRecord(TABLE_TAG_HHEA);
    if(hheaTableRecord == NULL){
        printf("Cannot get the Cmap Record from %s\n", fontFileName);
        return ;
    }


    this->mLength = hheaTableRecord->length;
    this->mOffset = hheaTableRecord->offset;

    char* content = readNumberBytesFromFile(fontFileName, mOffset, mLength);

    int offset = 0;

    majorVersion = readTwoBytesAsUShort(content + offset);
    offset += sizeof(uint16_t);

    minorVersion = readTwoBytesAsUShort(content + offset);
    offset += sizeof(uint16_t);


    ascender = readTwoBytesAsShort(content + offset);
    offset += sizeof(uint16_t);

    descender = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    lineGap = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    advanceWidthMax = readTwoBytesAsUShort(content + offset);
    offset += sizeof(uint16_t);
    minLeftSideBearing = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    minRightSideBearing = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    xMaxExtent = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    caretSlopeRise = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    caretSlopeRun = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    caretOffset = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    reserved1 = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    reserved2 = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    reserved3 = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    reserved4 = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    metricDataFormat = readTwoBytesAsShort(content + offset);
    offset += sizeof(int16_t);
    numberOfHMetrics = readTwoBytesAsUShort(content + offset);
    offset += sizeof(uint16_t);
}