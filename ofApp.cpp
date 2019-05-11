#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofSetLineWidth(2);
	ofSetCircleResolution(36);

	for (int i = 0; i < 20; i++) {

		auto location = glm::vec2(ofRandom(ofGetWidth() * 0.1, ofGetWidth() * 0.9), ofRandom(ofGetHeight() * 0.1, ofGetHeight() * 0.9));
		auto radius = ofRandom(0, 200);

		auto circle = make_pair(location, radius);
		this->circles.push_back(circle);
	}

}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& circle : this->circles) {

		circle.second += 1;

		if (circle.second > 200) {

			circle.first = glm::vec2(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
			circle.second = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (auto& circle : this->circles) {

		ofNoFill();
		ofDrawCircle(circle.first, circle.second);
		for (auto& other : this->circles) {

			if (circle == other) { continue; }

			double theta, a;
			if (this->calculate_angle(circle.first, circle.second, other.first, other.second, theta, a)) {

				auto point_1 = circle.first + glm::vec2(circle.second * cos(theta + a), circle.second * sin(theta + a));
				auto point_2 = circle.first + glm::vec2(circle.second * cos(theta - a), circle.second * sin(theta - a));

				ofFill();
				ofDrawCircle(point_1, 8);
				ofDrawCircle(point_2, 8);
			}
		}
	}

}

//--------------------------------------------------------------
bool ofApp::calculate_angle(glm::vec2 location_1, float radius_1, glm::vec2 location_2, float radius_2, double& theta, double& a) {

	auto distance = glm::distance(location_1, location_2);
	if (distance > radius_1 + radius_2 || distance < radius_1 - radius_2) { return false; }

	theta = atan2(location_2.y - location_1.y, location_2.x - location_1.x);
	auto cos_a = (pow(distance, 2) + pow(radius_1, 2) - pow(radius_2, 2)) / (2 * distance * radius_1);
	a = acos(cos_a);
	return true;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}