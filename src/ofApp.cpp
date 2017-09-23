#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	image.load("image.jpg");

	cap = ofRectangle(0, 0, captureWidth, captureHeight);
	screen = ofRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	cap.scaleTo(screen, OF_ASPECT_RATIO_KEEP);
	cap.scaleFromCenter(ofPoint(2, 2));
	ofLog() << cap.getCenter();
	fbo.allocate(cap.getWidth(),cap.getHeight(),GL_RGBA);


	shader.setupShaderFromSource(GL_VERTEX_SHADER, camera_convert_vertex);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER,camera_convert_fragment);
	shader.linkProgram();
	plane = ofMesh::plane(captureWidth, captureHeight);


	/*
	renderShader.setupShaderFromSource(GL_VERTEX_SHADER, render_vertex);
	renderShader.setupShaderFromSource(GL_FRAGMENT_SHADER, render_fragment);
	renderShader.linkProgram();
	renderPlane = ofMesh::plane(ofGetWindowWidth(),ofGetWindowHeight());*/

}

//--------------------------------------------------------------
void ofApp::update(){
	
	fbo.begin();
	shader.begin();
	shader.setUniformTexture("image", image.getTexture(), 0);
	plane.draw();
	shader.end();
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofTranslate(0, 0);
	ofPoint center = cap.getCenter();

	float x = center.x;
	float y = center.y / 2;
	fbo.draw(-x,-y, cap.getWidth(), cap.getHeight());

	// maybe? 
	// * seem to recall portrait still being messed up
	// * also zooming is an issue potentially?
	//fbo.draw((cap.getWidth() / 2) * -1,0,cap.getWidth() * 2,cap.getHeight() * 2);

	/*
		Maybe above for portrait, and this for landscape

		fbo.draw((cap.getWidth() / 2) * -1, (cap.getHeight() / 4) * -1, cap.getWidth() * 2, cap.getHeight() * 2);

	*/


	/*
		Using a rendering plane to avoid altering the texture as expected, has a similar effect
		due to using full screen uv settings in the shader.
	*/

	/*

	Could work? Need to figure out what default shader uniforms are + another issue is re-allocation of mesh
	
		float x = cap.getWidth() / 2;
	x *= -1;
	float aspect = cap.getWidth() / cap.getHeight();
	aspect *= 0.1;
	renderShader.begin();
	renderShader.setUniform1f("aspect",aspect);
	renderShader.setUniformTexture("image", fbo.getTexture(), 0);
	renderPlane.draw();
	renderShader.end();
	*/
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
