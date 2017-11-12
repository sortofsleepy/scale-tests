#include "ofApp.h"
//! vertex data to render the camera image
float kImagePlaneVertexData[8] = {
	-1.0, -1.0,  
	1.0, -1.0,  
	-1.0,  1.0, 
	1.0,  1.0
};

float verts[16] = {
	-1.0, -1.0,  0.0, 1.0,
	1.0, -1.0,  1.0, 1.0,
	-1.0,  1.0,  0.0, 0.0,
	1.0,  1.0,  1.0, 0.0,
};

float texCoords[8] = {
	0.0, 1.0,
	1.0,1.0,
	0.0,0.0,
	1.0,0.0
};

float aspect = 0.0f;
float diffX = 0.0f;
float diffY = 0.0f;
ofVec2f aspectRatio;
//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	image.load("image.jpg");


	cap = ofRectangle(0, 0, image.getWidth(),image.getHeight());
	screen = ofRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	aspect = 1;

	ofLog() << (float)ofGetWindowWidth() / (float)ofGetWindowHeight();

	float ratio = (float)ofGetWindowWidth() / (float)ofGetWindowHeight();


	aspectRatio.x = (float)aspect;
	aspectRatio.y = (float)aspect;



	// 2 should instead be the scale factor from [[UIScreen mainScreen] scale]
	// or maybe aspect ratio?
	cap.scaleFromCenter(ofPoint(ratio,ratio));

	diffX = cap.getWidth() - ofGetWindowWidth();
	diffY = cap.getHeight() - ofGetWindowHeight();
	diffX /= 2.0;
	diffY /= 2.0;

	//vMesh.setVertexData(kImagePlaneVertexData, 4, 8, GL_DYNAMIC_DRAW);

	vMesh.setVertexData(verts, 4, 16, GL_DYNAMIC_DRAW);

	vMesh.enableTexCoords();
	vMesh.setTexCoordData(texCoords, 8, GL_DYNAMIC_DRAW);

	fbo.allocate(ofGetWindowWidth(),ofGetWindowHeight(), GL_RGBA);
	drawFbo.allocate(cap.getWidth(),cap.getHeight(), GL_RGBA);

	shader.setupShaderFromSource(GL_VERTEX_SHADER, camera_convert_vertex);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, camera_convert_fragment);
	shader.bindDefaults();
	shader.linkProgram();
	plane = ofMesh::plane(image.getWidth(),image.getHeight());

	
}

//--------------------------------------------------------------
void ofApp::update() {


	drawFbo.begin();
	shader.begin();
	shader.setUniformTexture("image", image.getTexture(), 0);
	shader.setUniform2f("aspectRatio", aspectRatio.x,aspectRatio.y);
	vMesh.draw(GL_TRIANGLE_STRIP, 0, 16);
	shader.end();
	drawFbo.end();

	fbo.begin();
	drawFbo.draw(-diffX, -diffY);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	fbo.draw(0,0,ofGetWindowWidth(),ofGetWindowHeight());

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
