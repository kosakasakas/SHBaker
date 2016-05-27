//
//  KSTextureBufferRGBA8.cpp
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//
//

#include "KSTextureBufferRGBA8.h"

using namespace Kosakasakas;

KSTextureBufferRGBA8::KSTextureBufferRGBA8()
: m_pTextureBuffer(nullptr)
, m_Width(0)
, m_Height(0)
{}

KSTextureBufferRGBA8::~KSTextureBufferRGBA8()
{
    delete m_pTextureBuffer;
    m_pTextureBuffer    = nullptr;
}

bool KSTextureBufferRGBA8::Initialize(int width, int height)
{
    // すでに生成済み
    if (m_pTextureBuffer) return false;
    
    m_pTextureBuffer    = new unsigned char [width * height * 4]();
    
    // 確保に失敗した場合
    if(!m_pTextureBuffer) return false;
    
    m_Width     = width;
    m_Height    = height;
    
    return true;
}

void    KSTextureBufferRGBA8::Finalize()
{
    m_Width     = 0;
    m_Height    = 0;
    delete m_pTextureBuffer;
    m_pTextureBuffer    = nullptr;
}



