#include "ofApp.h"
#include "KSSphericalHarmonics.h"

using namespace Kosakasakas;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    // 球体のセットアップ
    m_Sphere.setRadius(ofGetHeight() * 0.3f);
    m_Sphere.setResolution(2);
    
    // シェーダのロード
    m_Shader.load("test.vert", "test.frag");
    
    // テクスチャのセット
    m_Width   = 512;
    m_Height  = 512;
    int l   = 1;
    int m   = -1;
    float wSize = 2.0f * PI / (float)m_Width;
    float hSize = 2.0f * PI / (float)m_Height;
    m_pSHTexBuffer  = new unsigned char[4 * m_Width * m_Height];
    for (int w = 0; w < m_Width; ++w)
    {
        for (int h = 0; h < m_Height; ++h)
        {
            float theta = w * wSize;
            float phi   = h * hSize;
            float val   = KSSphericalHarmonics::Calc(l, m, theta, phi);
            // R
            m_pSHTexBuffer[4 * (m_Width * h + w) + 0] = MAX(-val * 255.0f, 0.0f);
            // G
            m_pSHTexBuffer[4 * (m_Width * h + w) + 1] = MAX(val * 255.0f, 0.0f);
            // B
            m_pSHTexBuffer[4 * (m_Width * h + w) + 2] = 0;
            // A
            m_pSHTexBuffer[4 * (m_Width * h + w) + 3] = 255;
        }
    }
    
    m_SHTex.loadData(m_pSHTexBuffer, m_Width, m_Height, GL_RGBA);
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
    m_Sphere.setPosition(ofGetWidth() * 0.25f, ofGetHeight() * 0.5f, 0.0f);
    m_Sphere.rotate(spinX, 1.0f, 0.0f, 0.0f);
    m_Sphere.rotate(spinY, 0.0f, 1.0f, 0.0f);
    
    // テクスチャのセットアップ
    m_SHTex.draw(ofGetWidth() * 0.5f, 0);
    
    // 球体の描画
    m_Shader.begin();
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
