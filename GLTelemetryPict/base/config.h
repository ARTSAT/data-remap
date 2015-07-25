//
//  config.h
//  GL
//
//  Created by h on 6/24/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#ifndef GL_config_h
#define GL_config_h

#import "Renderer.h"


#define DPI             (150)
#define PX_PER_HOUR     (30)
#define PX_PER_DAY     (PX_PER_HOUR*24)

#define DAY_IN_A_PIC    (4)

#define PIC_WIDTH_PX    (24*PX_PER_HOUR*DAY_IN_A_PIC)
#define PIC_HEIGH_PX    (1024*5)


const float screen_w = PIC_WIDTH_PX;
const float screen_h = PIC_HEIGH_PX;




#define RENDERER_CLASS TestRenderer



#endif
