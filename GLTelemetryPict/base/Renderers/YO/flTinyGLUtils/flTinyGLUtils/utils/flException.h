//
//  flException.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flException__
#define __flTinyGLUtils__flException__

#include <exception>
#include <string>

#include "flCommon.h"

FL_NAMESPACE_BEGIN

class Exception : public std::exception {
public:
    Exception(const std::string &message);
    Exception(const char *file,
              const char *function,
              const int line,
              const std::string &message);
    
    virtual ~Exception() throw();
    
    std::string getDetails() const;
    std::string getMessage() const;
    std::string getFileName() const;
    std::string getFunctionName() const;
    const int getLineNumber() const;
    
    virtual const char *what() const throw();
    
private:
    void createDetails();
    
    std::string mDetails;
    std::string mMessage;
    std::string mFileName;
    std::string mFunctionName;
    int mLine;
};

FL_NAMESPACE_END

//----------------------------------------------------------------------------------------
#define flThrowException(message) \
throw fl::Exception(__FILE__, __FUNCTION__, __LINE__, message)

/// exception handler
//----------------------------------------------------------------------------------------
#define FL_BEGIN_EXCEPTION_HANDLING try {

#define FL_END_EXCEPTION_HANDLING }\
catch (fl::Exception &e) {\
std::cout << e.what() << std::endl;\
}\
catch (std::exception &e) {\
std::cout << e.what() << std::endl;\
}\
catch (...) {\
std::cout << "Unknown exception catched!" << std::endl;\
}

#define FL_ASSERT_END_EXCEPTION_HANDLING }\
catch (fl::Exception &e) {\
std::cout << e.what() << std::endl;\
assert(false);\
}\
catch (std::exception &e) {\
std::cout << e.what() << std::endl;\
assert(false);\
}\
catch (...) {\
std::cout << "Unknown exception catched!" << std::endl;\
assert(false);\
}

#endif