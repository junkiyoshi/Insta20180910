#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	// Make New Ripple
	if (ofGetFrameNum() % 3 == 0) {

		ofPoint point(ofRandom(this->fbo.getWidth()), ofRandom(this->fbo.getHeight()), ofRandom(500, 1000));
		unique_ptr<Ripple> ripple(new Ripple(point));
		this->ripples.push_back(move(ripple));
	}

	// Draw Ripples
	this->fbo.begin();
	ofClear(0);

	for (int i = this->ripples.size() - 1; i >= 0; i--) {

		if (this->ripples[i]->isLife()) {

			this->ripples[i]->update();
			this->ripples[i]->draw();
		}
		else {

			this->ripples.erase(this->ripples.begin() + i);
		}
	}

	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex", this->fbo.getTexture(), 1);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();

	this->fbo.draw(0, 0);
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}