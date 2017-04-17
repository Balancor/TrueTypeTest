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
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540

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

    char* content = readNumberBytesFromFile(FONT_FILENAME, glyphDataRecord->offset + glyphOffset, 32);
    int16_t  numOfCountours = readTwoBytesAsUShort(content);

    Glyph* glyph = NULL;
    uint16_t  numOfPoints = 0;
    int16_t maxXCoord = 0, minXCoord = 0,
            maxYCoord = 0, minYCoord = 0;
    vector<QuadraticBezierCurve> curves;
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

        curves = ((SimpleGlyph*)glyph)->getQuadraticBezierCurves();
    } else {

    }
    printf("minXCoord: %d, minYCoord: %d\n", minXCoord, minYCoord);
    Bitmap* bitmap = new Bitmap(ppem, ppem);

    vector<QuadraticBezierCurve>::iterator it;
    for( it = curves.begin(); it != curves.end(); it++ ){
        Point *startPoint, *controlPoint, *endPoint;
        startPoint = new Point((it->startPoint->x - minXCoord) * scale,
                               (it->startPoint->y - minYCoord) * scale);
        printf("\nstartPoint:");
        startPoint->dump();

        controlPoint = new Point((it->controlPoint->x - minXCoord) * scale,
                               (it->controlPoint->y - minYCoord) * scale);
        printf("\ncontrolPoint:");
        printf("xCoord: %d\n", (it->controlPoint->x - minXCoord) * scale);
        controlPoint->dump();



        endPoint = new Point((it->endPoint->x - minXCoord) * scale,
                               (it->endPoint->y - minYCoord) * scale);
        printf("\nendPoint:");
        endPoint->dump();
        bitmap->drawQuadraticBezier(*startPoint, *controlPoint, *endPoint);
    }
    return bitmap;
}

void renderBitmap(){
    //汉字"中"的Unicode: 0x4E2D, "二" 0x4E8C, "暖" 0x6696  "人" 0x4EBA "又" 0x53C8
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

void testBitmap(){
    int bitmapWidth, bitmapHeight;
    bitmapHeight = WINDOW_HEIGHT;
    bitmapWidth = WINDOW_WIDTH;
    Bitmap* testBitmap = new Bitmap(WINDOW_WIDTH, WINDOW_HEIGHT);

    /*for test Bezier*/
    Point startPoint(100, 300);
    Point controlPoint(400, 300);
    Point endPoint(400,300);
    testBitmap->drawQuadraticBezier(startPoint, controlPoint, endPoint);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1 * bitmapWidth, bitmapWidth,
               -1 * bitmapHeight, bitmapHeight);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    uint32_t  offset = 0;

    for (int i = 0; i < bitmapHeight ; i++) {
        for (int j = 0; j < bitmapWidth; j++) {
            uint32_t  color = readFourBytesAsUInt((char*)(testBitmap->mRawData + offset));
            if(color) glVertex2i(j, i); // switch x, y , bitmap coord and openGL Screen coord are different
            offset += 4;
        }
    }
    glEnd();
    glFlush();

    glutSwapBuffers();
}

void renderBezier(){
    Point *bezierStartPoint, *bezierControlPoint, *bezierEndPoint;
    uint8_t bezierStartPointFlag, bezierControlPointFlag, bezierEndPointFla;


    int pointIndex = 0;
    int pointOfCountours = 24;
    int onCurvePoints = 2;
    for (int j = 0; j < pointOfCountours; ++j) {
        uint8_t  pointFlag = flags[pointIndex];


        if(pointFlag & SIMPLE_FLAG_ON_CUREVE != 0){
            onCurvePoints--;
        }



    }
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
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Sketch");
    glewInit();

    glClearColor(0.0,0.0,0.0,0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(renderBitmap);
    glutMainLoop();

    return 0;
}