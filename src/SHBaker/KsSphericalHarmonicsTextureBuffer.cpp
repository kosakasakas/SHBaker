//
//  KsSphericalHarmonicsTextureBuffer.cpp
//  SHBaker
//
//  Created by 小坂 昂大 on 2016/07/02.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "KsSphericalHarmonicsTextureBuffer.hpp"

using namespace Kosakasakas;

//! コンストラクタ
KsSphericalHarmonicsTextureBuffer::KsSphericalHarmonicsTextureBuffer()
{}

//! デストラクタ
KsSphericalHarmonicsTextureBuffer::~KsSphericalHarmonicsTextureBuffer()
{
    Finalize();
}

/**
 @brief 初期化
 
 SHテクスチャデータの初期化を行います.
 1チャンネルにつき1つのルックアップデータを格納し、RGBの3チャンネルに格納します.
 αチャンネルにはRGBの符号情報がbitで入ります.
 フォーマットはRGBA8になっている点、留意してください.
 @param width   横幅
 @param height  縦幅
 @param pDataR  Rチャンネルに格納するSHルックアップデータ
 @param pDataG  Gチャンネルに格納するSHルックアップデータ
 @param pDataB  Bチャンネルに格納するSHルックアップデータ
 @return 成功可否
 */
bool    KsSphericalHarmonicsTextureBuffer::Initialize(int width,
                                                   int height,
                                                   const std::shared_ptr<KsSphericalHarmonicsMapData>& pDataR,
                                                   const std::shared_ptr<KsSphericalHarmonicsMapData>& pDataG,
                                                   const std::shared_ptr<KsSphericalHarmonicsMapData>& pDataB)
{
    // データがnullなら終了
    if (!pDataR || !pDataG || !pDataB)
    {
        return false;
    }
        
    // データが初期化されてないなら終了
    if (!pDataR->HasData()
        || !pDataB->HasData()
        || !pDataG->HasData())
    {
        return false;
    }
    
    //! 解像度が違ったら終了
    if (!(pDataR->GetThetaSize()    == height)
        || !(pDataR->GetPhiSize()   == width)
        || !(pDataG->GetThetaSize() == height)
        || !(pDataG->GetPhiSize()   == width)
        || !(pDataB->GetThetaSize() == height)
        || !(pDataB->GetPhiSize()   == width))
    {
        return false;
    }
    
    m_pDataR    = pDataR;
    m_pDataG    = pDataG;
    m_pDataB    = pDataB;
    
    return KSTextureBufferRGBA8::Initialize(width, height);
}

//! 終了処理
void    KsSphericalHarmonicsTextureBuffer::Finalize()
{
    m_pDataR    = nullptr;
    m_pDataG    = nullptr;
    m_pDataB    = nullptr;
}

//! データの格納
bool    KsSphericalHarmonicsTextureBuffer::DrawData()
{
    const float* SHDataR  = m_pDataR->GetDataConst();
    const float* SHDataG  = m_pDataG->GetDataConst();
    const float* SHDataB  = m_pDataB->GetDataConst();
    
    for (int h = 0; h < m_Height; ++h)
    {
        for (int w = 0; w < m_Width; ++w)
        {
            int index   = m_Width * h + w;
            
            float shR   = SHDataR[index];
            float shG   = SHDataG[index];
            float shB   = SHDataB[index];
            
            // RGBの精度を落とさないため、alphaには符号情報を入れておく
            // 正なら0、負なら1
            unsigned char A = 0;
            if (shR < 0)
            {
                A   += 1;
                shR = -shR;
            }
            if (shG < 0)
            {
                A   += 2;
                shG = -shG;
            }
            if (shB < 0)
            {
                A   += 4;
                shB = -shB;
            }
            
            // R
            m_pTextureBuffer[4 * index + 0] = (unsigned char) (255.0f * shR);
            // G
            m_pTextureBuffer[4 * index + 1] = (unsigned char) (255.0f * shG);
            // B
            m_pTextureBuffer[4 * index + 2] = (unsigned char) (255.0f * shB);
            // A
            m_pTextureBuffer[4 * index + 3] = A;
        }
    }
    return true;
}

