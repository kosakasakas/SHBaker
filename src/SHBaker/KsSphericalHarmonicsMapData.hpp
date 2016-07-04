//
//  KsSphericalHarmonicsMapData.hpp
//  SHBaker
//
//  Created by 小坂 昂大 on 2016/07/02.
//  Copyright (c) 2016年 Takahiro Kosaka. All rights reserved.
//
//  This Source Code Form is subject to the terms of the Mozilla
//  Public License v. 2.0. If a copy of the MPL was not distributed
//  with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KsSphericalHarmonicsMapData_hpp
#define KsSphericalHarmonicsMapData_hpp

namespace Kosakasakas {
    
    /**
     @brief 球面調和関数データバッファクラス
     
     球面調和関数のルックアップデータの入ったバッファを生成するクラスです.
     (l,m)のパラメータセット一つ分の球面調和関数ルックアップテーブルが格納されています.
     signed floatフォーマットで格納されています.
     */
    class KsSphericalHarmonicsMapData
    {
    public:
        //! コンストラクタ
        KsSphericalHarmonicsMapData();
        //! デストラクタ
        virtual ~KsSphericalHarmonicsMapData();
    
        //! 初期化
        bool    Initialize(int l, int m, int thetaResSize, int phiResSize);
        //! 終了処理
        void    Finalize();
        //! データの参照
        inline const float* GetDataConst() const
        {
            return m_pDataBuffer;
        }
        //! データを持っているかどうか
        inline bool HasData() const
        {
            return (m_pDataBuffer);
        }
        //! シータ方向の解像度
        inline int  GetThetaSize() const
        {
            return m_ThetaSize;
        }
        //! ファイ方向の解像度
        inline int  GetPhiSize() const
        {
            return m_PhiSize;
        }
        
    private:
        //! データの格納
        bool    DrawData();
        
    private:
        //! 第何球面調和関数ID
        int m_SHID;
        //! パラメータlの値
        int m_L;
        //! パラメータmの値
        int m_M;
        //! Θ方向の解像度
        int m_ThetaSize;
        //! φ方向の解像度
        int m_PhiSize;
        //! バッファ
        float*  m_pDataBuffer;
    };
}

#endif /* KsSphericalHarmonicsMapData_hpp */
