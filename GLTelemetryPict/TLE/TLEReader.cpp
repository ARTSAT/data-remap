//
//  TLEReader.cpp
//  Telemetry
//
//  Created by h on 7/1/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#include "TLEReader.h"


vector<TLE> openTLE(){


    const char* path = "../../data/sat39577.txt";

    vector<TLE> tles;
    //vector<cOrbit*> orbits;
    cOrbit *orbitSDP4;


    static unsigned long startOf2014InSec = unixTimeFromDate(2014, 1, 1, 0, 0, 0);


    FILE *fpr = fopen( path, "r");
    {

        int lineCnt = 0;
        char line[1024];

        while (fgets(line, 1024, fpr) != NULL) {

            if (lineCnt>=5) {

                string str1,str2,str3;
                str1 = "INVADER (CO-77)";

                string line1 = line;
                char* line2 = fgets(line, 1024, fpr);

                if (line2==NULL) {
                    break;
                }else{
                    str2 = line1;
                    str3 = line2;

                    cTle SDP4 = cTle(str1, str2, str3);
                    orbitSDP4 = new cOrbit( SDP4 );
                    //orbits.push_back(orbitSDP4);

                    float d = SDP4.GetField(cTle::FLD_EPOCHDAY);
                    float secIn2014 = d*86400.f;
                    float epochInUnixTime = secIn2014 + startOf2014InSec;

                    TLE tle;
                    tle.orbit = orbitSDP4;
                    tle.epochSecInUnixTime = epochInUnixTime;
                    tles.push_back(tle);
                    //printf("number = %i : %f\n",lineCnt-5,epochInUnixTime);
                }
            }

            lineCnt++;
        }

        printf("%i lines\n",lineCnt);
    }
    fclose(fpr);



    return tles;




}