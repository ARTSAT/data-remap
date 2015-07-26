//
//  telemetryReaderAzimuth.h
//  GLTelemetryPict
//
//  Created by Koichiro Mori on 2015/07/26.
//  Copyright (c) 2015年 h. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include "telemetryReader.h"

using namespace std;

typedef enum {
    TLM_AZM_TIME_UNIX = 0,
    TLM_AZM_TIME_ALT = 1,
    TLM_AZM_TIME_AZ = 2,
}telemetryAzimuthCSVIndex;

typedef struct{
    int unixTime;
    float altitude;
    float azimuth;
}telemetryAzimuth;


class telemetryReaderAzimuth {

public:
    telemetryReaderAzimuth(const char * path) {
        telemetries_az = telemetryFromFileAz(path);
    }
    ~telemetryReaderAzimuth() {};
    vector<telemetryAzimuth> telemetries_az;
    vector<telemetryAzimuth> telemetryFromFileAz( const char * path ) {
        vector<telemetryAzimuth> telemetries;
        
        
        FILE *fpr = fopen( path, "r");
        
        char *dummy[256];
        char line[4096];
        while (fgets(line, 4096, fpr) != NULL) {
            
            dummy[0] = strtok(line, ",");
            for (int i=1; i<256; ++i) {
                dummy[i] = strtok(NULL, ",");
            }
            
            telemetryAzimuth tl;
            
            tl.unixTime = atoi(dummy[ TLM_AZM_TIME_UNIX ]);
            tl.altitude  = atof(dummy[ TLM_AZM_TIME_ALT ]);
            tl.azimuth = atof(dummy[TLM_AZM_TIME_AZ]);
            
            telemetries.push_back(tl);
            
        }
        
        fclose(fpr);
        
        //cout << telemetries.size() << " telemetries" << endl;
        
        return telemetries;
    };
    vector<telemetryAzimuth> telemetriesInRangeAz( int secStart, int duration ){
        
        vector<telemetryAzimuth> telems;
        for (int i=0; i<telemetries_az.size(); ++i) {
            
            int timeFromLaunch =  telemetries_az[i].unixTime;
            
            if (timeFromLaunch >= secStart) {
                if (timeFromLaunch < secStart + duration) {
                    telems.push_back(telemetries_az[i]);
                }
            }
        }
        
        return telems;
    }

};