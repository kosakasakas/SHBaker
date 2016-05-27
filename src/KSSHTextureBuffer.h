//
//  KSSHTextureBuffer.hpp
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//
//

#ifndef KSSHTextureBuffer_h
#define KSSHTextureBuffer_h

#include "KSTextureBufferRGBA8.h"

namespace Kosakasakas {

    class KSSHTextureBuffer : public KSTextureBufferRGBA8
    {
    public:
        KSSHTextureBuffer();
        ~KSSHTextureBuffer();
        bool    Initialize(int width, int height, int bandID, int texID);
        
        bool    GetSHBaseIDsByChannel(int& dstL, int& dstM, int channel);
        
    private:
        bool    SetupChannelSHIDs(int bandID, int texID);
        
        struct SHBaseIDs
        {
        public:
            int m_L;
            int m_M;
        };
        bool    SetSHBaseIDs(SHBaseIDs& dst, int baseID);
        
        enum ChannelID
        {
            R,
            G,
            B,
            
            NUM
        };
        
        SHBaseIDs   m_ChannelSHIDs[ChannelID::NUM];
        bool        m_bChannelEnables[ChannelID::NUM];
    };
    
} //namespace Kosakasakas {

#endif /* KSSHTextureBuffer_h */
