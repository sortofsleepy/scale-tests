#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofGLWindowSettings settings;
	settings.setGLVersion(2,1);
	
	
	//settings.width = 1536;
	//settings.height = 2048;

	settings.width = 2048;
	settings.height = 1536;

	ofCreateWindow(settings);
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
