#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "truetype/Base.h"
#include "utils.h"
#include "truetype/GlyphData.h"
#include "FontUtils.h"

#define FONT_FILENAME "resources/MSYHMONO.ttf"
#define WINDOW_WIDTH  960
#define WINDOW_HEIGHT 540

#define FONT_SIZE 36
#define DEV_DPI 96
using namespace std;
FontUtils* mFontUtils;

void renderBitmap(){
    //汉字"中"的Unicode: 0x4E2D, "二" 0x4E8C, "暖" 0x6696  "人" 0x4EBA "又" 0x53C8
    Bitmap* fontBitmap = mFontUtils->getFontbitmap(0x6696);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int ortho2DWidth = 96;
    gluOrtho2D(-1 * ortho2DWidth, ortho2DWidth,
               -1 * ortho2DWidth, ortho2DWidth);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    uint32_t  offset = 0;

    for (int i = 0; i < fontBitmap->getHeight() ; i++) {
        for (int j = 0; j < fontBitmap->getWidth(); j++) {
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

    mFontUtils = new FontUtils(FONT_FILENAME);
    mFontUtils->initDevInfo(FONT_SIZE, DEV_DPI);

    glutDisplayFunc(renderBitmap);
    glutMainLoop();

    return 0;
}