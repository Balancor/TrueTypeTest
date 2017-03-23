#include <iostream>
#include "Base.h"
#include "utils.h"
#include "SegmentMappingTable.h"

#define FONT_FILENAME "resources/MSYHMONO.ttf"
using namespace std;


int main() {
/*
    char* content = readNumberBytesFromFile(FONT_FILENAME, 0, 1024);
    printf("fontFileName: %s\n", fontFileName);
    DirectoryTable *table = new DirectoryTable(FONT_FILENAME);
    free(content);
*/
    //CmapTable* cmapTable = getCmapTable(FONT_FILENAME);


    //EncodingTableRecord *encodingRecord = cmapTable->getEncodingRecord(3, 0);
    //EncodingTable* encodingTable;


    SegmentMappingTable* segmentMappingTable = new SegmentMappingTable(FONT_FILENAME, 3, 1);
    uint16_t  gid = segmentMappingTable->getGlyphIndex(0x6696);
    printf("glyph index: %u\n", gid);
    return 0;
}