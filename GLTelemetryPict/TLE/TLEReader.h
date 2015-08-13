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


        cSite *site;

    //L Latitude : 35.610603 Longitude : 139.351124 Altitude : 148[m]

    TLEManager(){
        allTLEs = openTLE();

        site = new cSite(35.610603, 139.351124, 0.148);



    }


    int indexForTime( int targetTime ){
        int index = (int)allTLEs.size()-1;
        while ( allTLEs[index].epochSecInUnixTime > targetTime ) {
            index--;
        }
        return index;
    }




    cTopo lookingAngle( int targetTime ){


        static const float secInMin = 60.f;
        cJulian julianTime = cJulian( targetTime );
        int index = indexForTime(targetTime);

        if (index<0) {
            index = 0;
        }


        cOrbit* obt = allTLEs[index].orbit;
        //printf("index = %i, temp = %f\n\n",index,obt->TPlusEpoch(julianTime));

        double temp = obt->TPlusEpoch(julianTime)/secInMin;
        cEciTime t = obt->GetPosition( temp );
        cEciTime eciSDP4( t );


        cTopo topo = site->GetLookAngle( t );

        return topo;
    }


    float elevation( cTopo topo ){
        return topo.ElevationDeg();
    }

    bool isVisible( int targetTime ){

        float ele = elevation( lookingAngle(targetTime) );


        return ele>0. ? true : false;
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


    int firstUnixEpoch(){
        int tmp = allTLEs[0].epochSecInUnixTime;
        return tmp;
    }



};









#endif /* defined(__Telemetry__TLEReader__) */
