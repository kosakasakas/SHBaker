//
//  KSSphericalHarmonicsTextureMaker.cpp
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//
//

#include "KSSphericalHarmonicsTextureMaker.h"
#include "KSSphericalHarmonics.h"
#include <math.h>

using namespace Kosakasakas;

KSSphericalHarmonicsTextureMaker::KSSphericalHarmonicsTextureMaker()
{}

KSSphericalHarmonicsTextureMaker::~KSSphericalHarmonicsTextureMaker()
{}

void    KSSphericalHarmonicsTextureMaker::Finalize()
{}

bool    KSSphericalHarmonicsTextureMaker::Initialize(KSSphericalHarmonicsTextureParam& param)
{
    int baseNum = CalcBasisNum(param.m_MaxBandID);
    
    int num = baseNum / 3;
    int mod = baseNum % 3;
    if(mod != 0) ++num;
    
    m_TexNum    = num;
    
    m_TextureBufferPtrVec.resize(m_TexNum);
    
    float wSize = 2.0f * M_PI / (float) param.m_Width;
    float hSize = 2.0f * M_PI / (float) param.m_Height;
    for (int i = 0; i < m_TexNum; ++i)
    {
        // テクスチャの初期化
        auto pTexBuffer = std::make_shared<KSSHTextureBuffer>();
        if (!pTexBuffer->Initialize(param.m_Width,
                                    param.m_Height,
                                    param.m_MaxBandID,
                                    i))
        {
            return false;
        }
        
        // カラーデータを実際に入れる
        unsigned char* pData    = pTexBuffer->GetDataRef();
        for (int w=0, nw=param.m_Width; w<nw; ++w)
        {
            for (int h=0,nh=param.m_Height; h<nh; ++h)
            {
                float theta = w * wSize;
                float phi   = h * hSize;
                
                int alpha = 0;
                for(int c = 0; c < 3; ++c)
                {
                    int l, m;
                    pTexBuffer->GetSHBaseIDsByChannel(l, m, c);
                    
                    float val   = KSSphericalHarmonics::Calc(l, m, theta, phi);
                    
                    pData[4 * (nw * h + w) + c] = val * 255;
                    
                    // RGBの精度を落とさないため、alphaに符号情報を入れておく
                    // 正なら1、負なら0で2^3=8階調のどれかがalphaに入る.
                    if (val)
                    {
                        alpha += pow(2, c);
                    }
                }
                
                pData[4 * (nw * h + w) + 3] = alpha;
            }
        }
        
        m_TextureBufferPtrVec[i]    = pTexBuffer;
    }
    
    m_Param = param;
    
    return true;
}


int     KSSphericalHarmonicsTextureMaker::CalcBasisNum(int bandID)
{
    if (bandID < 0) return 0;
    
    if (bandID == 0)
    {
        return 1;
    }
    else
    {
        return 2 * bandID + 1 + CalcBasisNum(bandID - 1);
    }
}