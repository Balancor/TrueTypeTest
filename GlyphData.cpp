//
// Created by guoguo on 17-3-27.
//

#include "GlyphData.h"
#include "Base.h"
#include "utils.h"
#include "GTrueType_defs.h"

SimpleGlyph::SimpleGlyph(const char* fileName, uint32_t offset, uint32_t length){
    char* content = readNumberBytesFromFile(fileName, offset, length);

    int offsetInternal = 0;
    numberOfCountours = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    xMin = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    yMin = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    xMax = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;
    yMax = readTwoBytesAsShort(content + offsetInternal);
    offsetInternal += 2;

    endPtsOfContours = (uint16_t*)malloc(sizeof(uint16_t) * numberOfCountours);
    for (int i = 0; i < numberOfCountours; ++i) {
        endPtsOfContours[i] = readTwoBytesAsUShort(content + offsetInternal);
        offsetInternal += 2;
    }

    numberOfPoints = endPtsOfContours[numberOfCountours - 1] + 1;

    instructionLength = readTwoBytesAsUShort(content + offsetInternal);
    offsetInternal += 2;

    instructions = (uint8_t*)malloc(sizeof(uint8_t) * instructionLength);
    for (int j = 0; j < instructionLength; ++j) {
        instructions[j] = *(content + offsetInternal);
        offsetInternal ++;
    }

    int lengthOfFlags = 0;
    uint8_t repeatedCount = 0;
    uint8_t flag = 0;
    flags = (uint8_t*)malloc(sizeof(uint8_t) * numberOfPoints);
    for (int pointIndex = 0; pointIndex < numberOfPoints; pointIndex++) {
        if (repeatedCount == 0) {
            flag = (uint8_t)(*(content + offsetInternal));
            offsetInternal ++;
            flags[lengthOfFlags++] = flag;

            if ((flag & SIMPLE_GLYPH_FLAG_REPEAT) == SIMPLE_GLYPH_FLAG_REPEAT) {
                repeatedCount = (uint8_t)(*(content + offsetInternal));
                offsetInternal++;
                lengthOfFlags++;
            }
        } else {
            repeatedCount--;
        }
    }



}