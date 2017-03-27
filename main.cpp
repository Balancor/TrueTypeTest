#include <iostream>
#include "Base.h"
#include "utils.h"
#include "SegmentMappingTable.h"
#include "HeadTable.h"
#include "MaxpTable.h"
#include "LocaTable.h"
#include "GTrueType_defs.h"
#include "GlyphData.h"

#define FONT_FILENAME "resources/MSYHMONO.ttf"
using namespace std;


int main() {
    SegmentMappingTable* segmentMappingTable = new SegmentMappingTable(FONT_FILENAME, 3, 1);
    uint16_t  gid = segmentMappingTable->getGlyphIndex(0x6696);
    printf("main glyph index: %u\n", gid);

    HeadTable* headTable = new HeadTable(FONT_FILENAME);
//    headTable->dump();
    printf("main glyph mIndexToLocFormat: %u\n", headTable->mIndexToLocFormat);

    MaxpTable *maxpTable = new MaxpTable(FONT_FILENAME);
//    maxpTable->dump();

    LocaTable* locaTable = new LocaTable(FONT_FILENAME, headTable->mIndexToLocFormat == 0 , maxpTable->mNumGlyphs);



    DirectoryTable *directoryTable = new DirectoryTable(FONT_FILENAME);
    TableRecord* glyphDataRecord = directoryTable->getTableRecord(TABLE_TAG_GLFY);

    uint32_t  glyphOffset = locaTable->getGlyphOffset(gid);
    uint32_t glyphLength = locaTable->getGlyphLength(gid);
    char* content = readNumberBytesFromFile(FONT_FILENAME, glyphDataRecord->offset + glyphOffset, 32);
    int16_t  numOfCountours = readTwoBytesAsUShort(content);

    Glyph* glyph = NULL;
    if(numOfCountours >= 0){
        glyph = new SimpleGlyph(FONT_FILENAME, glyphDataRecord->offset + glyphOffset, glyphLength);
    } else {

    }

    return 0;
}