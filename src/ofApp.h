#pragma once

#include "ofMain.h"
#define STRINGIFY(A) #A
class ofApp : public ofBaseApp{

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
		int captureWidth = 1280;
		int captureHeight = 720;
		ofRectangle cap, screen;
		ofFbo fbo;
		ofShader shader;
		ofMesh plane;
		ofImage image;
		int scale = 2;
		
		ofMesh renderPlane;
		ofShader renderShader;

		const std::string camera_convert_vertex = STRINGIFY(
			
			attribute vec2 position;
		varying vec2 vUv;
		uniform mat4 rotationMatrix;

		const vec2 scale = vec2(0.5, 0.5);
		void main() {


			vUv = position.xy * scale + scale;
			
			gl_Position = vec4(position, 1.0, 1.0);



		}


		);



		const std::string camera_convert_fragment = STRINGIFY(
		
		// this is the yyuv texture from ARKit
		uniform sampler2D  image;
		varying vec2 vUv;


		void main() {

			// flip uvs so image isn't inverted.
			vec2 textureCoordinate = 1.0 - vec2(vUv.s, vUv.t);

			vec4 tex = texture2D(image, vUv);
			gl_FragColor = tex;

		}







		);




		const std::string render_vertex = STRINGIFY(

			attribute vec2 position;
		varying vec2 vUv;
		uniform mat4 viewMatrix;
		uniform mat4 projectionMatrix;
		uniform float aspect;

		//const vec2 scale = vec2(0.5, 0.5);
		void main() {

			vec2 scale = vec2(aspect, 0.5);
			vUv = position.xy * scale + scale;
	
			gl_Position = projectionMatrix * viewMatrix * vec4(position, -5.0, 1.0);



		}


		);


		const std::string render_fragment = STRINGIFY(

			// this is the yyuv texture from ARKit
			uniform sampler2D  image;
		varying vec2 vUv;


		void main() {

			// flip uvs so image isn't inverted.
			vec2 textureCoordinate = 1.0 - vec2(1.0 - vUv.s, vUv.t);

			vec4 tex = texture2D(image, textureCoordinate);
			gl_FragColor = tex;

		}







		);

};
