#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 5);
	this->mesh = ico_sphere.getMesh();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		this->param_list.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->draw_mesh = this->mesh;
	this->line_mesh = this->mesh;

	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {
		
		auto vertex = this->draw_mesh.getVertex(i);
		auto noise_value = ofNoise(glm::vec4(vertex * 0.005, ofGetFrameNum() * 0.0085));

		if (noise_value <= 0.45 || noise_value >= 0.55) {
		
			vertex = glm::normalize(vertex) * 0;
		}

		this->draw_mesh.setVertex(i, vertex);
		this->line_mesh.setVertex(i, vertex);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.37);
	ofRotateY(ofGetFrameNum() * 0.72);

	ofSetColor(0);
	this->draw_mesh.draw();

	ofSetColor(255);
	this->line_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}