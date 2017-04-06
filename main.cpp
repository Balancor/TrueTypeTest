#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstring>

#include "Base.h"
#include "utils.h"
#include "SegmentMappingTable.h"
#include "HeadTable.h"
#include "MaxpTable.h"
#include "LocaTable.h"
#include "GTrueType_defs.h"
#include "GlyphData.h"
#include "Bitmap.h"
#include "HmtxTable.h"
#include "HheaTable.h"

#define FONT_FILENAME "resources/MSYHMONO.ttf"


using namespace std;

int16_t *xCoordinates = NULL;
int16_t *yCoordinates = NULL;
uint16_t *endPtsOfContours = NULL;
uint16_t numberOfCountours = 0;
uint8_t *flags = NULL;

int uppem = 0;
float ppem = 0.0f;
int dpi = 96;
int fontSize = 72;
float scale = 0.0f;
bool* dirtyPoint;


static GLuint fontTextureId;


Bitmap* getFontbitmap(uint32_t symbolCode){
    SegmentMappingTable* segmentMappingTable = new SegmentMappingTable(FONT_FILENAME, 3, 1);
    uint16_t  gid = segmentMappingTable->getGlyphIndex(symbolCode);
    HeadTable* headTable = new HeadTable(FONT_FILENAME);
    uppem = headTable->mUnitsPerEm;
    ppem = fontSize * dpi / 72;
    scale = ppem / uppem;
    printf("ppem: %f\n", ppem);
    printf("grid-coord to pixel-coord Scale: %f\n", scale);


    MaxpTable *maxpTable = new MaxpTable(FONT_FILENAME);
    LocaTable* locaTable = new LocaTable(FONT_FILENAME, headTable->mIndexToLocFormat == 0 , maxpTable->mNumGlyphs);

    HheaTable* hheaTable = new HheaTable(FONT_FILENAME);
    HmtxTable* hmtxTable = new HmtxTable(FONT_FILENAME, hheaTable->numberOfHMetrics, maxpTable->mNumGlyphs);



    DirectoryTable *directoryTable = new DirectoryTable(FONT_FILENAME);
    TableRecord* glyphDataRecord = directoryTable->getTableRecord(TABLE_TAG_GLFY);

    uint32_t  glyphOffset = locaTable->getGlyphOffset(gid);
    uint32_t glyphLength = locaTable->getGlyphLength(gid);

    uint16_t advanceWidth = hmtxTable->getAdvanceWidth(gid);
    int16_t leftSideBearing = hmtxTable->getLeftSideBearing(gid);
    printf("advanceWidth: %u, leftSideBearing: %d\n", advanceWidth, leftSideBearing);
    char* content = readNumberBytesFromFile(FONT_FILENAME, glyphDataRecord->offset + glyphOffset, 32);
    int16_t  numOfCountours = readTwoBytesAsUShort(content);

    Glyph* glyph = NULL;
    uint16_t  numOfPoints = 0;
    int16_t maxXCoord = 0, minXCoord = 0,
            maxYCoord = 0, minYCoord = 0;
    if(numOfCountours >= 0){
        glyph = new SimpleGlyph(FONT_FILENAME, glyphDataRecord->offset + glyphOffset, glyphLength);
        xCoordinates = ((SimpleGlyph*)glyph)->getXCoords();
        yCoordinates = ((SimpleGlyph*)glyph)->getYCoords();
        endPtsOfContours = ((SimpleGlyph*)glyph)->endPtsOfContours;
        numberOfCountours = ((SimpleGlyph*)glyph)->numberOfCountours;
        numOfPoints = ((SimpleGlyph*)glyph)->numberOfPoints;
        flags = ((SimpleGlyph*)glyph)->flags;
        maxXCoord = ((SimpleGlyph*)glyph)->getMaxXCoord();
        minXCoord = ((SimpleGlyph*)glyph)->getMinXCoord();
        maxYCoord = ((SimpleGlyph*)glyph)->getMaxYCoord();
        minYCoord = ((SimpleGlyph*)glyph)->getMinYCoord();
    } else {

    }

    Bitmap* bitmap = new Bitmap(ppem, ppem);

    int numOfBitmp = 0;
    int16_t  prevPointX = 0, prevPointY = 0;
    int16_t  targetX = 0, targetY = 0;
    int16_t  countoursStartX = 0, countoursStartY = 0,
             countoursEndX = 0, countoursEndY = 0;
    int pointIndex = 0;
    for (int i = 0; i < numberOfCountours ; ++i) {
        uint16_t pointOfCountours = endPtsOfContours[i] + 1;
        if( i > 0 ){
            pointOfCountours = endPtsOfContours[i] - endPtsOfContours[i - 1];
        }

        for (int j = 0; j < pointOfCountours; ++j) {
            targetX = (int16_t)((xCoordinates[pointIndex] - minXCoord) * scale );
            targetY = (int16_t)((yCoordinates[pointIndex] - minYCoord) * scale );
            if (targetX < ppem && targetY < ppem
                && targetX >= 0 && targetY >= 0){
                numOfBitmp++;
                if(j > 0){
                    bitmap->drawLine(prevPointX, prevPointY, targetX, targetY);
                }
            }
            if(j == 0){
                countoursStartX = targetX; countoursStartY = targetY;
            } else if (j == (pointOfCountours - 1)){
                countoursEndX = targetX; countoursEndY = targetY;
                bitmap->drawLine(countoursEndX,countoursEndY,countoursStartX, countoursStartY);
            }


            prevPointX = targetX;
            prevPointY = targetY;

            pointIndex++;
        }

    }


    return bitmap;
}

void renderBitmap(){
    //汉字"中"的Unicode: 0x4E2D, "二" 0x4E8C, "暖" 0x6696
    Bitmap* fontBitmap = getFontbitmap(0x6696);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int ortho2DWidth = 96;
    gluOrtho2D(-1 * ortho2DWidth, ortho2DWidth,
               -1 * ortho2DWidth, ortho2DWidth);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    uint32_t  offset = 0;

    for (int i = 0; i < ppem ; i++) {
        for (int j = 0; j < ppem; j++) {
            uint32_t  color = readFourBytesAsUInt((char*)(fontBitmap->mRawData + offset));
            if(color) glVertex2i(j, i); // switch x, y , bitmap coord and openGL Screen coord are different
            offset += 4;
        }
    }
    glEnd();
    glFlush();

    glutSwapBuffers();
}


void renderFunction()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, fontTextureId);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-96, 96, -96, 96);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);  glVertex2i(-90, -90);
    glTexCoord2f(1.0, 0.0);  glVertex2i( 90, -90);

    glTexCoord2f(1.0, 1.0);  glVertex2i( 90,  90);
    glTexCoord2f(0.0, 1.0);  glVertex2i(-90,  90);
    glEnd();

    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(960,540);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Sketch");
    glewInit();



    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    /*
    //汉字"中"的Unicode: 0x4E2D, 0x4E8C
    Bitmap* fontBitmap = getFontbitmap(0x4E2D);



    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &fontTextureId);

    glBindTexture(GL_TEXTURE_2D, fontTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 ppem,
                 ppem,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 fontBitmap);
*/

//    glutDisplayFunc(renderFunction);
    glutDisplayFunc(renderBitmap);
    glutMainLoop();

    return 0;
}