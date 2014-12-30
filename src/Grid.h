#pragma once
#include <Issue.h>

class Grid : public ofxTUIBaseWindow{
	std::vector<Issue>& issue_ref_;
	public:
	ofEvent<void> triggerEvent;

	Grid(std::vector<Issue>& i):ofxTUIBaseWindow(50,70,0,0),issue_ref_(i){};
	virtual ~Grid(){};

	template<class ListenerClass, typename ListenerMethod>
		void addListener(ListenerClass * listener, ListenerMethod method){
			ofAddListener(triggerEvent,listener,method);
		}

	virtual void setup(){
		setColor("None");
		fillAllBackground();
	}

	bool isRate(Issue& i){
		for (auto&& j : i.tasks_) {
			int difftime = j.time_-unix_time;
			int day = 0;
			if(difftime>=0){
				day = (int)((float)(difftime)/86400.0+0.5);
			}else{
				day = (int)((float)(difftime)/86400.0-0.5);
			}
			if(day<0 && j.check_ == 0){
				return true;
			}
		}
		return false;
	};

	virtual void draw(){
		setColor("None");
		fillAllBackground();
		int issueNum = 0;
		for (auto&& i : issue_ref_) {
			int taskNum = 0;

			//check
			if(isRate(i)){
				i.tasks_.clear();
				i.addTask(unix_time,0);
				i.addTask(unix_time+86400*1,0);
				i.addTask(unix_time+86400*3,0);
				i.addTask(unix_time+86400*7,0);
				ofNotifyEvent(triggerEvent);
			}

			setColor("None");
			setPos(issueNum,0);
			addStr(i.index_);

			setColor("Normal");
			for (auto&& j : i.tasks_) {
				int difftime = j.time_-unix_time;
				int day = 0;
				if(difftime>=0){
					day = (int)((float)(difftime)/86400.0+0.5);
				}else{
					day = (int)((float)(difftime)/86400.0-0.5);
				}


				setPos(issueNum,day+10);
				if(j.check_==0){
					if(day == 0){
						setColorBackground(200,0,0);
					}else{
						setColorBackground(128,0,0);
					}
				}else{
					if(day == 0){
						setColorBackground(0,200,0);
					}else{
						setColorBackground(0,128,0);
					}
				};
				addStr("*");

				taskNum++;
			}

			issueNum++;
		}
	};
};
