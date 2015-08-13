//
//  flException.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flException.h"
#include <sstream>

using namespace fl;
using namespace std;

Exception::Exception(const std::string &message) :
mMessage(message)
{
}

Exception::Exception(const char *file,
                           const char *function,
                           const int line,
                           const std::string &message) :
mFileName(file),
mFunctionName(function),
mLine(line),
mMessage(message)
{
    createDetails();
}

Exception::~Exception() throw()
{
}

#pragma mark ___________________________________________________________________

const char* Exception::what() const throw()
{
    return mDetails.c_str();
}

#pragma mark ___________________________________________________________________

std::string Exception::getDetails() const
{
    return mDetails;
}

std::string Exception::getMessage() const
{
    return mMessage;
}

std::string Exception::getFileName() const
{
    return mFileName;
}

std::string Exception::getFunctionName() const
{
    return mFunctionName;
}

const int Exception::getLineNumber() const
{
    return mLine;
}

#pragma mark ___________________________________________________________________

void Exception::createDetails()
{
    ostringstream oss;
    oss << "Exception raised" << endl <<
    "File: " << mFileName << endl <<
    "Function: " << mFunctionName << endl <<
    "Line: " << mLine << endl <<
    "Message: " << mMessage;
    mDetails = oss.str();
}