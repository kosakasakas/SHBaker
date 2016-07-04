//
//  KsSphericalHarmonicsTextureBuffer.hpp
//
//  球面調和関数データの入ったテクスチャを1枚生成するクラスです.
//
//  Created by 小坂 昂大 on 2016/07/02.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KsSphericalHarmonicsTextureBuffer_hpp
#define KsSphericalHarmonicsTextureBuffer_hpp

#include "KSTextureBufferRGBA8.h"
#include "KsSphericalHarmonicsMapData.hpp"
#include <vector>
#include <memory.h>

namespace Kosakasakas {
    
    /**
     @brief 球面調和関数データテクスチャ
     
     球面調和関数データの入ったテクスチャを1枚生成するクラスです.
     一つのチャンネルにつき、(l,m)のパラメータセット一つ分の球面調和関数ルックアップテーブルが格納されています.
     R,G,Bチャンネルにはデータが格納されており、Aチャンネルにはそれらの符号情報がbitデータとして格納されています.
     符号の複合方法はシェーダ(debug_shtex.frag)を参考にしてください.
     */
    class KsSphericalHarmonicsTextureBuffer
    : public KSTextureBufferRGBA8
    {
    public:
        //! コンストラクタ
        KsSphericalHarmonicsTextureBuffer();
        //! デストラクタ
        virtual ~KsSphericalHarmonicsTextureBuffer();
        //! 初期化
        bool    Initialize(int width,
                           int height,
                           const std::shared_ptr<KsSphericalHarmonicsMapData>& pDataR,
                           const std::shared_ptr<KsSphericalHarmonicsMapData>& pDataG,
                           const std::shared_ptr<KsSphericalHarmonicsMapData>& pDataB);
        //! 終了処理
        void    Finalize();
        
    protected:
        //! データの格納
        bool    DrawData();
        
    private:
        //! 1チャンネル分のデータ格納バッファ R
        std::shared_ptr<KsSphericalHarmonicsMapData>   m_pDataR;
        //! 1チャンネル分のデータ格納バッファ G
        std::shared_ptr<KsSphericalHarmonicsMapData>   m_pDataG;
        //! 1チャンネル分のデータ格納バッファ B
        std::shared_ptr<KsSphericalHarmonicsMapData>   m_pDataB;
    };
}

#endif /* KsSphericalHarmonicsTextureBuffer_hpp */
