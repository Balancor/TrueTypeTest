#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

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

int16_t *xCoordinates = NULL;
int16_t *yCoordinates = NULL;
uint16_t *endPtsOfContours = NULL;
uint16_t numberOfCountours = 0;
int16_t  numberOfPoint = 0;

void renderFunction()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.0, 1.0);//clear red

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2048, 2048, -2048, 2048);

    glLineWidth(1.0f);
    glColor3f(1.0, 0.0, 0.0);

    int pointIndex = 0;
    for (int i = 0; i < numberOfCountours ; ++i) {
        uint16_t pointOfCountours = endPtsOfContours[i] + 1;
        if( i > 0 ){
            pointOfCountours = endPtsOfContours[i] - endPtsOfContours[i - 1];
        }

        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < pointOfCountours; ++j) {
            glVertex2i(xCoordinates[pointIndex], yCoordinates[pointIndex]);
            pointIndex++;
        }
        glEnd();
        glFlush();
    }
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    SegmentMappingTable* segmentMappingTable = new SegmentMappingTable(FONT_FILENAME, 3, 1);
    uint16_t  gid = segmentMappingTable->getGlyphIndex(0x4E2D);//汉字"中"的Unicode: 0x4E2D, 0x4E8C
    HeadTable* headTable = new HeadTable(FONT_FILENAME);
    MaxpTable *maxpTable = new MaxpTable(FONT_FILENAME);
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
        xCoordinates = ((SimpleGlyph*)glyph)->getXCoords();
        yCoordinates = ((SimpleGlyph*)glyph)->getYCoords();
        endPtsOfContours = ((SimpleGlyph*)glyph)->endPtsOfContours;
        numberOfCountours = ((SimpleGlyph*)glyph)->numberOfCountours;
        numberOfPoint = ((SimpleGlyph*)glyph)->getNumOfPoints();
    } else {

    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(2048,2048);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Sketch");
    glewInit();


    glutDisplayFunc(renderFunction);
    glutMainLoop();

    return 0;
}