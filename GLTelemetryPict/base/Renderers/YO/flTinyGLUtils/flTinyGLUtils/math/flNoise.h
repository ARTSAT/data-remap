/* port from oF */

#pragma once


/*
 * Mesa 3-D graphics library
 * Version:  6.5
 *
 * Copyright (C) 2006  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * SimplexNoise1234
 * Copyright (c) 2003-2005, Stefan Gustavson
 *
 * Contact: stegu@itn.liu.se
 */

/** \file
    \brief C implementation of Perlin Simplex Noise over 1,2,3, and 4 dimensions.
    \author Stefan Gustavson (stegu@itn.liu.se)
*/

/*
 * This implementation is "Simplex Noise" as presented by
 * Ken Perlin at a relatively obscure and not often cited course
 * session "Real-Time Shading" at Siggraph 2001 (before real
 * time shading actually took on), under the title "hardware noise".
 * The 3D function is numerically equivalent to his Java reference
 * code available in the PDF course notes, although I re-implemented
 * it from scratch to get more readable code. The 1D, 2D and 4D cases
 * were implemented from scratch by me from Ken Perlin's text.
 *
 * This file has no dependencies on any other file, not even its own
 * header file. The header file is made for use by external code only.
 */

#include "flCommon.h"

FL_NAMESPACE_BEGIN

/*
 * ---------------------------------------------------------------------
 */

/*
 * Helper functions to compute gradients-dot-residualvectors (1D to 4D)
 * Note that these generate gradients of more than unit length. To make
 * a close match with the value range of classic Perlin noise, the final
 * noise values need to be rescaled to fit nicely within [-1,1].
 * (The simplex noise functions as such also have different scaling.)
 * Note also that these noise functions are the most practical and useful
 * signed version of Perlin noise. To return values according to the
 * RenderMan specification from the SL noise() and pnoise() functions,
 * the noise values need to be scaled and offset to [0,1], like this:
 * float SLnoise = (SimplexNoise1234::noise(x,y,z) + 1.0) * 0.5;
 */

float  grad1( int hash, float x );
float  grad2( int hash, float x, float y );
float  grad3( int hash, float x, float y , float z );
float  grad4( int hash, float x, float y, float z, float t );

/* 1D simplex noise */
float _slang_library_noise1 (float x);

/* 2D simplex noise */
float _slang_library_noise2 (float x, float y);

/* 3D simplex noise */
float _slang_library_noise3 (float x, float y, float z);

/* 4D simplex noise */
float _slang_library_noise4 (float x, float y, float z, float w);
FL_NAMESPACE_END