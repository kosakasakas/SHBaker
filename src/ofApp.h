#pragma once

#include "ofMain.h"
#include <string>

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    //! 球体オブジェクト
    ofIcoSpherePrimitive    m_Sphere;
    //! デバッグ用スクリーン
    ofPlanePrimitive        m_Plane;
    
    //! シェーダオブジェクト
    ofShader    m_Shader;
    //!
    ofShader    m_ShaderDebugSHTex;
    
    //! SHテクスチャのマップ
    std::vector<ofTexture> m_SHTexVec;
    
    //! デバッグ用カラー表示フラグ
    bool    m_bDebug;
    
    //! オフスクリーンレンダリング用のバッファ
    ofFbo   m_Fbo;
    std::vector<ofFbo>  m_FboSHVec;
    
    //! カメラ
    ofCamera    m_Camera;
};
