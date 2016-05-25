//
//  KSSphericalHarmonics.h
//
//  球面調和関数の演算を行うクラス
//
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//  Created by Takahiro Kosaka on 2016/05/25.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "KSSphericalHarmonics.h"
#include <math.h>

namespace Kosakasakas
{
    static const float PI = 3.1415927;
}

using namespace Kosakasakas;

float KSSphericalHarmonics::Calc(int l, int m, float theta, float phi)
{
    float sf    = CalcScalingFactor(l, m);
    
    if (0 < m)
    {
        sf *= sqrtf(2.0f) * cosf(m * phi) * CalcLegendrePolynomials(l, m, cosf(theta));;
    }
    else if (m < 0)
    {
        sf *= sqrtf(2.0f) * sinf(-m * phi) * CalcLegendrePolynomials(l, -m, cosf(theta));;
    }
    else
    {
        sf *= CalcLegendrePolynomials(l, m, cosf(theta));;
    }
    
    return sf;
}

float KSSphericalHarmonics::CalcScalingFactor(int l, int m)
{
    float lpm = 1.0f;
    float lnm = 1.0f;
    if(m < 0) m = -m;
    
    for (int i = l-m; 0 < i; --i)
    {
        lnm *= i;
    }
    
    for (int i = l+m; 0 < i; --i)
    {
        lpm *= i;
    }
    
    return sqrtf(((2.0f * l + 1.0f) * lnm) / (4.0f * PI * lpm));
}

float KSSphericalHarmonics::CalcLegendrePolynomials(int l, int m, float x)
{
    float pmm = 1.0f;
    
    if (0 < m)
    {
        float somx2 = sqrtf((1.0f - x) * (1.0 + x));
        float fact = 1.0f;
        for(int i = 1; i <= m; i++)
        {
            pmm *= (-fact) * somx2;
            fact += 2.0f;
        }
    }
    
    if (l == m) return pmm;
    
    float pmmp1 = x * (2.0f * m + 1.0f) * pmm;
    
    if (l == (m + 1)) return pmmp1;
    
    float pll = 0.0f;
    for(int ll=(m+2); ll<=l; ll++)
    {
        pll = ((2.0f * ll - 1.0f) * x * pmmp1 - (ll + m - 1.0f) * pmm) / (ll - m);
        pmm = pmmp1;
        pmmp1 = pll;
    }
    
    return pll;
}
