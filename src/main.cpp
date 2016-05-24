#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
    ofGLWindowSettings settings;
    
    // 自分のMacBookProのサポートVerである4.1を入れておく
    settings.setGLVersion(4,1);
    settings.width  = 1024;
    settings.height = 512;
    
    ofCreateWindow(settings);
    
    ofRunApp(new ofApp());
}
