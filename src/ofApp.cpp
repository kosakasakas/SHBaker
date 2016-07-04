#include "ofApp.h"
#include "KsSphericalHarmonicsTextureFactory.hpp"

using namespace Kosakasakas;

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetVerticalSync(true);
    
    // 球体のセットアップ
    m_Sphere.setRadius(ofGetHeight() * 0.3f);
    m_Sphere.setResolution(3);
    
    // プレーンのセットアップ
    m_Plane.set(512, 512);
    
    // シェーダのロード
    m_Shader.load("test.vert", "test.frag");
    m_ShaderDebugSHTex.load("debug_shtex.vert", "debug_shtex.frag");
    
    //　作成するテクスチャの情報
    int texNum      = 4;
    int texWidth    = 512;
    int texHeight   = 512;
    
    // SHテクスチャファクトリのセットアップ
    KsSphericalHarmonicsTextureFactory factory;
    factory.Initialize(texNum, texWidth, texHeight);
    
    // 生成するテクスチャ数分リサイズ
    m_SHTexVec.resize(texNum);
    m_FboSHVec.resize(texNum * 3);
    
    // オフスクリーンレンダリング用のFBO確保
    m_Fbo.allocate(512, 512, GL_RGBA8);
    for (auto& fbo : m_FboSHVec)
    {
        fbo.allocate(texWidth, texHeight, GL_RGBA8);
    }
    
    // これをしないとUV座標が[0,1]にならない
    ofDisableArbTex();
    
    // 球面調和関数のテクスチャバッファデータを取得
    for (int i=0,n=m_SHTexVec.size(); i<n; ++i)
    {
        SHTextureBufferPtr pTexBuffer   = factory.GetSHTextureBuffer(i);
        m_SHTexVec[i].loadData(pTexBuffer->GetData(),
                             texWidth,
                             texHeight,
                             GL_RGBA);
        
        // 画像をセーブするならtrueを。
        if (true)
        {
            /*ofPixels pixels;
            pixels.setFromPixels(pTexBuffer->GetData(),
                                 texWidth,
                                 texHeight,
                                 ofPixelFormat::OF_PIXELS_RGBA);*/
            ofImage image;
            image.setFromPixels(pTexBuffer->GetData(),
                                texHeight,
                                texHeight,
                                ofImageType::OF_IMAGE_COLOR_ALPHA);
            char buf[256];
            sprintf(buf, "image/spherical_harmonics_%d.png", i);
            image.save(buf);
        }
    }
    
    // テクスチャバッファを解放
    factory.Finalize();
    
    ofEnableArbTex();
    
    // カメラのセットアップ
    m_Camera.setPosition(0.0f, 0.0f, 0.0f);
    m_Camera.lookAt(ofVec3f(0.0f, 0.0f, 1.0f), ofVec3f(0.0, 1.0, 0.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    // 球のセットアップ
    m_Sphere.setPosition(m_Fbo.getWidth() * 0.5f, m_Fbo.getHeight() * 0.5f, 0.0f);
    m_Sphere.rotate(spinX, 1.0f, 0.0f, 0.0f);
    m_Sphere.rotate(spinY, 0.0f, 1.0f, 0.0f);
    
    // デバッグ表示したいパラメータ
    ofTexture& debugTex = m_SHTexVec[2];
    int channel         = 2;
    
    // カメラ適用
    m_Camera.begin();
    {
        // デプス有効化
        ofEnableDepthTest();
        
        m_Fbo.begin();
        {
            // フレームバッファ初期化
            ofClear(0, 0, 255, 255);
            
            // シェーダアタッチ
            m_Shader.begin();
            {
                // シェーダセットアップ
                m_Shader.setUniformTexture("u_SHTex",   debugTex, 0);
                m_Shader.setUniform1i("u_Channel",      channel);
                
                m_Sphere.draw();
            }
            m_Shader.end();
        }
        m_Fbo.end();
        
        // デプス無効化
        ofDisableDepthTest();
        
    }
    m_Camera.end();
    
    // SHテクスチャのオフスクリーンレンダリングを行う
    for (int i=0,n=m_SHTexVec.size(); i<n; ++i)
    {
        // デバッグシェーダを当てる
        m_ShaderDebugSHTex.begin();
        {
            // テクスチャをバインド
            m_ShaderDebugSHTex.setUniformTexture("u_SHTex", m_SHTexVec[i], i);
            
            // 3チャンネル分のテクスチャを全部書く
            for (int j=0; j<3; ++j)
            {
                // FBOをバインド
                m_FboSHVec[3*i+j].begin();
                {
                    // チャンネル変更
                    m_ShaderDebugSHTex.setUniform1i("u_Channel", j);
                    
                    // 描画
                    m_Plane.draw();
                }
                m_FboSHVec[3*i+j].end();
            }
        }
        m_ShaderDebugSHTex.end();
    }
    
    // フレームバッファを描画
    m_Fbo.draw(0, 0);
    
    // デバッグテクスチャを描画
    m_FboSHVec[0].draw(512,     0,      128,    128);
    m_FboSHVec[1].draw(640,     0,      128,    128);
    m_FboSHVec[2].draw(768,     0,      128,    128);
    m_FboSHVec[3].draw(512,     128,    128,    128);
    m_FboSHVec[4].draw(640,     128,    128,    128);
    m_FboSHVec[5].draw(768,     128,    128,    128);
    m_FboSHVec[6].draw(512,     256,    128,    128);
    m_FboSHVec[7].draw(640,     256,    128,    128);
    m_FboSHVec[8].draw(768,     256,    128,    128);
    m_FboSHVec[9].draw(512,     384,    128,    128);
    m_FboSHVec[10].draw(640,    384,    128,    128);
    m_FboSHVec[11].draw(768,    384,    128,    128);
    
    ofDrawBitmapString("l=0,m=0",    512,   10);
    ofDrawBitmapString("l=1,m=-1",   640,   10);
    ofDrawBitmapString("l=1,m=0",    768,   10);
    
    ofDrawBitmapString("l=1,m=1",    512,   138);
    ofDrawBitmapString("l=2,m=-2",   640,   138);
    ofDrawBitmapString("l=2,m=-1",   768,   138);
    
    ofDrawBitmapString("l=2,m=0",    512,   266);
    ofDrawBitmapString("l=2,m=1",    640,   266);
    ofDrawBitmapString("l=2,m=2",    768,   266);
    
    ofDrawBitmapString("l=3,m=-3",   512,   394);
    ofDrawBitmapString("l=3,m=-2",   640,   394);
    ofDrawBitmapString("l=3,m=-1",   768,   394);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
