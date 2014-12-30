#pragma once

unsigned int unix_time;
unsigned int now_time;
#include "ofMain.h"
#include <ofxTUI.h>

#include <Issue.h>
#include <List.h>
#include <Grid.h>
#include <DataBase.h>

class ofApp : public ofBaseApp{
	private:
		std::vector<Issue> issues_;
		ofxTUIWindow win;
		ofxTUIButton addButton_;
		ofxTUITextbox addTextbox_;
		List list_;
		Grid grid_;
		DataBase dataBase_;

		unsigned int counter;
		// unsigned int unix_time;

	public:
		ofApp():win(1,1),addButton_(1,5),addTextbox_(1,9),issues_(),list_(issues_),grid_(issues_),dataBase_(issues_),counter(0){};
		virtual ~ofApp(){};
		void setup(){
			unix_time = ofGetUnixTime();
			now_time = ofGetHours()*60*60 + ofGetMinutes()*60 + ofGetSeconds();

			dataBase_.load();

			win.addFont("fonts/Inconsolata.otf",10);
			win.loadColorScheme("defaultColorScheme.xml");
			win.fitWindowSize();
			win.addSubWindow(addTextbox_,2,9);
			addButton_.addStr("add");
			addButton_.addListener(this,&ofApp::addNewIssue);
			win.addSubWindow(addButton_,2,19);
			win.addSubWindow(list_,5,0);
			win.addSubWindow(grid_,5,22);
			win.callSetup();

			grid_.addListener(&list_,&List::loadCurrentIssues);

			list_.loadCurrentIssues();


		};

		void addNewIssue(){
			if(addTextbox_() !=""){
				list_.addIssue(addTextbox_());
			}
			addTextbox_("");
		};

		void update(){
			//debug
			// unix_time += 86400/600;
			// now_time += 86400/600;
			// now_time = now_time%86400;

			unix_time = ofGetUnixTime();
			now_time = ofGetHours()*60*60 + ofGetMinutes()*60 + ofGetSeconds();

			win.callUpdate();
		};
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

			win.setPos(2,0);
			win.setColor("Normal");
			win.addStr("AddIssue:");

			win.setPos(4,0);
			win.setColor("Normal");
			win.addStr("TaskList:");

			win.callDraw();
		};

		void exit(){
			dataBase_.save();
		}

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
