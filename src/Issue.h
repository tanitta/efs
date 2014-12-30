#pragma once
#include <Task.h>
class Issue {
	public:
		std::string index_;
		int level_;
		vector<Task> tasks_;
		Issue(std::string name):index_(name),level_(1),tasks_(){};
		virtual ~Issue(){};

		std::string getIndexName(){return index_;}

		void addTask(unsigned int time, int check){
			tasks_.push_back(Task(time,check));
		}

		bool isCompleted(){
			bool b = true;
			for (auto&& t : tasks_) {
				if(t.check_ == 1){
					b = b && true;
				}else{
					b = b && false;
				}
			}
			return b;
		}

		bool operator==(bool b){
			return isCompleted() == b;
		}
};

