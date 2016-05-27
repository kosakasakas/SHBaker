//
//  KSTextureBufferRGBA8.h
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//
//

#ifndef KSTextureBufferRGBA8_h
#define KSTextureBufferRGBA8_h

namespace Kosakasakas {
    
    /**
     @brief RGBA8形式のテクスチャデータを一枚分保持するクラス
     */
    class KSTextureBufferRGBA8
    {
    public:
        KSTextureBufferRGBA8();
        virtual ~KSTextureBufferRGBA8();
        bool    Initialize(int width, int height);
        void    Finalize();
        
        inline unsigned char*  GetDataRef()
        {
            return m_pTextureBuffer;
        }
        inline const unsigned char* GetData() const
        {
            return m_pTextureBuffer;
        }
    private:
        typedef unsigned char*      TextureBufferPtr;
        
        TextureBufferPtr   m_pTextureBuffer;
        int m_Width;
        int m_Height;
    };
    
} //namespace Kosakasakas {


#endif /* KSTextureBufferRGBA8_h */
