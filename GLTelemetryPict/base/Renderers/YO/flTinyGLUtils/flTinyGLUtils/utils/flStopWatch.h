//
//  flStopWatch.h
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 6/17/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#ifndef __flTinyGLUtils__flStopWatch__
#define __flTinyGLUtils__flStopWatch__

#include "flCommon.h"
#include <chrono>
#include <string>
#include <iostream>

FL_NAMESPACE_BEGIN

class StopWatch {
public:
    StopWatch() :
    mStartTime(std::chrono::system_clock::now())
    {
    }
    
    StopWatch(const std::string& info) :
    mInfo(info),
    mStartTime(std::chrono::system_clock::now())
    {
    }
    
    ~StopWatch()
    {
        auto endTime = std::chrono::system_clock::now();
        auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - mStartTime);
        if (mInfo.empty()) {
            std::cout << "Takes " << msec.count() << " milliseconds." << std::endl;
        }
        else {
            std::cout << mInfo << " takes " << msec.count() << " milliseconds." << std::endl;
        }
    }
    
private:
    std::chrono::time_point<std::chrono::system_clock> mStartTime;
    std::string mInfo;
};

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flStopWatch__) */
