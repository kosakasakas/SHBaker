//
//  KsSphericalHarmonicsTextureFactory.hpp
//  SHBaker
//
//  Created by 小坂 昂大 on 2016/07/02.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KsSphericalHarmonicsTextureFactory_hpp
#define KsSphericalHarmonicsTextureFactory_hpp

#include <vector>
#include "KsSphericalHarmonicsTextureBuffer.hpp"

namespace Kosakasakas {
    
    //! テクスチャバッファポインタの定義
    typedef std::shared_ptr<KsSphericalHarmonicsTextureBuffer> SHTextureBufferPtr;
    
    /**
     @brief 球面調和関数データテクスチャのファクトリ
     
     球面調和関数データの入ったテクスチャを指定枚数分生成します.
     */
    class KsSphericalHarmonicsTextureFactory
    {
    public:
        //! コンストラクタ
        KsSphericalHarmonicsTextureFactory();
        //! デストラクタ
        virtual ~KsSphericalHarmonicsTextureFactory();
        //! 初期化
        bool    Initialize(int texNum, int width, int height);
        //! 終了処理
        void    Finalize();
        
        //! 球面調和関数テクスチャバッファの取得
        const SHTextureBufferPtr  GetSHTextureBuffer(int texID) const;
        
    protected:
        //! テクスチャを作成
        bool    CreateTexture(int width, int height);
        //! 球面調和関数のパラメータ取得
        void    GetSHParam(int& l, int& m, int shID);
        
    private:
        //! テクスチャバッファベクトル
        std::vector<SHTextureBufferPtr> m_SHTextureBufferPtrVec;
    };
}

#endif /* KsSphericalHarmonicsTextureFactory_hpp */
