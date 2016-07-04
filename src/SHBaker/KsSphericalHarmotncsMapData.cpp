//
//  KsphericalHarmonicsMapData.cpp
//  SHBaker
//
//  Created by 小坂 昂大 on 2016/07/02.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "KsSphericalHarmonicsMapData.hpp"
#include "KsSphericalHarmonics.h"
#include <math.h>

using namespace Kosakasakas;

//! コンストラクタ
KsSphericalHarmonicsMapData::KsSphericalHarmonicsMapData()
: m_pDataBuffer(nullptr)
{}

//! デストラクタ
KsSphericalHarmonicsMapData::~KsSphericalHarmonicsMapData()
{
    Finalize();
}

/**
 @brief 初期化
 
 データバッファの初期化と書き込みを行います.
 解像度=サンプル数になるため、大きい方が滑らかな補完のバッファが作成できます.
 @param l   lの値
 @param m   mの値
 @param thetaResSize    theta方向の解像度
 @param phiResSize      phi方向の解像度
 @return 成功可否
 */
bool    KsSphericalHarmonicsMapData::Initialize(int l, int m, int thetaResSize, int phiResSize)
{
    // すでに生成済みなら何もしない
    if (m_pDataBuffer)
    {
        return false;
    }
    
    m_L = l;
    m_M = m;
    m_ThetaSize     = thetaResSize;
    m_PhiSize       = phiResSize;
    m_pDataBuffer   = new float[m_ThetaSize * m_PhiSize];
    
    return DrawData();
}

//! 終了処理
void    KsSphericalHarmonicsMapData::Finalize()
{
    delete [] m_pDataBuffer;
    m_pDataBuffer   = nullptr;
}

//! バッファに書き込む
bool    KsSphericalHarmonicsMapData::DrawData()
{
    // バッファが未製作なら何もしない
    if (!m_pDataBuffer)
    {
        return false;
    }
    
    float thetaStep = M_PI / (float)m_ThetaSize;
    float phiStep   = M_PI / (float)m_PhiSize;
    for (int h = 0; h < m_ThetaSize; ++h)
    {
        for (int w = 0; w < m_PhiSize; ++w)
        {
            // SH計算
            float theta = thetaStep * h;
            float phi   = phiStep * w;
            float sh    = KsSphericalHarmonics::Calc(m_L, m_M, theta, phi);
            
            // バッファに格納
            m_pDataBuffer[m_PhiSize * h + w] = sh;
        }
    }
    
    return true;
}
