//
// Created by guoguo on 17-3-22.
//

#ifndef GTRUETYPE_BASE_H
#define GTRUETYPE_BASE_H

#include <iostream>
#include <cmath>

typedef struct {
    uint32_t tag;
    uint32_t checkSum;
    uint32_t offset;
    uint32_t length;
}TableRecord;


class DirectoryTable {
protected:
    uint32_t 	sfntVersion;
    uint16_t 	mNumTables;
    uint16_t 	mSearchRange;
    uint16_t 	mEntrySelector;
    uint16_t 	mRangeShift;
    TableRecord** mTableRecords;
public:
    DirectoryTable(const char* fontFileName);
    TableRecord* getTableRecord(uint32_t tag);
    ~DirectoryTable(){
        printf("Destory Constructor\n");
        if(mTableRecords != NULL){
            for (int i = 0; i < mNumTables; ++i) {
                TableRecord* record = mTableRecords[i];
                free(record);
            }
            free(mTableRecords);
        }
    }
};



class Table{
protected:
    uint32_t mOffset;
    uint32_t mLength;
    char* mRawData;

public:
    ~Table(){

    }

    virtual void setOffset(uint32_t offset) = 0;
};

class Point {
public:
    int32_t x = 0;
    int32_t y = 0;
    Point(){};

    Point(int32_t xCoord, int32_t yCoord){
        this->x = xCoord;
        this->y = yCoord;
    }


    void setPoint(int32_t xCoord, int32_t yCoord){
        this->x = xCoord;
        this->y = yCoord;
    }

    inline bool operator == (const Point& point) const {
        return (x == point.x) && (y == point.y);
    }

    inline bool operator != (const Point& point) const {
        return !operator == (point);
    }

    inline bool isOrigin() const {
        return !(x|y);
    }

    inline bool operator < (const Point& point){
        return y < point.y || (y == point.y && x < point.x);
    }

    inline Point& operator - () {
        x = -x;
        y = -y;
        return *this;
    }

    inline Point operator - (const Point& point){
        const Point result(x - point.x, y - point.y);
        return result;
    }

    inline Point operator + (const Point& point){
        const Point result(x + point.x, y + point.y);
        return result;
    }

    inline Point& operator += (const Point& point){
        x += point.x;
        y += point.y;
        return  *this;
    }

    inline Point& operator -= (const Point& point){
        x -= point.x;
        y -= point.y;
        return  *this;
    }

    inline float length() {
        return  hypot(x, y);
    }
    inline float distanceTo(const Point& p){
        return (*this - p).length();
    }

    inline Point getLocationAtLine(const Point& p, float locationPercent){
        Point *result = new Point();
        int offsetX = p.x - x;
        int offsetY = p.y - y;
        result->x = (uint32_t)(x + offsetX * locationPercent + 0.5);
        result->y = (uint32_t)(y + offsetY * locationPercent + 0.5);
        return *result;
    }

    inline Point dump(){
        printf("Point(%d, %d)\n", x, y);
    }
};



#endif //GTRUETYPE_BASE_H
