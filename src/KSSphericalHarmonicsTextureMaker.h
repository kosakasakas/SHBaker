//
//  KSSphericalHarmonicsTextureMaker.h
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//
//

#ifndef KSSphericalHarmonicsTextureMaker_h
#define KSSphericalHarmonicsTextureMaker_h

#include <vector>
#include "memory.h"
#include "KSSHTextureBuffer.h"

namespace Kosakasakas {
    
    class KSSphericalHarmonicsTextureParam
    {
    public:
        KSSphericalHarmonicsTextureParam(){};
        virtual ~KSSphericalHarmonicsTextureParam(){};
        
        int m_Width;
        int m_Height;
        int m_MaxBandID;
    };
    
    /**
     @brief
     */
    class KSSphericalHarmonicsTextureMaker
    {
    public:
        KSSphericalHarmonicsTextureMaker();
        virtual ~KSSphericalHarmonicsTextureMaker();
        bool    Initialize(KSSphericalHarmonicsTextureParam& param);
        void    Finalize();
        
        typedef std::shared_ptr<KSSHTextureBuffer>      TextureBufferPtr;
        typedef std::vector<TextureBufferPtr>           TextureBfferPtrVec;
        
        inline const TextureBfferPtrVec&    GetTextureBufferPtrVec() const
        {
            return m_TextureBufferPtrVec;
        }
        
        inline const int    GetWidth() const
        {
            return m_Param.m_Width;
        }
        
        inline const int    GetHeight() const
        {
            return m_Param.m_Height;
        }
        
        static int CalcBasisNum(int bandID);
    private:
        
    private:
        TextureBfferPtrVec                  m_TextureBufferPtrVec;
        KSSphericalHarmonicsTextureParam    m_Param;
        
        int m_TexNum;
    };
    
} //namesp

#endif /* KSSphericalHarmonicsTextureMaker_h */
