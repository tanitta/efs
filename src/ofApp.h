#pragma once

#include "ofMain.h"
#include <ofxTUI.h>

#include <Issue.h>
#include <Grid.h>
class ofApp : public ofBaseApp{
	private:
		std::vector<Issue> issues_;
		ofxTUIWindow win;

	public:
		ofApp():win(1,1),issues_(){};
		virtual ~ofApp(){};
		void setup(){
			win.addFont("fonts/Inconsolata.otf",10);
			win.loadColorScheme("defaultColorScheme.xml");
			win.fitWindowSize();
		};
		void update(){};
		void draw(){
			win.fillAllBackground();

			win.setPos(0,0);
			win.setColor("Frame");
			win.addStrRect("",0,0,1,win.width);
			win.setPos(0,39);
			win.addStr("+");

			win.setPos(0,0);
			win.setColor("Headline");
			win.addStr("#");
			win.setPos(0,1);
			win.setColor("Normal");
			win.addStr("Eternal Force Scheduler");

			win.setPos(1,1);
			win.setColor("None");
			win.addStr("Toggle");

			win.callDraw();
		};

		void keyPressed(int key){
			win.callKeyPressed(key);
		};

		void keyReleased(int key){};

		void mouseMoved(int x, int y ){
			win.callMouseMoved(x, y);
		};

		void mouseDragged(int x, int y, int button){
			win.callMouseDragged(x, y, button);
		};

		void mousePressed(int x, int y, int button){
			win.callMousePressed(x, y, button);
		};

		void mouseReleased(int x, int y, int button){
			win.callMouseReleased(x, y, button);
		};

		void windowResized(int w, int h){
			win.fitWindowSize(h,w);
		};
		void dragEvent(ofDragInfo dragInfo){};
		void gotMessage(ofMessage msg){};

};
