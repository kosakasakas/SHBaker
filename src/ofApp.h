#pragma once

#include "ofMain.h"

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
    ofIcoSpherePrimitive m_Sphere;
    
    //! シェーダオブジェクト
    ofShader    m_Shader;
    
    //! 球面調和関数LookUpテクスチャ
    ofTexture     m_SHTex;
    ofImage       m_SHImage;
    
    //!
    unsigned char* m_pSHTexBuffer;
    
    int m_Width;
    int m_Height;
};
