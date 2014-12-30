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
		std::vector<Issue>& issue_ref_;
		std::vector<ofxTUIToggle> toggles_x_;

		ofxTUIButton pushButton_;
		ofxTUIButton readButton_;

		int currentIssues_;
		std::vector<TaskIndex> taskIndex_;
	public:
		List(std::vector<Issue>& i):ofxTUIBaseWindow(18,21,0,0),issue_ref_(i),toggles_x_(),currentIssues_(0),taskIndex_(),pushButton_(1,5),readButton_(1,5){};
		virtual ~List(){};

		virtual void setup(){
			setColor("None");
			fillAllBackground();
			pushButton_.addStr("Push");
			pushButton_.addListener(this,&List::push);

			readButton_.addStr("Read");
			readButton_.addListener(this,&List::loadCurrentIssues);
		}

		void loadCurrentIssues(){
			taskIndex_.clear();
			clearSubWindow();
			toggles_x_.clear();

			int issueNum = 0;
			for (auto&& i : issue_ref_) {
				int taskNum = 0;
				for (auto&& t : i.tasks_) {
					int difftime = t.time_-unix_time;
					int day = 0;
					day = (int)((float)(difftime)/86400.0);
					if(0 < difftime && difftime < 86400){
						if(t.check_ < 1){
							taskIndex_.push_back(TaskIndex(issueNum,taskNum));
							toggles_x_.push_back(ofxTUIToggle(1,3));

						}
					}
					taskNum++;
				}
				issueNum++;
			}
			// clearSubWindow();
			for (auto&& i : toggles_x_) {
				addSubWindow(i,0,0);
			}
			addSubWindow(pushButton_,2,15);
			addSubWindow(readButton_,0,15);
		}

		void push(){
			int c = 0;
			for (auto&& i : taskIndex_) {
				issue_ref_[i.issueNum_].tasks_[i.taskNum_].check_ = (int)toggles_x_[c]();
				c++;
			}
			issue_ref_.erase(std::remove(issue_ref_.begin(), issue_ref_.end(), true), issue_ref_.end());
			loadCurrentIssues();
		};

		virtual void update(){
		}

		virtual void draw(){
			setColor("None");
			fillAllBackground();
			setColor("Frame");
			setPos(0,1);
			addStr("Index    ");
			setPos(0,11);
			addStr(" x ");

			addStrRect("|",0,0,10,1);
			addStrRect("|",0,10,10,1);
			addStrRect("|",0,14,10,1);
			addStrRect("|",0,20,10,1);

			setColor("None");
			int c = 0;
			for (auto&& i : taskIndex_) {
				setPos(c+1,1);
				addStr(issue_ref_[i.issueNum_].getIndexName());

				toggles_x_[c].setWindowPos(c+1,11);

				c++;
			}
		};

		void addIssue(std::string index_name){
			issue_ref_.push_back(Issue(index_name));
			unsigned int deadline = unix_time-(unsigned int)now_time+86400;
			issue_ref_.back().addTask(deadline,0);
			issue_ref_.back().addTask((unsigned int)deadline+(unsigned int)(86400*1),0);
			issue_ref_.back().addTask((unsigned int)deadline+(unsigned int)(86400*3),0);
			issue_ref_.back().addTask((unsigned int)deadline+(unsigned int)(86400*7),0);
		};
};
