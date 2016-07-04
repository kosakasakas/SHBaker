//
//  KSTextureBufferRGBA8.h
//  SHBaker
//
//  Created by Takahiro Kosaka on 2016/05/26.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KSTextureBufferRGBA8_h
#define KSTextureBufferRGBA8_h

namespace Kosakasakas {
    
    /**
     @brief RGBA8形式のテクスチャデータを一枚分保持するクラス
     */
    class KSTextureBufferRGBA8
    {
    public:
        //! コンストラクタ
        KSTextureBufferRGBA8();
        //! デストラクタ
        virtual ~KSTextureBufferRGBA8();
        //! 初期化
        virtual bool    Initialize(int width, int height);
        //! 終了処理
        virtual void    Finalize();
        //! バッファへのポインタを取得
        inline unsigned char*  GetDataRef()
        {
            return m_pTextureBuffer;
        }
        //! バッファへのポインタを取得（コンスト）
        inline const unsigned char* GetData() const
        {
            return m_pTextureBuffer;
        }
        
    protected:
        //! データの格納のための抽象関数
        virtual bool    DrawData()  = 0;
        
    protected:
        //! テクスチャバッファの定義
        typedef unsigned char*      TextureBufferPtr;
        
        //! テクスチャバッファ
        TextureBufferPtr   m_pTextureBuffer;
        //! 横幅
        int m_Width;
        //! 高さ
        int m_Height;
    };
    
} //namespace Kosakasakas {


#endif /* KSTextureBufferRGBA8_h */
