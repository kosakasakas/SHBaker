//
//  KsSphericalHarmonicsTextureFactory.cpp
//  SHBaker
//
//  Created by 小坂 昂大 on 2016/07/02.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "KsSphericalHarmonicsTextureFactory.hpp"

using namespace Kosakasakas;

//! コンストラクタ
KsSphericalHarmonicsTextureFactory::KsSphericalHarmonicsTextureFactory()
{}

//! デストラクタ
KsSphericalHarmonicsTextureFactory::~KsSphericalHarmonicsTextureFactory()
{
    Finalize();
}

/**
 @brief 初期化
 
 ファクトリの初期化を行います.
 指定されたテクスチャ枚数分だけテクスチャバッファをl,m=0から順に作成します.
 一つのテクスチャには3パラメータ分のSHルックアップデータが格納されているため、
 texNum * 3 だけのSH関数を参照することができます.
 @param texNum  テクスチャ枚数
 @param width   横幅
 @param height  縦幅
 @return 成功可否
 */
bool    KsSphericalHarmonicsTextureFactory::Initialize(int texNum, int width, int height)
{
    // 現状は、1枚以上8枚以下じゃないと書けません
    if (texNum < 1 && 8 < texNum)
    {
        return false;
    }
    
    // テクスチャ枚数分確保
    m_SHTextureBufferPtrVec.resize(texNum);
    
    // テクスチャ作成
    return CreateTexture(width, height);
}

//! 終了処理
void    KsSphericalHarmonicsTextureFactory::Finalize()
{
    m_SHTextureBufferPtrVec.clear();
}

//! テクスチャの作成
bool    KsSphericalHarmonicsTextureFactory::CreateTexture(int width, int height)
{
    typedef std::shared_ptr<KsSphericalHarmonicsMapData> SHDataPtr;
    
    // テクスチャインデックス
    int shID = 0;
    
    // テクスチャ作成
    for (auto& pShTexBufferPtr : m_SHTextureBufferPtrVec)
    {
        // パラメータの定義
        int l, m;
        
        // Rチャンネルに入れるデータの計算
        SHDataPtr pDataR;
        {
            // 球面調和関数のパラメータ取得
            GetSHParam(l, m, shID);
            
            // l,mでデータを計算
            pDataR = std::make_shared<KsSphericalHarmonicsMapData>();
            if (!pDataR->Initialize(l, m, height, width))
            {
                goto ERROR_LABEL;
            }
            
            // IDをインクリメント
            ++shID;
        }
        
        // Gチャンネルに入れるデータの計算
        SHDataPtr pDataG;
        {
            // 球面調和関数のパラメータ取得
            GetSHParam(l, m, shID);
            
            // l,mでデータを計算
            pDataG = std::make_shared<KsSphericalHarmonicsMapData>();
            if (!pDataG->Initialize(l, m, height, width))
            {
                goto ERROR_LABEL;
            }
            
            // IDをインクリメント
            ++shID;
        }
        
        // Bチャンネルに入れるデータの計算
        SHDataPtr pDataB;
        {
            // 球面調和関数のパラメータ取得
            GetSHParam(l, m, shID);
            
            // l,mでデータを計算
            pDataB = std::make_shared<KsSphericalHarmonicsMapData>();
            if (!pDataB->Initialize(l, m, height, width))
            {
                goto ERROR_LABEL;
            }
            
            // IDをインクリメント
            ++shID;
        }
        
        // テクスチャデータに変換してキャッシュ
        pShTexBufferPtr = std::make_shared<KsSphericalHarmonicsTextureBuffer>();
        if (!pShTexBufferPtr->Initialize(width,
                                        height,
                                        pDataR,
                                        pDataG,
                                        pDataB))
        {
            goto ERROR_LABEL;
        }
    }
    
    return true;
    
ERROR_LABEL:
    return false;
}

//! 第何関数か取得
const SHTextureBufferPtr    KsSphericalHarmonicsTextureFactory::GetSHTextureBuffer(int texID) const
{
    int size = m_SHTextureBufferPtrVec.size();
    if (texID < 0 && size < texID)
    {
        return nullptr;
    }
    return m_SHTextureBufferPtrVec[texID];
}

/**
 @brief パラメータの取得
 
 l=0,m=0を0番目、l=1,m=-1を1番目としてn番目のshIDのl,mのパラメータを返す関数です.
 上限は24番目までです.
 @param l   lの値が入るint参照値
 @param m   mの値が入るint参照値
 @param shID    上から何番目のパラメータか
 @return 成功可否
 */
void    KsSphericalHarmonicsTextureFactory::GetSHParam(int &l, int &m, int shID)
{
    switch (shID) {
        case 0:
            l   = 0;
            m   = 0;
            break;
        case 1:
            l   = 1;
            m   = -1;
            break;
        case 2:
            l   = 1;
            m   = 0;
            break;
            
        case 3:
            l   = 1;
            m   = 1;
            break;
        case 4:
            l   = 2;
            m   = -2;
            break;
        case 5:
            l   = 2;
            m   = -1;
            break;
            
        case 6:
            l   = 2;
            m   = 0;
            break;
        case 7:
            l   = 2;
            m   = 1;
            break;
        case 8:
            l   = 2;
            m   = 2;
            break;
            
        case 9:
            l   = 3;
            m   = -3;
            break;
        case 10:
            l   = 3;
            m   = -2;
            break;
        case 11:
            l   = 3;
            m   = -1;
            break;
            
        case 12:
            l   = 3;
            m   = 0;
            break;
        case 13:
            l   = 3;
            m   = 1;
            break;
        case 14:
            l   = 3;
            m   = 2;
            break;
            
        case 15:
            l   = 3;
            m   = 3;
            break;
        case 16:
            l   = 4;
            m   = -4;
            break;
        case 17:
            l   = 4;
            m   = -3;
            break;
            
        case 18:
            l   = 4;
            m   = -2;
            break;
        case 19:
            l   = 4;
            m   = -1;
            break;
        case 20:
            l   = 4;
            m   = 0;
            break;
            
        case 21:
            l   = 4;
            m   = 1;
            break;
        case 22:
            l   = 4;
            m   = 2;
            break;
        case 23:
            l   = 4;
            m   = 3;
            break;
            
        case 24:
            l   = 4;
            m   = 4;
            break;
            
        default:
            l   = 0;
            m   = 0;
            break;
    }
}