#include <iostream>
#include "Base.h"
#include "utils.h"
#include "SegmentMappingTable.h"
#include "HeadTable.h"
#include "MaxpTable.h"
#include "LocaTable.h"

#define FONT_FILENAME "resources/MSYHMONO.ttf"
using namespace std;


int main() {
//    SegmentMappingTable* segmentMappingTable = new SegmentMappingTable(FONT_FILENAME, 3, 1);
//    uint16_t  gid = segmentMappingTable->getGlyphIndex(0x6696);
//    printf("main glyph index: %u\n", gid);

    HeadTable* headTable = new HeadTable(FONT_FILENAME);
//    headTable->dump();

    MaxpTable *maxpTable = new MaxpTable(FONT_FILENAME);
//    maxpTable->dump();

    LocaTable* locaTable = new LocaTable(FONT_FILENAME, headTable->mIndexToLocFormat , maxpTable->mNumGlyphs);

    return 0;
}