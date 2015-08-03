//
//  telemetryReader.cpp
//  Telemetry
//
//  Created by h on 7/1/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#include "telemetryReader.h"


int unixTimeFromDate( int year, int month, int day, int hour, int min, int sec){


    unsigned long dateInUnixTime;
    time_t rawtime;
    struct tm * timeinfo;

    //int year=2014, month=2, day=27, hour = 0, min = 0, sec = 0;

    /* get current timeinfo: */
    time ( &rawtime ); //or: rawtime = time(0);
    /* convert to struct: */
    timeinfo = localtime ( &rawtime );

    /* now modify the timeinfo to the given date: */
    timeinfo->tm_year   = year - 1900;
    timeinfo->tm_mon    = month - 1;    //months since January - [0,11]
    timeinfo->tm_mday   = day;          //day of the month - [1,31]
    timeinfo->tm_hour   = hour;         //hours since midnight - [0,23]
    timeinfo->tm_min    = min;          //minutes after the hour - [0,59]
    timeinfo->tm_sec    = sec;          //seconds after the minute - [0,59]

    /* call mktime: create unix time stamp from timeinfo struct */
    dateInUnixTime = mktime ( timeinfo );

    //printf ("Until the given date, since 1970/01/01 %lu seconds have passed.\n", dateInUnixTime);

    return (int)dateInUnixTime;
    
}


float averageTMPofSolarPanels(telemetry telem){

    float avr = 0.f;

    avr+=telem.tmp_solar_mX;
    avr+=telem.tmp_solar_pX;
    avr+=telem.tmp_solar_mY1;
    avr+=telem.tmp_solar_pY1;
    avr+=telem.tmp_solar_mY2;
    avr+=telem.tmp_solar_pY2;
    avr+=telem.tmp_solar_mZ1;
    avr+=telem.tmp_solar_pZ1;
    avr+=telem.tmp_solar_mZ2;
    avr+=telem.tmp_solar_pZ2;

    avr/=10.f;
    return avr;
}

float averageTMPofSolarPanelX(telemetry telem){

    float avr = 0.f;

    avr+=telem.tmp_solar_mY1;
    avr+=telem.tmp_solar_pY1;
    avr+=telem.tmp_solar_mY2;
    avr+=telem.tmp_solar_pY2;

    avr/=4.f;
    return avr;

}


float averageTMPofSolarPanelY(telemetry telem){

    float avr = 0.f;

    avr+=telem.tmp_solar_mZ1;
    avr+=telem.tmp_solar_pZ1;
    avr+=telem.tmp_solar_mZ2;
    avr+=telem.tmp_solar_pZ2;

    avr/=4.f;
    return avr;
    
}


float averageTMPofSolarPanelZ(telemetry telem){

    float avr = 0.f;

    avr+=telem.tmp_solar_mX;
    avr+=telem.tmp_solar_pX;

    avr/=2.f;
    return avr;
    
}

float averageTMPofBatteries(telemetry telem){

    float avr = 0.f;

    avr+=telem.tmp_bat1;
    avr+=telem.tmp_bat2;
    avr+=telem.tmp_bat3;

    avr/=3.f;
    return avr;
}



vector<telemetry> telemetryFromFile( const char * path ){

    vector<telemetry> telemetries;


    FILE *fpr = fopen( path, "r");

    char *dummy[256];
    char line[4096];
    while (fgets(line, 4096, fpr) != NULL) {

        dummy[0] = strtok(line, ",");
        for (int i=1; i<256; ++i) {
            dummy[i] = strtok(NULL, ",");
        }

        telemetry tl;

        tl.obcTime  = atoi(dummy[ TLM_TIME_OBC]);
        tl.unixTime = atoi(dummy[ TLM_TIME_UNIX ]);

        tl.volt_bat  = atof(dummy[ TLM_VOL_BAT ]);
        tl.volt_bus  = atof(dummy[ TLM_VOL_BUS ]);
        tl.cur_powerOBC = atof(dummy[ TLM_CUR_POWER_OBC ]);
        tl.cur_bus      = atof(dummy[ TLM_CUR_BUS ]);
        tl.cur_bat      = atof(dummy[ TLM_CUR_BAT ]);
        tl.cur_solar    = atof(dummy[ TLM_CUR_SOLAR ]);
        tl.cur_solar_mX = atof(dummy[ TLM_CUR_SOLAR_mX ]);
        tl.cur_solar_pX = atof(dummy[ TLM_CUR_SOLAR_pX ]);
        tl.cur_solar_mY1 = atof(dummy[ TLM_CUR_SOLAR_mY1 ]);
        tl.cur_solar_pY1 = atof(dummy[ TLM_CUR_SOLAR_pY1 ]);
        tl.cur_solar_mY2 = atof(dummy[ TLM_CUR_SOLAR_mY2 ]);
        tl.cur_solar_pY2 = atof(dummy[ TLM_CUR_SOLAR_pY2 ]);
        tl.cur_solar_mZ = atof(dummy[ TLM_CUR_SOLAR_mZ ]);
        tl.cur_solar_pZ = atof(dummy[ TLM_CUR_SOLAR_pZ ]);
        tl.cur_mainOBC  = atof(dummy[ TLM_CUR_MAIN_OBC ]);

        tl.tmp_bat1  = atof(dummy[ TLM_TMP_BAT_1 ]);
        tl.tmp_bat2  = atof(dummy[ TLM_TMP_BAT_2 ]);
        tl.tmp_bat3  = atof(dummy[ TLM_TMP_BAT_3 ]);
        tl.tmp_solar_mX  = atof(dummy[ TLM_TMP_SOLAR_mX ]);
        tl.tmp_solar_pX  = atof(dummy[ TLM_TMP_SOLAR_pX ]);
        tl.tmp_solar_mY1  = atof(dummy[ TLM_TMP_SOLAR_mY1 ]);
        tl.tmp_solar_pY1  = atof(dummy[ TLM_TMP_SOLAR_pY1 ]);
        tl.tmp_solar_mY2  = atof(dummy[ TLM_TMP_SOLAR_mY2 ]);
        tl.tmp_solar_pY2  = atof(dummy[ TLM_TMP_SOLAR_pY2 ]);
        tl.tmp_solar_mZ1  = atof(dummy[ TLM_TMP_SOLAR_mZ1 ]);
        tl.tmp_solar_pZ1  = atof(dummy[ TLM_TMP_SOLAR_pZ1 ]);
        tl.tmp_solar_mZ2  = atof(dummy[ TLM_TMP_SOLAR_mZ2 ]);
        tl.tmp_solar_pZ2  = atof(dummy[ TLM_TMP_SOLAR_pZ2 ]);
        tl.tmp_powerOBC     = atof(dummy[ TLM_TMP_POWER_OBC ]);
        tl.tmp_missionOBC   = atof(dummy[ TLM_TMP_MISS_OBC ]);
        tl.tmp_CwTxOBC      = atof(dummy[ TLM_TMP_CW_TX_OBC ]);
        tl.tmp_RX           = atof(dummy[ TLM_TMP_RX ]);
        tl.tmp_mainOBC      = atof(dummy[ TLM_TMP_MAIN_OBC ]);

        tl.magn[0]  = atof(dummy[ TLM_MAG_X ]);
        tl.magn[1]  = atof(dummy[ TLM_MAG_Y ]);
        tl.magn[2]  = atof(dummy[ TLM_MAG_Z ]);

        tl.gyro[0]  = atof(dummy[ TLM_GYR_X ]);
        tl.gyro[1]  = atof(dummy[ TLM_GYR_Y ]);
        tl.gyro[2]  = atof(dummy[ TLM_GYR_Z ]);

        telemetries.push_back(tl);

        //dumpTelemetry(&tl);

    }

    fclose(fpr);


    cout << telemetries.size() << " telemetries" << endl;

    return telemetries;

}


void dumpTelemetry( telemetry *tl ){
    printf("unixTime = %i\n",tl->unixTime);

}