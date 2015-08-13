//
//  flMCNoise.cpp
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 8/12/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "flMCNoise.h"

MULTI_COLOR_NAMESPACE_BEGIN

#define B 0x100
#define BM 0xff
//#define N 0x10000000
  #define N 0x100
#define NP 12
#define NM 0xfff

#define ADOT(a, b) (a[0] * b[0] + a[1] * b[1] + a[2] * b[2])
#define setup(u, b0, b1, r0, r1)\
    t = u + N;\
    b0 = ((int)t) & BM;\
    b1 = (b0+1) & BM;\
    r0 = t - (int)t;\
    r1 = r0 - 1.;

static int p[B + B + 2];
static float g[B + B + 2][3];

void initNoise()
{
    for (int i = 0; i < B; i++) {
        float v[3], s;
        do {
            for (int j = 0; j < 3; j++)
                v[j] = (float)((::random() % (B + B)) - B) / B;
            s = ADOT(v, v);
        } while (s > 1.0);
        s = sqrt(s);
        for (int j = 0; j < 3; j++)
            g[i][j] = v[j] / s;
    }
    
    for (int i = 0; i < B; i++)
        p[i] = i;
    for (int i = B; i > 0; i -= 2) {
        int j;
        int k = p[i];
        p[i] = p[j = ::random() % B];
        p[j] = k;
    }
    
    for (int i = 0; i < B + 2; i++) {
        p[B + i] = p[i];
        for (int j = 0; j < 3; j++)
            g[B + i][j] = g[i][j];
    }
}

float noise3(Vector vec)
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
    float rx0, rx1, ry0, ry1, rz0, rz1, sy, sz, *q, a, b, c, d, t, u, v;
    
	setup(vec.x, bx0, bx1, rx0, rx1);
	setup(vec.y, by0, by1, ry0, ry1);
	setup(vec.z, bz0, bz1, rz0, rz1);

//    t = ((float)vec.x) + N;
//    int i0 = ((int)t) & BM;
//    int i1 = (i0+1) & BM;
//    float f0 = t - (int)t;
//    float f1 = f0 - 1.;
//    printf("%f %i %i %f %f\n", t, i0, i1, f0, f1);
//    exit(0);
    
	const int i = p[bx0];
	const int j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

#define at(rx, ry, rz) (rx * q[0] + ry * q[1] + rz * q[2])

#define s_curve(t) (t * t * (3.f - 2.f * t))

#define lerp(t, a, b) (a + t * (b - a))

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g[b00 + bz0]; u = at(rx0, ry0, rz0);
	q = g[b10 + bz0]; v = at(rx1, ry0, rz0);
	a = lerp(t, u, v);

	q = g[b01 + bz0]; u = at(rx0, ry1, rz0);
	q = g[b11 + bz0]; v = at(rx1, ry1, rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g[b00 + bz1]; u = at(rx0, ry0, rz1);
	q = g[b10 + bz1]; v = at(rx1, ry0, rz1);
	a = lerp(t, u, v);

	q = g[b01 + bz1]; u = at(rx0, ry1, rz1);
	q = g[b11 + bz1]; v = at(rx1, ry1, rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return 1.5f * lerp(sz, c, d);
    
#undef at
#undef s_curve
#undef lerp
}

Vector vecNoise3(Vector point)
{
	Vector result;

	result.x = noise3(point);
	point.x += 10.0f;
	result.y = noise3(point);
	point.y += 10.0f;
	result.z = noise3(point);

	return result;
}

#undef B
#undef BM
#undef N
#undef NP
#undef NM

#undef ADOT
#undef setup

MULTI_COLOR_NAMESPACE_END