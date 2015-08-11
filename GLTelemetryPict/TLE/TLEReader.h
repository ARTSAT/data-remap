//
//  TLEReader.h
//  Telemetry
//
//  Created by h on 7/1/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#ifndef __Telemetry__TLEReader__
#define __Telemetry__TLEReader__

#include <stdio.h>
#include <iostream>
#include <vector>


#include "stdafx.h"
#include "coreLib.h"
#include "cOrbit.h"
#include "telemetryReader.h"


using namespace Zeptomoby::OrbitTools;


typedef struct{

    cOrbit* orbit;
    unsigned long epochSecInUnixTime;

    
}TLE;



vector<TLE> openTLE();


class TLEManager {


public:

    vector<TLE> allTLEs;



    TLEManager(){
        allTLEs = openTLE();
    }


    int indexForTime( int targetTime ){
        int index = (int)allTLEs.size()-1;
        while ( allTLEs[index].epochSecInUnixTime > targetTime ) {
            index--;
        }
        return index;
    }



    cGeoTime geometryAtUnixTime( int unixtime ){

        static const float secInMin = 60.f;
        cJulian julianTime = cJulian( unixtime );
        int index = indexForTime(unixtime);

        if (index<0) {
            index = 0;
        }


        cOrbit* obt = allTLEs[index].orbit;
        //printf("index = %i, temp = %f\n\n",index,obt->TPlusEpoch(julianTime));

        double temp = obt->TPlusEpoch(julianTime)/secInMin;
        cEciTime t = obt->GetPosition( temp );
        cEciTime eciSDP4( t );
        cGeoTime geo(eciSDP4);



        return geo;
    }




};









#endif /* defined(__Telemetry__TLEReader__) */
