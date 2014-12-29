#pragma once
#include <Issue.h>
class TaskIndex{
	public:
		int issueNum_;
		int taskNum_;
		TaskIndex(int issueNum, int taskNum):issueNum_(issueNum),taskNum_(taskNum){}
};
class List : public ofxTUIBaseWindow{
	private:
		std::vector<Issue> issue_ref_;
		std::vector<ofxTUIToggle> toggles_o_;
		std::vector<ofxTUIToggle> toggles_x_;

		int currentIssues_;
		std::vector<TaskIndex> taskIndex_;
	public:
		List(std::vector<Issue>& i):ofxTUIBaseWindow(18,19,0,0),issue_ref_(i),toggles_o_(),toggles_x_(),currentIssues_(0),taskIndex_(){};
		virtual ~List(){};

		virtual void setup(){
			setColor("None");
			fillAllBackground();
		}

		void loadCurrentIssues(){
			taskIndex_.clear();
			clearSubWindow();
			toggles_o_.clear();
			toggles_x_.clear();

			int issueNum = 0;
			for (auto&& i : issue_ref_) {
				int taskNum = 0;
				for (auto&& t : i.tasks_) {
					if(t.time_<ofGetUnixTime()){
						if(t.check_ < 2){
							taskIndex_.push_back(TaskIndex(issueNum,taskNum));
							toggles_o_.push_back(ofxTUIToggle(1,3));
							toggles_x_.push_back(ofxTUIToggle(1,3));
							// addSubWindow(toggles_o_.back(),0,0);
							// addSubWindow(toggles_x_.back(),0,0);

						}
					}
					taskNum++;
				}
				issueNum++;
			}
		}

		virtual void draw(){
			// setColor("None");
			setColor("Frame");
			setPos(0,1);
			addStr("Index    ");
			setPos(0,11);
			addStr(" o ");
			setPos(0,15);
			addStr(" x ");

			addStrRect("|",0,0,10,1);
			addStrRect("|",0,10,10,1);
			addStrRect("|",0,14,10,1);
			addStrRect("|",0,18,10,1);

			setColor("None");
			int c = 0;
			for (auto&& i : taskIndex_) {
				setPos(c+1,1);
				addStr(issue_ref_[i.issueNum_].getIndexName());

				// toggles_o_[c].setWindowPos(c+1,6);
				// toggles_x_[c].setWindowPos(c+1,10);

				// toggles_o_[c].callDraw();
				// toggles_x_[c].callDraw();
				c++;
			}
			cout<<c<<endl;

		};

		void addIssue(std::string index_name){
			issue_ref_.push_back(Issue(index_name));
			issue_ref_.back().addTask(ofGetUnixTime(),0);
			issue_ref_.back().addTask(ofGetUnixTime()+86400*1,0);
			issue_ref_.back().addTask(ofGetUnixTime()+86400*3,0);
			issue_ref_.back().addTask(ofGetUnixTime()+86400*7,0);
		};
		// virtual void keyPressed(const int& key){};
		// virtual void keyReleased(const int& key){};
		// virtual void mouseMoved(const float& px, const float& py){
		// 	for (auto&& i : toggles_o_) {
		// 		i.callMouseMoved(px,py);
		// 	}
		// 	for (auto&& i : toggles_x_) {
		// 		i.callMouseMoved(px,py);
		// 	}
		// };
		// virtual void mouseDragged(const float& px, const float& py, const int& button){
		// 	for (auto&& i : toggles_o_) {
		// 		i.callMouseDragged(px,py,button);
		// 	}
		// 	for (auto&& i : toggles_x_) {
		// 		i.callMouseDragged(px,py,button);
		// 	}
		// };
		// virtual void mousePressed(const float& px, const float& py, const int& button){
		// 	for (auto&& i : toggles_o_) {
		// 		i.callMousePressed(px,py,button);
		// 	}
		// 	for (auto&& i : toggles_x_) {
		// 		i.callMousePressed(px,py,button);
		// 	}
		// };
		// virtual void mouseReleased(const float& px, const float& py, const int& button){
		// 	for (auto&& i : toggles_o_) {
		// 		i.callMouseReleased(px,py,button);
		// 	}
		// 	for (auto&& i : toggles_x_) {
		// 		i.callMouseReleased(px,py,button);
		// 	}
		// };
};
