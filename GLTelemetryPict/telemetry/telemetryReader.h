//
//  telemetryReader.h
//  Telemetry
//
//  Created by h on 7/1/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#ifndef __Telemetry__telemetryReader__
#define __Telemetry__telemetryReader__

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef enum {

    TLM_TIME_OBC = 0,
    TLM_TIME_UNIX,
    TLM_VOL_BAT,
    TLM_VOL_BUS,
    TLM_CUR_POWER_OBC,
    TLM_CUR_BUS,
    TLM_CUR_BAT,
    TLM_CUR_SOLAR,
    TLM_CUR_SOLAR_mY2,
    TLM_CUR_SOLAR_pY2,
    TLM_CUR_SOLAR_mZ,
    TLM_CUR_SOLAR_pZ,
    TLM_CUR_SOLAR_mY1,
    TLM_CUR_SOLAR_pY1,
    TLM_CUR_SOLAR_mX,
    TLM_CUR_SOLAR_pX,
    TLM_CUR_MAIN_OBC,
    TLM_TMP_BAT_1,
    TLM_TMP_BAT_2,
    TLM_TMP_BAT_3,
    TLM_TMP_SOLAR_pX,
    TLM_TMP_SOLAR_mX,
    TLM_TMP_SOLAR_pY1,
    TLM_TMP_SOLAR_pY2,
    TLM_TMP_SOLAR_mY1,
    TLM_TMP_SOLAR_mY2,
    TLM_TMP_SOLAR_pZ1,
    TLM_TMP_SOLAR_pZ2,
    TLM_TMP_SOLAR_mZ1,
    TLM_TMP_SOLAR_mZ2,
    TLM_TMP_POWER_OBC,
    TLM_TMP_MISS_OBC,
    TLM_TMP_CW_TX_OBC,
    TLM_TMP_RX,
    TLM_TMP_MAIN_OBC,
    TLM_GYR_X,
    TLM_GYR_Y,
    TLM_GYR_Z,
    TLM_MAG_X,
    TLM_MAG_Y,
    TLM_MAG_Z,
    TLM_ELEM_COUNT,

}telemetryCSVIndex;


typedef struct{

    int obcTime;
    int unixTime;

    float volt_bat;
    float volt_bus;

    float cur_powerOBC;
    float cur_bus;
    float cur_bat;
    float cur_solar;
    float cur_solar_mX;
    float cur_solar_pX;
    float cur_solar_mY1;
    float cur_solar_pY1;
    float cur_solar_mY2;
    float cur_solar_pY2;
    float cur_solar_mZ;
    float cur_solar_pZ;
    float cur_mainOBC;

    float tmp_bat1;
    float tmp_bat2;
    float tmp_bat3;
    float tmp_solar_mX;
    float tmp_solar_pX;
    float tmp_solar_mY1;
    float tmp_solar_pY1;
    float tmp_solar_mY2;
    float tmp_solar_pY2;
    float tmp_solar_mZ1;
    float tmp_solar_pZ1;
    float tmp_solar_mZ2;
    float tmp_solar_pZ2;
    float tmp_powerOBC;
    float tmp_missionOBC;
    float tmp_CwTxOBC;
    float tmp_RX;
    float tmp_mainOBC;

    float gyro[3];
    float magn[3];



}telemetry;

int unixTimeFromDate( int year, int month, int day, int hour, int min, int sec);

vector<telemetry> telemetryFromFile( const char * path );
void dumpTelemetry( telemetry *tl );


class telemetryReader {


public:


    vector<telemetry> telemetries;


    telemetryReader(const char* path){
        telemetries = telemetryFromFile(path);
    }

    ~telemetryReader(){}



    int firstUnixTime(){
        return telemetries[0].unixTime;
    }

    int lastUnixTime(){
        return telemetries[telemetries.size()-1].unixTime;
    }

    int durationUnixTime(){
        return lastUnixTime() - firstUnixTime();
    }



    vector<telemetry> telemetriesInRange( int secStart, int duration ){

        vector<telemetry> telems;
        for (int i=0; i<telemetries.size(); ++i) {

            int timeFromLaunch =  telemetries[i].unixTime;// - firstUnixTime();

            if (timeFromLaunch >= secStart) {
                if (timeFromLaunch < secStart + duration) {
                    telems.push_back(telemetries[i]);
                }
            }
        }

        return telems;
    }


    
};








#endif /* defined(__Telemetry__telemetryReader__) */
