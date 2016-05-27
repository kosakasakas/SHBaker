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
    
    KSSphericalHarmonicsTextureParam param;
    param.m_Width       = 512;
    param.m_Height      = 512;
    param.m_MaxBandID   = 1;
    m_SHTexMaker.Initialize(param);
    
    auto texVec = m_SHTexMaker.GetTextureBufferPtrVec();
    
    //m_Test.load("kosakasakas.jpg");
    ofDisableArbTex();
    // note that we disable arb tex, meaning we will use normalized texture coordinates,
    // where a texture's x and y coordinate are each expressed as a normalized float.
    // this makes things slightly easier in the shader.
    // と言うことらしいので、Disableしとく
    //ofLoadImage(m_SHTex, "ps.png");
    m_SHTex.loadData(texVec[0]->GetData(), m_SHTexMaker.GetWidth(), m_SHTexMaker.GetHeight(), GL_RGBA);
    ofEnableArbTex();
    
    //m_Sphere.mapTexCoordsFromTexture(m_SHTex);
    m_FBO.allocate(400, 400, GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    ofEnableDepthTest();
    ofDisableAlphaBlending();
    
    m_FBO.begin();
    ofSetColor(0,0,255,255);
    m_FBO.end();
    
    // 球のセットアップ
    m_Sphere.setPosition(ofGetWidth() * 0.25f, ofGetHeight() * 0.5f, 0.0f);
    m_Sphere.rotate(spinX, 1.0f, 0.0f, 0.0f);
    m_Sphere.rotate(spinY, 0.0f, 1.0f, 0.0f);
    
    // テクスチャのセットアップ
    m_SHTex.draw(ofGetWidth() * 0.5f, 0);
    //m_Test.draw(ofGetWidth() * 0.5f, 0);
    
    //m_SHTex.bind(0);
    // 球体の描画
    m_Shader.begin();
    //m_Shader.setUniformTexture("u_textureA", m_SHTex, 0);
    m_Shader.setUniformTexture("tex0", m_SHTex, 0);
    m_Sphere.draw();
    m_p.draw();
    m_Shader.end();
    
    //m_SHTex.unbind(0);
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
