//
//  config.h
//  GL
//
//  Created by h on 6/24/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#ifndef GL_config_h
#define GL_config_h




#define PX_PER_HOUR     (30)
#define PX_PER_DAY      (PX_PER_HOUR*24)

#define DAY_IN_A_PIC    (4)

#define PIC_WIDTH_PX    (24*PX_PER_HOUR*DAY_IN_A_PIC)
#define PIC_HEIGH_PX    (1024*5 + 120)

const float ruler_h = (36+48);


const float screen_w = PIC_WIDTH_PX;
const float screen_h = PIC_HEIGH_PX - ruler_h*3;



#include "telemetryReader.h"


const int startUnixTime     = unixTimeFromDate(2014, 2, 28, 0, 0, 0);
const int endUnixTime       = unixTimeFromDate(2014, 9, 3, 0, 0, 0);

#endif
