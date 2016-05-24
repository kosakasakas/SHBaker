#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    // 球体のセットアップ
    m_Sphere.setRadius(ofGetHeight() * 0.3f);
    m_Sphere.setResolution(2);
    
    // シェーダのロード
    m_Shader.load("test.vert", "test.frag");
    
    // テクスチャのセット
    m_SHTex.
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    ofEnableDepthTest();
    
    m_Sphere.setPosition(ofGetWidth() * 0.25f, ofGetHeight() * 0.5f, 0.0f);
    m_Sphere.rotate(spinX, 1.0f, 0.0f, 0.0f);
    m_Sphere.rotate(spinY, 0.0f, 1.0f, 0.0f);
    
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
