//
// Created by guoguo on 17-4-17.
//

#ifndef GTRUETYPE_GLYPH_H
#define GTRUETYPE_GLYPH_H


#include <cstdint>
#include "truetype/GlyphData.h"

class Glyph {
private:
    uint32_t  mCharCode;

    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;


    vector<QuadraticBezierCurve> mQuadraticBezierCurves;

    void init();
public:
    Glyph(uint32_t charCode){
        mCharCode = charCode;
    }


    vector<QuadraticBezierCurve> getQuadraticBezierCurves(){
        return mQuadraticBezierCurves;
    }

    int16_t  getXMin(){
        return xMin;
    }
    int16_t  getXMax(){
        return xMax;
    }
    int16_t  getYMin(){
        return yMin;
    }
    int16_t  getYMax(){
        return yMax;
    }

    void setXMin(int16_t val){
        xMin = val;
    };

    void setYMin(int16_t val){
        yMin = val;
    };

    void setXMax(int16_t val){
        xMax = val;
    };

    void setYMax(int16_t val){
        yMax = val;
    };

    void initCurves(vector<QuadraticBezierCurve> curves){
        this->mQuadraticBezierCurves = curves;
    }

};


#endif //GTRUETYPE_GLYPH_H
