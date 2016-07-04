//
//  KsSphericalHarmonics.h
//
//  球面調和関数の演算を行うクラス
//
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//  Created by Takahiro Kosaka on 2016/05/25.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __SHBaker__KsSphericalHarmonics__
#define __SHBaker__KsSphericalHarmonics__

namespace Kosakasakas {
    
    /**
     @brief 球面調和関数の演算を行うクラスです。
     */
    class KsSphericalHarmonics
    {
    public:
        //! 球面調和関数の計算結果の取得
        static float Calc(int l, int m, float theta, float phi);
    private:
        //! スケールファクタを取得
        static float CalcScalingFactor(int l, int m);
        //! LegendrePolynomialsの取得
        static float CalcLegendrePolynomials( int l, int m, float x );
    };
    
} //namespace Kosakasakas {


#endif /* defined(__SHBaker__KsSphericalHarmonics__) */
