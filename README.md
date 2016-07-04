# SHBaker
球面調和関数のlookupテクスチャの生成ツールです.

!(screenshot)[image/screenshot.png]

一枚につき三つ分の球面調和関数のルックアップデータを格納したテクスチャを生成します.(RGBに符号なしデータ、Aに各チャンネルの符号bit)
デフォルトでは4枚分のテクスチャが生成されます.

bin/data/image/spherical_harmonics_*.pngが該当のデータです.

※アプリではデバッグ表示のため、正の値が緑、負の値が赤で表示されています.


## テクスチャのデコード方法
詳しくはglslを参照してください.
以下のようにデコードすることができます.

    vec3    GetSignConvertVec(float val)
    {
        int bit = int(255.0 * val);
        vec3 res;
        res.x   = ((bit & 1) == 1) ? -1.0 : 1.0;
        res.y   = ((bit & 2) == 2) ? -1.0 : 1.0;
        res.z   = ((bit & 4) == 4) ? -1.0 : 1.0;
        return res;
    }

    void main()
    {
        vec4 col    = texture(u_SHTex, o_texcoord);
        vec3 sign   = GetSignConvertVec(col.a);
        col.rgb     = sign * col.rgb;
        float sh    = (u_Channel == 0) ? col.r
                    : (u_Channel == 1) ? col.g
                    : (u_Channel == 2) ? col.b
                    : 0.0;
        vec3 val;
        val.x   = (sh < 0) ? -sh : 0.0;
        val.y   = (sh > 0) ? sh : 0.0;
        val.z   = 0.0;

        outputColor = vec4(val, 1.0);
    }




