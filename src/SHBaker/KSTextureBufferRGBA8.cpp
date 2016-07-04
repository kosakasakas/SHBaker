//
//  KSTextureBufferRGBA8.cpp
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "KSTextureBufferRGBA8.h"

using namespace Kosakasakas;

//! コンストラクタ
KSTextureBufferRGBA8::KSTextureBufferRGBA8()
: m_pTextureBuffer(nullptr)
, m_Width(0)
, m_Height(0)
{}

//! デストラクタ
KSTextureBufferRGBA8::~KSTextureBufferRGBA8()
{
    delete [] m_pTextureBuffer;
    m_pTextureBuffer    = nullptr;
}

//! 初期化
bool KSTextureBufferRGBA8::Initialize(int width, int height)
{
    // すでに生成済み
    if (m_pTextureBuffer) return false;
    
    m_pTextureBuffer    = new unsigned char [width * height * 4]();
    
    // 確保に失敗した場合
    if(!m_pTextureBuffer) return false;
    
    m_Width     = width;
    m_Height    = height;
    
    return DrawData();
}

//! 終了処理
void    KSTextureBufferRGBA8::Finalize()
{
    m_Width     = 0;
    m_Height    = 0;
    delete m_pTextureBuffer;
    m_pTextureBuffer    = nullptr;
}



