//
//  flRandom.h
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 6/14/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#ifndef __flTinyGLUtils__flRandom__
#define __flTinyGLUtils__flRandom__

#include "flCommon.h"
#include <random>

FL_NAMESPACE_BEGIN

template <typename T, class Destribution>
class Random {
public:
    Random();
    virtual ~Random() {}
    
    void seed();
    
    template<typename S>
    void seed(S _seed);
    
    T operator () (T max); // 0 - max
    T operator () (T min, T max); // min - max
    
    T r(T max);  // 0 - max
    T r(T min, T max); // min - max
    T rf(); // -1 - 1
    T ruf(); // 0 - 1
    
private:
    std::mt19937 mMt19937;
    std::function<T()> mUnitDestribution;
    std::function<T()> mUnsignedUnitDestribution;
};

template <typename T, class Destribution>
Random<T, Destribution>::Random()
{
    mUnitDestribution = bind(Destribution(static_cast<T>(-1), static_cast<T>(1)), ref(mMt19937));
    mUnsignedUnitDestribution = bind(Destribution(static_cast<T>(0), static_cast<T>(1)), ref(mMt19937));
}

template <typename T, class Destribution>
void Random<T,  Destribution>::seed()
{
    std::random_device rd;
    seed(rd());
}

template <typename T, class Destribution>
template<typename S>
void Random<T, Destribution>::seed(S _seed)
{
    mMt19937.seed(_seed);
}

template <typename T, class Destribution>
T Random<T, Destribution>::operator () (T min, T max)
{
    Destribution destribution(min, max);
    return destribution(mMt19937);
}

template <typename T, class Destribution>
T Random<T, Destribution>::operator () (T max)
{
    return *this(static_cast<T>(0), max);
}

template <typename T, class Destribution>
T Random<T, Destribution>::r(T max)
{
    return *this(max);
}

template <typename T, class Destribution>
T Random<T, Destribution>::r(T min, T max)
{
    return *this(min, max);
}

template <typename T, class Destribution>
T Random<T, Destribution>::rf()
{
    return mUnitDestribution();
}

template <typename T, class Destribution>
T Random<T, Destribution>::ruf()
{
    mUnsignedUnitDestribution();
}

typedef Random<char, std::uniform_int_distribution<char>> RandChar;
typedef Random<short, std::uniform_int_distribution<short>> RandShort;
typedef Random<int, std::uniform_int_distribution<int>> RandInt;
typedef Random<long, std::uniform_int_distribution<long>> RandLong;
typedef Random<float, std::uniform_real_distribution<float>> RandFloat;
typedef Random<double, std::uniform_real_distribution<double>> RandDouble;

typedef Random<float, std::normal_distribution<float>> RandNormalFloat;
typedef Random<double, std::normal_distribution<double>> RandNormalDouble;

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flRandom__) */
