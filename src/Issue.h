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
};

