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

#ifndef __SHBaker__KSSphericalHarmonics__
#define __SHBaker__KSSphericalHarmonics__

namespace Kosakasakas {
    
    /**
     @brief 球面調和関数の演算を行うクラスです。
     */
    class KSSphericalHarmonics
    {
    public:
        static float Calc(int l, int m, float theta, float phi);
    private:
        static float CalcScalingFactor(int l, int m);
        static float CalcLegendrePolynomials( int l, int m, float x );
    };
    
} //namespace Kosakasakas {


#endif /* defined(__SHBaker__KSSphericalHarmonics__) */
