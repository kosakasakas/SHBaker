//
//  KSSHTextureBuffer.cpp
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//
//

#include "KSSHTextureBuffer.h"
#include "KSSphericalHarmonicsTextureMaker.h"

using namespace Kosakasakas;

KSSHTextureBuffer::KSSHTextureBuffer()
{}

KSSHTextureBuffer::~KSSHTextureBuffer()
{}

bool KSSHTextureBuffer::Initialize(int width, int height, int bandID, int texID)
{
    if (!KSTextureBufferRGBA8::Initialize(width, height))
    {
        return false;
    }
    
    if (!SetupChannelSHIDs(bandID, texID))
    {
        return false;
    }
    
    return true;
}

bool    KSSHTextureBuffer::GetSHBaseIDsByChannel(int& dstL, int& dstM, int channel)
{
    if (!m_bChannelEnables[channel]) return false;
    
    dstL    = m_ChannelSHIDs[channel].m_L;
    dstM    = m_ChannelSHIDs[channel].m_M;
}

bool KSSHTextureBuffer::SetupChannelSHIDs(int bandID, int texID)
{
    if (texID < 0) return false;
    
    int baseNum = KSSphericalHarmonicsTextureMaker::CalcBasisNum(bandID);
    
    int maxTexID    = baseNum / 3;
    int mod         = baseNum % 3;
    
    if (texID > maxTexID) return false;
    
    if (texID < maxTexID)
    {
        m_bChannelEnables[R]    = true;
        m_bChannelEnables[G]    = true;
        m_bChannelEnables[B]    = true;
    }
    else
    {
        switch (mod)
        {
            case 0:
                m_bChannelEnables[R]    = true;
                m_bChannelEnables[G]    = true;
                m_bChannelEnables[B]    = true;
                break;
                
            case 1:
                m_bChannelEnables[R]    = true;
                m_bChannelEnables[G]    = false;
                m_bChannelEnables[B]    = false;
                break;
                
            case 2:
                m_bChannelEnables[R]    = true;
                m_bChannelEnables[G]    = true;
                m_bChannelEnables[B]    = false;
                break;
                
            default:
                m_bChannelEnables[R]    = false;
                m_bChannelEnables[G]    = false;
                m_bChannelEnables[B]    = false;
                break;
        }
    }
    
    int startBaseID = 3 * texID;
    for (int i = 0; i < NUM; ++i)
    {
        if (m_bChannelEnables[i])
        {
            int baseID  = startBaseID + i;
            bool res    = SetSHBaseIDs(m_ChannelSHIDs[i], baseID);
            if (!res)
            {
                m_bChannelEnables[i] = false;
            }
        }
    }
    
    return true;
}

bool    KSSHTextureBuffer::SetSHBaseIDs(SHBaseIDs& dst, int baseID)
{
    // 面倒なので手動
    if (baseID  == 0)
    {
        dst.m_L = 0;
        dst.m_M = 0;
        return true;
    }
    else if (baseID < 4)
    {
        dst.m_L = 1;
        dst.m_M = baseID - 2;
        return true;
    }
    else if (baseID < 9)
    {
        dst.m_L = 2;
        dst.m_M = baseID - 6;
        return true;
    }
    else if (baseID < 16)
    {
        dst.m_L = 3;
        dst.m_M = baseID - 12;
        return true;
    }
    else if (baseID < 25)
    {
        dst.m_L = 3;
        dst.m_M = baseID - 12;
        return true;
    }
    else if (baseID < 36)
    {
        dst.m_L = 4;
        dst.m_M = baseID - 20;
        return true;
    }
    
    // 面倒なので終了
    return false;
}
