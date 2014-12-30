#pragma once
#include <ofxXmlSettings.h>
#include <Issue.h>
#include <Task.h>
class DataBase {
	std::vector<Issue>& issue_ref_;
	bool bLoaded;
	ofxXmlSettings xml;
	public:
	DataBase(std::vector<Issue>& i):issue_ref_(i),bLoaded(false){};
	virtual ~DataBase(){};

	void save(){
		// xml.addValue(const string& tag, int value)
		xml.clear();
		xml.addTag("Issues");
		if (bLoaded) {
			xml.pushTag("Issues");
			int issueNum = 0;
			for (auto&& i : issue_ref_) {
				xml.addTag("Issue_"+std::to_string(issueNum));
				xml.pushTag("Issue_"+std::to_string(issueNum));
					xml.addValue("IndexName", i.index_);
					xml.addTag("Tasks");
					xml.pushTag("Tasks");
						int taskNum = 0;
						for (auto&& t : i.tasks_) {
							xml.addTag("Task_"+std::to_string(taskNum));
							xml.pushTag("Task_"+std::to_string(taskNum));
								xml.addValue("Time", (int)t.time_);
								xml.addValue("Check", t.check_);
							xml.popTag();
							taskNum++;
						}
						xml.addValue("Number", taskNum);
					xml.popTag();
				xml.popTag();
				issueNum++;
			}
			std::cout<<"getNumTags(issue) : "<<xml.getNumTags("Issues")<<std::endl;
			xml.addValue("Number", issueNum);
			xml.popTag();

			xml.saveFile();
		}
	};

	void load(){
		std::string message;
		std::string str = "Hoge.xml";
		if(xml.loadFile(str)){
			message = str+" loaded!";
			bLoaded = true;
		}else{
			message = "unable to load "+str+" check data/ folder";
		}
		std::cout<<message<<std::endl;

		TranslateXmlToIssues();

	};

	void TranslateXmlToIssues(){
		for (int i = 0; i < xml.getValue("Issues:Number",0); i++) {
			std::string name = xml.getValue("Issues:Issue_"+std::to_string(i)+":IndexName","");
			issue_ref_.push_back(Issue(name));


			int tasks = xml.getValue("Issues:Issue_"+std::to_string(i)+":Tasks:Number",0);
			for (int t = 0; t < tasks; t++) {
				std::cout<<"TranslateXmlToIssues i:"<<i<<" t:"<<t<<std::endl;
				unsigned int time = xml.getValue("Issues:Issue_"+std::to_string(i)+":Tasks:Task_"+std::to_string(t)+":Time",0);
				int check = xml.getValue("Issues:Issue_"+std::to_string(i)+":Tasks:Task_"+std::to_string(t)+":Check",0);
				issue_ref_[i].tasks_.push_back(Task(time,check));
				std::cout<<issue_ref_[i].tasks_[t].check_<<std::endl;
			}
			// std::cout<<xml.getValue("Issues:Issue_0:Tasks:Number",0)<<std::endl;
			// int tasknumber = xml.getValue("Issues:Issue_0:Tasks:Number",0)
			// std::cout<<tasknumber<<std::endl;
			// xml.popTag();
		}
	};

};
