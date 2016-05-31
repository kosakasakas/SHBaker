#include "ofApp.h"

using namespace Kosakasakas;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    // 球体のセットアップ
    m_Sphere.setRadius(ofGetHeight() * 0.3f);
    m_Sphere.setResolution(2);
    
    // シェーダのロード
    m_Shader.load("test.vert", "test.frag");
    
    // SHMakerのセットアップ
    KSSphericalHarmonicsTextureParam param;
    param.m_Width       = 512; // 出力テクスチャのheight
    param.m_Height      = 512; // 出力テクスチャのwidth
    param.m_MaxBandID   = 2; // 何バンドまで描画するか
    m_SHTexMaker.Initialize(param);
    
    // SHTextureを描画
    if (!m_SHTexMaker.DrawTex())
    {
        ofLog(ofLogLevel::OF_LOG_ERROR, "球面調和テクスチャバッファの描画に失敗しました");
    }
    
    // 球面調和関数のテクスチャバッファデータを取得
    auto texVec = m_SHTexMaker.GetTextureBufferPtrVec();
    
    // サンプル曰く、
    // > note that we disable arb tex, meaning we will use normalized texture coordinates,
    // > where a texture's x and y coordinate are each expressed as a normalized float.
    // > this makes things slightly easier in the shader.
    // と言うことらしいので、ofDisableArbTexはDisableしとく
    ofDisableArbTex();
    m_SHTex.loadData(texVec[0]->GetData(), m_SHTexMaker.GetWidth(), m_SHTexMaker.GetHeight(), GL_RGBA);
    m_Tes.load("projection.jpg");
    ofEnableArbTex();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    ofEnableDepthTest();
    
    // 球のセットアップ
    m_Sphere.setPosition(ofGetWidth() * 0.5f, ofGetHeight() * 0.5f, 0.0f);
    m_Sphere.rotate(spinX, 1.0f, 0.0f, 0.0f);
    m_Sphere.rotate(spinY, 0.0f, 1.0f, 0.0f);
    
    // テクスチャのセットアップ
    //m_Tes.getTexture().draw(ofGetWidth() * 0.5f, 0);
    m_SHTex.draw(ofGetWidth() * 0.5f, 0);
    
    // 球体の描画
    m_Shader.begin();
    m_Shader.setUniformTexture("u_SHTex", m_SHTex, 0);
    m_Shader.setUniform1i("u_Channel", 1);
    m_Sphere.draw();
    m_Shader.end();
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
